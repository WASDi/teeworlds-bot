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
		//go to 2129,657
		//aim -260,-240
		//hook
	} else if (stage == 5) {
		//there is no stage 5, after stage 4 we are inside the chamber. TODO Switch strategy.
	}
	lastStage = stage;
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
			move(controls, rightFromCenter ? MOVE_LEFT : MOVE_RIGHT); // move to center
		} else if (rightFromCenter ? pos.x > CENTER_X + 180 : pos.x < CENTER_X - 180) {
			//near the upper traps, escape
			controls->m_InputData.m_Hook = 0;
			move(controls, rightFromCenter ? MOVE_RIGHT : MOVE_LEFT); // move away from center
		}
	} else {
		if (player->m_HookState == HOOK_RETRACTED) {
			controls->m_InputData.m_Hook = 0;
		}
		int targetX = CENTER_X + 210 * inv;
		if (inTheMiddleY) {
			targetX -= 25 * inv; // move target closer to center
		}
		float delta = pos.x - targetX;
		if (delta < -5) {
			move(controls, MOVE_RIGHT);
		} else if (delta > 5) {
			move(controls, MOVE_LEFT);
		} else {
			move(controls, DONT_MOVE);
			// aim hook up and a little outwards
			controls->m_MousePos.x = 10 * inv;
			controls->m_MousePos.y = -100;

			// maybe jump
			bool canDoubleJump = !(player->m_Jumped & 2);
			controls->m_InputData.m_Jump = player->IsGrounded() || (canDoubleJump && player->m_Vel.y > 5);

			if (inTheMiddleY && pos.y <= 900) {
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
	//TODO code that looks better using bounding boxes
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
	if (pos.y < 530 && pos.x > 2385 && pos.x < 3800) {
		// upper area heading left to behind the gate
		return 3;
	}
	if (pos.x > 1380 && pos.x <= 2385 && pos.y < 1000) {
		// within bounding box for area behind gate (stage 4 or 5)
		if (pos.x < 1850) {
			// left of freeze before chamber
			bool insideChamber = aboveLine(pos, UPPER_STAIRS_COORDINATES);
			if (insideChamber) {
				return 5; // success!
			}
		}
		bool behindGateArea = aboveLine(pos, LOWER_STAIRS_COORDINATES);
		if (behindGateArea) {
			return 4;
		}
	}
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
		controls->m_InputDirectionRight = 0;
	} else if (directon == MOVE_RIGHT) {
		controls->m_InputDirectionLeft = 0;
		controls->m_InputDirectionRight = 1;
	}
}

const int MoveToChamberStrategy::STAGE1_X_POS_TO_JUMP[] = {2400, 2725, 3050};
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

const vec4 MoveToChamberStrategy::UPPER_STAIRS_COORDINATES = vec4(1489, 699, 1809, 539);
const vec4 MoveToChamberStrategy::LOWER_STAIRS_COORDINATES = vec4(1489, 987, 2385, 539);

bool MoveToChamberStrategy::aboveLine(vec2 pos, vec4 lineData) {
	float stairKValue = (lineData.y - lineData.w) / (lineData.z - lineData.x);
	vec2 posNorm = vec2(pos.x - lineData.x, lineData.y - pos.y);

	return posNorm.y > stairKValue * posNorm.x;
}