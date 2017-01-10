#include "MoveToChamberStrategy.h"
#include "Blmapv3Util.h"
#include "game/client/bot/BotUtil.h"
#include "Blmapv3StageResolver.h"

MoveToChamberStrategy::MoveToChamberStrategy(CGameClient* client) : BotStrategy(client), lastStage(0) {
}

void MoveToChamberStrategy::execute(CControls* controls) {
	if (isFrozen()) {
		BotUtil::resetInput(controls);
		return;
	}

	vec2* pos = &client->m_PredictedChar.m_Pos;
	if (pos->x > 4200 || pos->y > 1300) {
		// It's easier to just respawn than to program return from this point
		client->SendKill(-1);
	}
	int stage = Blmapv3StageResolver::resolveStage(&pos);
	if (stage != lastStage) {
		BotUtil::resetInput(controls);
	}

	if (stage == 1) {
		moveRightUnlessGateOpen(controls);
	} else if (stage == 2) {
		goFromFightingAreaToUpperArea(controls);
	} else if (stage == 3) {
		moveThroughUpperArea(controls);
	} else if (stage == 4) {
		jumpToBehindTheChamber(controls);
	} else if (stage == 5) {
		//there is no stage 5, after stage 4 we are inside the chamber. TODO Switch strategy.
	}
	lastStage = stage;
}

void MoveToChamberStrategy::moveRightUnlessGateOpen(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	bool tooLateToMoveBack = player->m_Pos.x > STAGE1_X_POS_TO_JUMP[0];
	if (!tooLateToMoveBack && Blmapv3Util::isGateOpen(client)) {
		float absDelta = fabs(GATE_X_POS - player->m_Pos.x);
		if (absDelta > 10) {
			BotUtil::moveTowards(controls, player->m_Pos.x, GATE_X_POS);
			controls->m_InputData.m_Hook = 0;
		}

		if (player->m_HookState == HOOK_GRABBED && player->m_HookPos.y > 950) {
			//accidentally hooked too low
			controls->m_InputData.m_Hook = 0;
		} else if (absDelta < 20) {
			//close enough, jump and hook
			controls->m_InputData.m_Jump = player->IsGrounded();
			controls->m_MousePos.x = 0;
			controls->m_MousePos.y = -100;
			controls->m_InputData.m_Hook = player->m_HookState != HOOK_RETRACTED; //always hook, rehook if retracted
		}
	} else {
		BotUtil::move(controls, MOVE_RIGHT);
		controls->m_InputData.m_Jump = shouldJump(STAGE1_X_POS_TO_JUMP, N_JUMPS_STAGE_1);
	}
}

void MoveToChamberStrategy::goFromFightingAreaToUpperArea(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	vec2 pos = player->m_Pos;

	bool rightFromCenter = pos.x > CENTER_X;
	int inv = rightFromCenter ? 1 : -1;

	bool inTheMiddleY = pos.y >= 846 && pos.y <= 945;
	bool hookedToDesiredSpot =
			player->m_HookState == HOOK_GRABBED &&
			player->m_HookPos.y > 500 &&
			player->m_HookPos.y < 545 &&
			(
			(player->m_HookPos.x > CENTER_X - 460 && player->m_HookPos.x < CENTER_X - 160) ||
			(player->m_HookPos.x > CENTER_X + 160 && player->m_HookPos.x < CENTER_X + 460)
			);

	if (hookedToDesiredSpot) {
		if (inTheMiddleY) {
			BotUtil::moveTowards(controls, pos.x, CENTER_X); // move to center
		} else if (rightFromCenter ? pos.x > CENTER_X + 180 : pos.x < CENTER_X - 180) {
			//near the upper traps, escape
			controls->m_InputData.m_Hook = 0;
			BotUtil::moveAwayFrom(controls, pos.x, CENTER_X);
		}
	} else {
		if (player->m_HookState == HOOK_RETRACTED) {
			controls->m_InputData.m_Hook = 0;
		}
		int targetX = CENTER_X + 210 * inv;
		if (inTheMiddleY) {
			targetX -= 25 * inv; // move target closer to center
		}
		float absDelta = fabs(pos.x - targetX);
		if (absDelta > 5) {
			BotUtil::moveTowards(controls, pos.x, targetX);
		} else {
			BotUtil::move(controls, DONT_MOVE);
			// aim hook up and a little outwards
			controls->m_MousePos.x = 10 * inv;
			controls->m_MousePos.y = -100;

			// maybe jump
			bool canDoubleJump = !(player->m_Jumped & 2);
			controls->m_InputData.m_Jump = pos.y > 850 && ((canDoubleJump && player->m_Vel.y > 5) || player->IsGrounded());

			if (inTheMiddleY && pos.y <= 900) {
				// HOOK
				controls->m_InputData.m_Hook = 1;
			}
		}
	}
}

void MoveToChamberStrategy::moveThroughUpperArea(CControls* controls) {
	BotUtil::move(controls, MOVE_LEFT);
	controls->m_InputData.m_Jump = shouldJump(STAGE2_X_POS_TO_JUMP, N_JUMPS_STAGE_2);
	if (client->m_PredictedChar.m_Pos.y > 500) {
		// down in a pothole, jump
		controls->m_InputData.m_Jump = client->m_PredictedChar.IsGrounded();
	}
}

const vec2 MoveToChamberStrategy::STAGE4_TARGET_POS = vec2(2129, 657);

void MoveToChamberStrategy::jumpToBehindTheChamber(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	vec2 pos = player->m_Pos;

	if (pos.x == STAGE4_TARGET_POS.x && pos.y == STAGE4_TARGET_POS.y) {
		controls->m_MousePos.x = -260;
		controls->m_MousePos.y = -240;
		controls->m_InputData.m_Hook = 1;
	} else if (player->m_HookState != HOOK_GRABBED) {
		BotUtil::moveTowards(controls, pos.x, STAGE4_TARGET_POS.x);

		if (pos.y > STAGE4_TARGET_POS.y && player->IsGrounded()) {
			controls->m_InputData.m_Jump = 1;
		} else {
			controls->m_InputData.m_Jump = 0;
		}
	}
}

const int MoveToChamberStrategy::STAGE1_X_POS_TO_JUMP[] = {2400, 2725, 3050};
const int MoveToChamberStrategy::STAGE2_X_POS_TO_JUMP[] = {3170, 2800, 2550};

bool MoveToChamberStrategy::shouldJump(const int* posXJumps, const int length) {
	vec2 pos = client->m_PredictedChar.m_Pos;
	for (int i = 0; i < length; i++) {
		int xPos = posXJumps[i];
		if (fabs(pos.x - xPos) < X_POS_JUMP_MARGIN) {
			return true;
		}
	}
	return false;

}