#include "Step5_OpenTheGateStrategy.h"
#include "game/client/bot/strategies/blmapv3/Blmapv3StageResolver.h"
#include "game/client/bot/BotUtil.h"

Step5_OpenTheGateStrategy::Step5_OpenTheGateStrategy(CGameClient* client) :
BotStrategy(client),
nemesisClientId(-1),
state(IDLE),
avoidDyingUntil(0) {
	extras = Step5Extras();
}

const vec2 Step5_OpenTheGateStrategy::IDLE_POS1 = vec2(1520 + 8, 657);
const vec2 Step5_OpenTheGateStrategy::IDLE_POS2 = vec2(1584, 625);
const vec2 Step5_OpenTheGateStrategy::ATTACK_POS = vec2(1648, 593);

#include <stdio.h>

void Step5_OpenTheGateStrategy::execute(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;

	if (state == AVOID_DYING) {
		if (avoidDyingUntil > getNowMillis()) {
			maybeAvoidDying(controls);
			return;
		} else {
			state = IDLE;
		}
	}

	CCharacterCore* enemy = 0;
	int newNemesisClientId = -1; // prioritized enemy
	bool enemyOnGateToggle = false;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (i == client->m_Snap.m_LocalClientID || !client->m_Snap.m_aCharacters[i].m_Active)
			continue;

		CCharacterCore* otherPlayer = &client->m_aClients[i].m_Predicted;
		if (Blmapv3StageResolver::insideChamber(&otherPlayer->m_Pos)) {
			bool otherPlayerOnGateToggle = insideGateToggle(&otherPlayer->m_Pos);
			bool foundNewEnemy = false;
			if (!enemy) {
				if (otherPlayerOnGateToggle || i == nemesisClientId) {
					foundNewEnemy = true;
				}
			} else if (otherPlayerOnGateToggle) {
				foundNewEnemy = true;
			}

			if (foundNewEnemy) {
				enemy = otherPlayer;
				newNemesisClientId = i;
				enemyOnGateToggle = otherPlayerOnGateToggle;
			}
		}
	}

	nemesisClientId = newNemesisClientId;

	if (state == RETURN_TO_IDLE || !enemy) {
		nemesisClientId = -1;
		if (!enemy) {
			maybeHelpSomeone(controls);
		} else {
			idle(controls);
		}
		return;
	}

	if (state == INIT_ATTACK) {
		controls->m_MousePos.x = enemy->m_Pos.x - player->m_Pos.x;
		controls->m_MousePos.y = enemy->m_Pos.y - player->m_Pos.y - 10; // a little above to don't hook ground
		controls->m_InputData.m_Hook = 1;
		controls->m_InputData.m_Jump = 1;
		state = WAIT_FOR_SECOND_JUMP;
	} else if (state == WAIT_FOR_SECOND_JUMP) {
		if (player->m_HookState == HOOK_GRABBED && player->m_HookedPlayer == -1) {
			state = RETURN_TO_IDLE;
		}
		BotUtil::moveTowards(controls, player->m_Pos.x, ATTACK_POS.x);
		controls->m_InputData.m_Jump = 0;
		if (player->m_Vel.y > 0.5) {
			controls->m_InputData.m_Jump = 1;
			state = HAMMER_READY;
		}
	} else if (state == HAMMER_READY) {
		BotUtil::moveTowards(controls, player->m_Pos.x, ATTACK_POS.x);
		if (player->m_HookState != HOOK_GRABBED || player->IsGrounded()) {
			state = RETURN_TO_IDLE; // fail, try again
		} else if (distance(player->m_Pos, enemy->m_Pos) < 55) {
			controls->m_InputData.m_Fire = 1;
			state = RETURN_TO_IDLE; // hope that enemy went away
		}
	} else if (enemyOnGateToggle) {
		if (BotUtil::atXPosition(player->m_Pos.x, ATTACK_POS.x, TARGET_POS_TOLERANCE) && player->IsGrounded()) {
			state = INIT_ATTACK;
			BotUtil::resetInput(controls);
		} else {
			BotUtil::resetInput(controls);
			BotUtil::moveTowardsWithJump(controls, player, &ATTACK_POS, true);
			maybeAvoidDying(controls);
		}
	} else {

		idle(controls);
	}
}

