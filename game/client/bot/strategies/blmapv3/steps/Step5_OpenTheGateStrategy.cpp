#include "Step5_OpenTheGateStrategy.h"
#include "game/client/bot/strategies/blmapv3/Blmapv3StageResolver.h"
#include "game/client/bot/BotUtil.h"

#include "step5help/PushOutFromUpperRight.h"
#include "step5help/DragOutFromLowerLeft.h"

#include "step5attack/AttackFromAbove.h"
#include "step5attack/TraditionalAttack.h"

Step5_OpenTheGateStrategy::Step5_OpenTheGateStrategy(CGameClient* client) :
BotStrategy(client),
nemesisClientId(-1),
state(IDLE),
avoidDyingUntil(0),
helpStrategy(0),
attackStrategy(0) {
}

const vec2 Step5_OpenTheGateStrategy::IDLE_POS1 = vec2(1520 + 8, 657);
const vec2 Step5_OpenTheGateStrategy::IDLE_POS2 = vec2(1584, 625);
const vec2 Step5_OpenTheGateStrategy::DANGEROUS_HOOKER_POS = vec2(1580, 450);

#include <stdio.h>

void Step5_OpenTheGateStrategy::execute() {
	CCharacterCore* player = &client->m_PredictedChar;

	if (state == AVOID_DYING) {
		if (avoidDyingUntil > getNowMillis()) {
			maybeAvoidDying();
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
			if (otherPlayer->m_Input.m_WantedWeapon == WEAPON_NINJA && otherPlayer->m_Pos.x <= 1425) {
				// frozen and not on the platform
				continue;
			}
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
			maybeHelpSomeoneOrElseIdle();
		} else {
			idle();
		}
	} else if (state == ATTACK_STRATEGY) {
		if (attackStrategy->isDone()) {
			BotUtil::resetInput(getControls());
			state = RETURN_TO_IDLE;
		} else {
			attackStrategy->execute();
		}
	} else if (enemyOnGateToggle) {
		BotUtil::resetInput(getControls());
		if (BotUtil::atXPosition(player->m_Pos.x, TraditionalAttack::ATTACK_POS.x, TARGET_POS_TOLERANCE) && player->IsGrounded()) {
			if (rand() % 2 == 0) {
				enterAttackState(new AttackFromAbove(getControls(), player, enemy));
			} else {
				enterAttackState(new TraditionalAttack(getControls(), player, enemy));
			}
		} else {
			BotUtil::moveTowardsWithJump(getControls(), player, &TraditionalAttack::ATTACK_POS, true);
			maybeAvoidDying();
		}
	} else {
		idle();
	}
}

void Step5_OpenTheGateStrategy::maybeHelpSomeoneOrElseIdle() {
	if (state == HELPING) {
		if (helpStrategy->isDone()) {
			BotUtil::resetInput(getControls());
			state = RETURN_TO_IDLE;
		} else {
			helpStrategy->execute();
		}
		return;
	}

	// TODO prioritize closest helpable player? Maybe not important
	CCharacterCore* player = &client->m_PredictedChar;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (i == client->m_Snap.m_LocalClientID || !client->m_Snap.m_aCharacters[i].m_Active)
			continue;

		CCharacterCore* otherPlayer = &client->m_aClients[i].m_Predicted;
		if (DragOutFromLowerLeft::applicable(&otherPlayer->m_Pos)) {
			//Frozen in lower left
			enterHelpState(new DragOutFromLowerLeft(getControls(), player, otherPlayer));
			return;
		} else if (PushOutFromUpperRight::applicable(&otherPlayer->m_Pos)) {
			//Frozen in upper right
			enterHelpState(new PushOutFromUpperRight(getControls(), player, otherPlayer));
			return;
		} else if (Blmapv3StageResolver::insideChamber(&otherPlayer->m_Pos)) {
			bool frozen = otherPlayer->m_Input.m_WantedWeapon == WEAPON_NINJA;
			bool hooked = otherPlayer->m_HookState == HOOK_GRABBED;
			bool idle = false; // TODO resolve if no input for X seconds
			if (frozen || (!hooked && idle)) {
				// TODO: throw out
			}
		}

	}

	idle(); // Idle if no one to help
}

void Step5_OpenTheGateStrategy::enterHelpState(BotSubStrategy* newHelpStrategy) {
	if (helpStrategy != 0) {
		delete helpStrategy;
		helpStrategy = 0;
	}
	BotUtil::resetInput(getControls());
	helpStrategy = newHelpStrategy;
	state = HELPING;
}

