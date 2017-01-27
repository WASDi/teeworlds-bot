#include "DragOutFromLowerLeft.h"

#include "../../../../BotUtil.h"

DragOutFromLowerLeft::DragOutFromLowerLeft(CControls* controls, CCharacterCore* me, CCharacterCore* otherPlayer) :
BotSubStrategy(controls, me, otherPlayer),
state(PRE_INIT) {
}

bool DragOutFromLowerLeft::applicable(vec2* pos) {
	return pos->x >= LEFT_BOUNDARY && pos->x <= RIGHT_BOUNDARY && pos->y == LOWER_BOUNDARY;
}

const vec2 DragOutFromLowerLeft::PRE_START_POS = vec2(1553, 657);
const vec2 DragOutFromLowerLeft::START_POS = vec2(1500, 657);

void DragOutFromLowerLeft::executeInternal() {
	if (me->m_HookState == HOOK_GRABBED && me->m_HookedPlayer == -1) {
		// grabbed wall, not supposed to happen when helping
		controls->m_InputData.m_Hook = 0;
		done = true;
		return;
	}

	bool releaseEarly = otherPlayer->m_Pos.x < LEFT_BOUNDARY + 20 && otherPlayer->m_Pos.y < Y_MIN + 20;
	if (releaseEarly || otherPlayer->m_Pos.y < Y_MIN || otherPlayer->m_Pos.x > RIGHT_BOUNDARY) {
		controls->m_InputData.m_Hook = 0;
		done = true;
	}

	if (state <= JUMPED && !applicable(&otherPlayer->m_Pos)) {
		// other player respawned or was moved away
		done = true;
		return;
	}

	if (state == PRE_INIT) {
		if (me->m_Pos == PRE_START_POS) {
			state = MOVE_TO_START_POS;
		} else {
			BotUtil::moveTowardsWithJump(controls, me, &PRE_START_POS, false);
		}
	} else if (state == MOVE_TO_START_POS) {
		if (me->m_Pos.y == START_POS.y && fabs(me->m_Pos.x - START_POS.x) < 5) {
			BotUtil::move(controls, DONT_MOVE);
			if (fabs(me->m_Vel.x) < 0.01 && fabs(me->m_Vel.y) < 0.01) {
				// stationary at start pos
				controls->m_InputData.m_Jump = 1;
				state = JUMPED;
			}
		} else {
			BotUtil::moveTowardsWithJump(controls, me, &START_POS, true);
		}
	} else if (state == JUMPED) {
		controls->m_InputData.m_Jump = 0;

		//realistic-looking aim
		controls->m_MousePos.x = -10;
		controls->m_MousePos.y = 20;
		if (me->m_Vel.y > 0) {
			if (otherPlayer->m_Pos.x > DANGEROUS_THRESHOLD) {
				state = DANGEROUS_FALLING;
			} else {
				controls->m_MousePos.x = otherPlayer->m_Pos.x - me->m_Pos.x - 20;
				controls->m_MousePos.y = otherPlayer->m_Pos.y - me->m_Pos.y;
				controls->m_InputData.m_Hook = 1;
				state = FALLING_HOOKING;
			}
		}
	} else if (state == FALLING_HOOKING) {
		// Hook fired last last state, player should be grabbed
		BotUtil::move(controls, MOVE_RIGHT);
	} else if (state == DANGEROUS_FALLING) {
		if (me->m_Pos.y > 650) {
			BotUtil::move(controls, MOVE_RIGHT);
			controls->m_MousePos.x = otherPlayer->m_Pos.x - me->m_Pos.x - 20;
			controls->m_MousePos.y = otherPlayer->m_Pos.y - me->m_Pos.y;
			controls->m_InputData.m_Hook = 1;
			controls->m_InputData.m_Jump = 1;
			state = FALLING_HOOKING;
		} else {
			BotUtil::move(controls, MOVE_LEFT);
		}
	}

}