void Step5_OpenTheGateStrategy::maybeHelpSomeone(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (i == client->m_Snap.m_LocalClientID || !client->m_Snap.m_aCharacters[i].m_Active)
			continue;

		CCharacterCore* otherPlayer = &client->m_aClients[i].m_Predicted;
		if (otherPlayer->m_Pos.x >= 1390 && otherPlayer->m_Pos.x <= 1424 && otherPlayer->m_Pos.y == 785) {
			//Frozen in lower left
		} else if (extras.pushOutFromUpperRight.applicable(&otherPlayer->m_Pos)) {
			//Frozen in upper right
			extras.pushOutFromUpperRight.execute(controls, player, otherPlayer);
			return;
		} else if (Blmapv3StageResolver::insideChamber(&otherPlayer->m_Pos)) {
			bool frozen = otherPlayer->m_Input.m_WantedWeapon == WEAPON_NINJA;
			bool idle = false; // TODO resolve if no input for X seconds
			if (frozen || idle) {
				// TODO: throw out
			}
		}

	}

	idle(controls); // Idle if no one to help
}

void Step5_OpenTheGateStrategy::idle(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	state = IDLE;
	BotUtil::resetInput(controls);
	vec2* idlePos = getDesiredIdlePos();
	if (BotUtil::atXPosition(player->m_Pos.x, idlePos->x, TARGET_POS_TOLERANCE)) {
		controls->m_MousePos.x = 0;
		controls->m_MousePos.y = 100;
		controls->m_InputData.m_Hook = 1;
	} else {
		BotUtil::moveTowardsWithJump(controls, player, idlePos, true);
		bool hookedToDesiredPosition = player->m_HookState == HOOK_GRABBED
				&& fabs(player->m_HookPos.x - idlePos->x) < TARGET_POS_TOLERANCE * 2
				&& fabs(player->m_HookPos.y - (idlePos->y + 42)) < TARGET_POS_TOLERANCE * 2;
		controls->m_InputData.m_Hook = hookedToDesiredPosition;
	}
	maybeAvoidDying(controls);
}

bool Step5_OpenTheGateStrategy::insideGateToggle(vec2* pos) {
	return pos->x <= 1489 && pos->y < 690;
}

void Step5_OpenTheGateStrategy::maybeAvoidDying(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	vec2* currPos = &player->m_Pos;
	vec2 expectedPos = vec2(currPos->x + player->m_Vel.x * 5,
			currPos->y + player->m_Vel.y * 5);

	// TODO if I am hooking AND I am hooked THEN remain hooking?
	// TODO use intersect to try not grab players when hooking?

	if (expectedPos.x > 1750) {
		// Upper right
		BotUtil::move(controls, MOVE_LEFT);
		// Hook down and a little left
		controls->m_MousePos.x = -10;
		controls->m_MousePos.y = 100;
		controls->m_InputData.m_Hook = 1;
		toggleAvoidDying();
	} else if (expectedPos.x < 1440) {
		// Lower left
		// Hook and move right, maybe jump
		BotUtil::move(controls, MOVE_RIGHT);
		controls->m_InputData.m_Jump = currPos->y > 689; // fell of the edge
		controls->m_MousePos.x = 100;
		controls->m_MousePos.y = 0;
		controls->m_InputData.m_Hook = 1;
		toggleAvoidDying();
	} else if (Blmapv3StageResolver::insideChamberFreeze(&expectedPos)) {
		// Upper left
		BotUtil::move(controls, MOVE_RIGHT);
		// Hook up right, because down is too far
		controls->m_MousePos.x = 100;
		controls->m_MousePos.y = -100;
		controls->m_InputData.m_Hook = 1;
		toggleAvoidDying();
	}
}

void Step5_OpenTheGateStrategy::toggleAvoidDying() {
	if (state == AVOID_DYING) {
		return;
	}
	state = AVOID_DYING;
	avoidDyingUntil = getNowMillis() + 300;
}

vec2* Step5_OpenTheGateStrategy::getDesiredIdlePos() {
	// TODO instead of cycling with time, return pos1 if another player is able to hook from outside
	return (vec2*) (getNowMillis() % (IDLE_POS_CYCLE_TIME * 2) > IDLE_POS_CYCLE_TIME ?
			&IDLE_POS1 : &IDLE_POS2);
}