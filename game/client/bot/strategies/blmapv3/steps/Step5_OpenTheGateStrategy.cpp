#include "Step5_OpenTheGateStrategy.h"
#include "game/client/bot/strategies/blmapv3/Blmapv3StageResolver.h"
#include "game/client/bot/BotUtil.h"

Step5_OpenTheGateStrategy::Step5_OpenTheGateStrategy(CGameClient* client) :
BotStrategy(client),
nemesisClientId(-1),
state(IDLE),
avoidedDyingManouverLastFrame(false) {
}

const vec2 Step5_OpenTheGateStrategy::IDLE_POS = vec2(1520 + 8, 657); // TODO cycle between positions?
const vec2 Step5_OpenTheGateStrategy::ATTACK_POS = vec2(1648, 593);

#include <stdio.h>

void Step5_OpenTheGateStrategy::execute(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;

	if (avoidedDyingManouverLastFrame) {
		BotUtil::resetInput(controls);
		avoidedDyingManouverLastFrame = false;
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
		idle(controls);
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
			avoidDying(controls);
		}
	} else {
		// TODO rescue tees out of the chamber
		// if not hooked and in chamber, push out
		// if frozen in lower left, drag out the underway
		// if in upper right, push out
		// if other player is frozen in safe area, hook out

		idle(controls);
	}
}

void Step5_OpenTheGateStrategy::idle(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	state = IDLE;
	BotUtil::resetInput(controls);
	if (BotUtil::atXPosition(player->m_Pos.x, IDLE_POS.x, TARGET_POS_TOLERANCE)) {
		controls->m_MousePos.x = 0;
		controls->m_MousePos.y = 100;
		controls->m_InputData.m_Hook = 1;
	} else {
		BotUtil::moveTowardsWithJump(controls, player, &IDLE_POS, true);
		//TODO remain hooked if hook position is good?
	}
	avoidDying(controls);
}

bool Step5_OpenTheGateStrategy::insideGateToggle(vec2* pos) {
	return pos->x <= 1489 && pos->y < 690;
}

void Step5_OpenTheGateStrategy::avoidDying(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	vec2* currPos = &player->m_Pos;
	vec2 expectedPos = vec2(currPos->x + player->m_Vel.x * 5,
			currPos->y + player->m_Vel.y * 5);

	// TODO if I am hooking AND I am hooked THEN remain hooking?
	// TODO if I am being hooked by someone outside, hook down and move left
	// TODO use intersect to try not grab players when hooking?
	// TODO remain hooked for at 250ms or so
	
	if (expectedPos.x > 1750) {
		// Upper right
		avoidedDyingManouverLastFrame = true;
		BotUtil::move(controls, MOVE_LEFT);
		// Hook down down left
		controls->m_MousePos.x = -50;
		controls->m_MousePos.y = 100;
		controls->m_InputData.m_Hook = 1;
	} else if (expectedPos.x < 1440) {
		// Lower left
		avoidedDyingManouverLastFrame = true;
		BotUtil::move(controls, MOVE_RIGHT);
		if (currPos->y > 689) {
			controls->m_InputData.m_Jump = 1;
		}
		// Hook up right
		controls->m_MousePos.x = 100;
		controls->m_MousePos.y = -100;
		controls->m_InputData.m_Hook = 1;
	} else if (Blmapv3StageResolver::insideChamberFreeze(&expectedPos)) {
		// Upper left
		avoidedDyingManouverLastFrame = true;
		BotUtil::move(controls, MOVE_RIGHT);
		// Hook down right
		controls->m_MousePos.x = 100;
		controls->m_MousePos.y = 100;
		controls->m_InputData.m_Hook = 1;
	}
}