void Step5_OpenTheGateStrategy::enterAttackState(BotSubStrategy* newAttackStrategy) {
	if (attackStrategy != 0) {
		delete attackStrategy;
		attackStrategy = 0;
	}
	BotUtil::resetInput(getControls());
	attackStrategy = newAttackStrategy;
	state = ATTACK_STRATEGY;
}

void Step5_OpenTheGateStrategy::idle() {
	CCharacterCore* player = &client->m_PredictedChar;
	state = IDLE;
	BotUtil::resetInput(getControls());
	const vec2* idlePos = getDesiredIdlePos();
	if (BotUtil::atXPosition(player->m_Pos.x, idlePos->x, TARGET_POS_TOLERANCE)) {
		if (player->m_HookState != HOOK_GRABBED) {
			getControls()->m_MousePos.x = idlePos->x - player->m_Pos.x;
			getControls()->m_MousePos.y = idlePos->y - player->m_Pos.y + 32;
		}
		getControls()->m_InputData.m_Hook = player->m_HookState != HOOK_RETRACTED;
	} else {
		BotUtil::moveTowardsWithJump(getControls(), player, idlePos, true);
		if (player->m_HookState == HOOK_GRABBED) {
			bool hookIsAtDesiredPosition = fabs(player->m_HookPos.x - idlePos->x) < TARGET_POS_TOLERANCE * 2
					&& fabs(player->m_HookPos.y - idlePos->y) < TARGET_POS_TOLERANCE * 4;
			getControls()->m_InputData.m_Hook = hookIsAtDesiredPosition;
		} else {
			if (player->m_HookState != HOOK_GRABBED) {
				getControls()->m_MousePos.x = idlePos->x - player->m_Pos.x;
				getControls()->m_MousePos.y = idlePos->y - player->m_Pos.y + 32;
			}
			getControls()->m_InputData.m_Hook = player->m_HookState != HOOK_RETRACTED;
		}
	}
	maybeAvoidDying();
}

bool Step5_OpenTheGateStrategy::insideGateToggle(vec2* pos) {
	return pos->x <= 1489 && pos->y < 690;
}

void Step5_OpenTheGateStrategy::maybeAvoidDying() {
	CCharacterCore* player = &client->m_PredictedChar;
	CControls* controls = getControls();
	vec2* currPos = &player->m_Pos;
	vec2 expectedPos = vec2(currPos->x + player->m_Vel.x * 4,
			currPos->y + player->m_Vel.y * 4);

	// TODO if I am hooking AND I am hooked THEN remain hooking?
	// TODO use intersect to try not grab players when hooking?

	if (expectedPos.x > 1750) {
		// Upper right
		BotUtil::move(controls, MOVE_LEFT);
		// Hook down and a little left
		getControls()->m_MousePos.x = -20;
		getControls()->m_MousePos.y = 100;
		getControls()->m_InputData.m_Hook = 1;
		toggleAvoidDying();
	} else if (expectedPos.x < 1440) {
		// Lower left
		// Hook and move right, maybe jump
		BotUtil::move(controls, MOVE_RIGHT);
		getControls()->m_InputData.m_Jump = currPos->y > 689; // fell of the edge
		getControls()->m_MousePos.x = 100;
		getControls()->m_MousePos.y = 0;
		getControls()->m_InputData.m_Hook = 1;
		toggleAvoidDying();
	} else if (Blmapv3StageResolver::insideChamberFreeze(&expectedPos)) {
		// Upper left
		BotUtil::move(controls, MOVE_RIGHT);
		// Hook down right
		getControls()->m_MousePos.x = 100;
		getControls()->m_MousePos.y = 100;
		getControls()->m_InputData.m_Hook = 1;
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

const vec2* Step5_OpenTheGateStrategy::getDesiredIdlePos() {
	CCharacterCore* playerHookingMe = getPlayerHookingMe();
	if (playerHookingMe && distance(DANGEROUS_HOOKER_POS, playerHookingMe->m_Pos) < 100) {
		return &IDLE_POS2;
	}
	return getNowMillis() % (IDLE_POS_CYCLE_TIME * 2) > IDLE_POS_CYCLE_TIME ?
			&IDLE_POS1 : &IDLE_POS2;
}