#include "MoveToChamberStrategy.h"

MoveToChamberStrategy::MoveToChamberStrategy(CGameClient* client) : BotStrategy(client), lastStage(0) {
}

void MoveToChamberStrategy::execute(CControls* controls) {
	int stage = resolveStage();
	if (stage != lastStage) {
		resetInput(controls);
	}

	if (stage == 1) {
		move(controls, MOVE_RIGHT);
		controls->m_InputData.m_Jump = shouldJump(STAGE1_X_POS_TO_JUMP, N_JUMPS_STAGE_1);
	} else if (stage == 2) {
		goFromFightingAreaToUpperArea(controls);
	} else if (stage == 3) {
		moveThroughUpperArea(controls);
	} else if (stage == 4) {
		//behind the gate, jump up behind the chamber
	} else if (stage == 5) {
		//there is no stage 5, after stage 4 we are inside the chamber. TODO Switch strategy.
	}
	lastStage = stage;
}

void MoveToChamberStrategy::goFromFightingAreaToUpperArea(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	vec2 pos = player->m_Pos;

	bool inTheMiddleY = pos.y >= 846 && pos.y <= 945;
	bool hookedToDesiredSpot =
			player->m_HookState == HOOK_GRABBED &&
			player->m_HookPos.y > 500 &&
			player->m_HookPos.y < 545 &&
			player->m_HookPos.x > 3300 &&
			player->m_HookPos.x < 3600;

	if (hookedToDesiredSpot) {
		if (inTheMiddleY) {
			move(controls, MOVE_RIGHT);
		} else if (pos.x < 3580) {
			//near the upper left trap, escape
			controls->m_InputData.m_Hook = 0;
			move(controls, MOVE_LEFT);
		}
	} else {
		controls->m_InputData.m_Hook = 0;
		int targetX = inTheMiddleY ? 3575 : 3550;
		float delta = pos.x - targetX;
		if (delta < -5) {
			move(controls, MOVE_RIGHT);
		} else if (delta > 5) {
			move(controls, MOVE_LEFT);
		} else {
			move(controls, DONT_MOVE);
			// aim hook up and a little left
			controls->m_InputData.m_TargetX = -10;
			controls->m_InputData.m_TargetY = -100;

			// maybe jump
			bool canDoubleJump = !(player->m_Jumped & 2);
			controls->m_InputData.m_Jump = player->IsGrounded() || (canDoubleJump && player->m_Vel.y > 5);

			if (inTheMiddleY && pos.y <= 878) {
				// HOOK
				controls->m_InputData.m_Hook = 1;
			}

		}
	}
}

void MoveToChamberStrategy::moveThroughUpperArea(CControls* controls) {
	move(controls, MOVE_LEFT);
	controls->m_InputData.m_Jump = shouldJump(STAGE2_X_POS_TO_JUMP, N_JUMPS_STAGE_2);
	if (client->m_PredictedChar.m_Pos.y > 500) {
		// down in a pothole, jump
		CCharacterCore* player = &client->m_PredictedChar;
		if (player->IsGrounded() && !isFrozen()) {
			controls->m_InputData.m_Jump = 1;
		} else {
			controls->m_InputData.m_Jump = 0;
		}
	}
}

int MoveToChamberStrategy::resolveStage() {
	vec2 pos = client->m_PredictedChar.m_Pos;
	if (pos.x < 1390) {
		// spawn area
		return 1;
	} else if (pos.y > 1006 && pos.x < 3400) {
		// lower area heading towards middle fighting area
		return 1;
	} else if (pos.y > 555 && pos.x >= 3400) {
		// in battle area
		return 2;
	}
	if (pos.y < 530 && pos.x > 2450 && pos.x < 3800) {
		// upper area heading left to behind the gate
		return 3;
	}
	//TODO stage 4
	if (pos.x > 3900) {
		// It's easier to just respawn than to program return from this point
		client->SendKill(-1);
	}
	return 0;
}

void MoveToChamberStrategy::move(CControls *controls, int directon) {
	if (directon == DONT_MOVE || isFrozen()) {
		controls->m_InputDirectionLeft = 0;
		controls->m_InputDirectionRight = 0;
	} else if (directon == MOVE_LEFT) {
		controls->m_InputDirectionLeft = 1;
	} else if (directon == MOVE_RIGHT) {
		controls->m_InputDirectionRight = 1;
	}
}

const int MoveToChamberStrategy::STAGE1_X_POS_TO_JUMP[] = {2380, 2700, 3020};
const int MoveToChamberStrategy::STAGE2_X_POS_TO_JUMP[] = {3170, 2800, 2550};

int MoveToChamberStrategy::shouldJump(const int* posXJumps, const int length) {
	if (isFrozen()) {
		return 0;
	}
	vec2 pos = client->m_PredictedChar.m_Pos;
	for (int i = 0; i < length; i++) {
		int xPos = posXJumps[i];
		if (fabs(pos.x - xPos) < X_POS_JUMP_MARGIN) {
			return 1;
		}
	}
	return 0;

}
