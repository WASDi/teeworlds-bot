#include "DragOutFromLowerLeft.h"

#include "../../../../BotUtil.h"
#include "base/tl/range.h"

DragOutFromLowerLeft::DragOutFromLowerLeft(CControls* controls, CCharacterCore* player, CCharacterCore* other) :
Step5HelpStrategy(controls, player, other),
state(PRE_INIT) {
}

bool DragOutFromLowerLeft::applicable(vec2* pos) {
	return pos->x >= LEFT_BOUNDARY && pos->x <= RIGHT_BOUNDARY && pos->y == LOWER_BOUNDARY;
}

const vec2 DragOutFromLowerLeft::PRE_START_POS = vec2(1553, 657);
const vec2 DragOutFromLowerLeft::START_POS = vec2(1500, 657);

void DragOutFromLowerLeft::execute() {
	if (player->m_HookState == HOOK_GRABBED && player->m_HookedPlayer == -1) {
		// grabbed wall, not supposed to happen
		controls->m_InputData.m_Hook = 0;
		state = PRE_INIT;
		return;
	}
	if (/* other left game TODO*/0) {
		done = true;
		return;
	}

	bool releaseEarly = other->m_Pos.y < Y_MIN + 32 && other->m_Pos.x < LEFT_BOUNDARY + 16;
	if (releaseEarly || other->m_Pos.y < Y_MIN || other->m_Pos.x > RIGHT_BOUNDARY) {
		controls->m_InputData.m_Hook = 0;
		done = true;
	}

	if (state == PRE_INIT) {
		if (player->m_Pos == PRE_START_POS) {
			state = MOVE_TO_START_POS;
		} else {
			BotUtil::moveTowardsWithJump(controls, player, &PRE_START_POS, false);
		}
	} else if (state == MOVE_TO_START_POS) {
		if (player->m_Pos.y == START_POS.y && fabs(player->m_Pos.x - START_POS.x) < 5) {
			BotUtil::move(controls, DONT_MOVE);
			if (fabs(player->m_Vel.x) < 0.01 && fabs(player->m_Vel.y) < 0.01) {
				// stationary at start pos
				controls->m_InputData.m_Jump = 1;
				state = JUMPED;
			}
		} else {
			BotUtil::moveTowardsWithJump(controls, player, &START_POS, true);
		}
	} else if (state == JUMPED) {
		controls->m_InputData.m_Jump = 0;
		if (player->m_Vel.y > 0) {
			if (!applicable(&other->m_Pos)) {
				// other player respawned or was moved away
				done = true;
				return;
			}

			if (other->m_Pos.x > DANGEROUS_THRESHOLD) {
				state = DANGEROUS_FALLING;
			} else {
				controls->m_MousePos.x = other->m_Pos.x - player->m_Pos.x - 20;
				controls->m_MousePos.y = other->m_Pos.y - player->m_Pos.y;
				controls->m_InputData.m_Hook = 1;
				state = FALLING_HOOKING;
			}
		}
	} else if (state == FALLING_HOOKING) {
		// Hook fired last last state, player should be grabbed
		BotUtil::move(controls, MOVE_RIGHT);
	} else if (state == DANGEROUS_FALLING) {
		if (player->m_Pos.y > 650) {
			BotUtil::move(controls, MOVE_RIGHT);
			controls->m_MousePos.x = other->m_Pos.x - player->m_Pos.x - 20;
			controls->m_MousePos.y = other->m_Pos.y - player->m_Pos.y;
			controls->m_InputData.m_Hook = 1;
			controls->m_InputData.m_Jump = 1;
			state = FALLING_HOOKING;
		} else {
			BotUtil::move(controls, MOVE_LEFT);
		}
	}

}