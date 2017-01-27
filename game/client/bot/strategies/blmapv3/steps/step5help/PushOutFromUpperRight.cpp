#include "PushOutFromUpperRight.h"

#include "../../../../BotUtil.h"

PushOutFromUpperRight::PushOutFromUpperRight(CControls* controls, CCharacterCore* me, CCharacterCore* otherPlayer) :
BotSubStrategy(controls, me, otherPlayer) {
}

bool PushOutFromUpperRight::applicable(vec2* pos) {
	return pos->x >= 1824 && pos->x < 1888 && pos->y == 497;
}

const vec2 PushOutFromUpperRight::TARGET = vec2(1809, 529);
const vec2 PushOutFromUpperRight::PRE_TARGET = vec2(TARGET.x - 48, TARGET.y);

void PushOutFromUpperRight::executeInternal() {
	if (!applicable(&otherPlayer->m_Pos)) {
		done = true;
		return;
	}
	if (me->m_Pos.x == TARGET.x) {
		if (me->m_Pos.y == TARGET.y) {
			controls->m_MousePos.x = 200;
			controls->m_MousePos.y = -100;
			if (distance(me->m_Pos, otherPlayer->m_Pos) < 60) {
				controls->m_InputData.m_Hook = 0;
				controls->m_InputData.m_Jump = 1;
			} else {
				controls->m_InputData.m_Hook = me->m_HookState != HOOK_RETRACTED;
			}
		} else if (me->m_Pos.y < TARGET.y - 32) {
			//has jumped high enough, attack!
			controls->m_MousePos.x = 100;
			controls->m_MousePos.y = 0;
			controls->m_InputData.m_Fire = 1;
			BotUtil::move(controls, MOVE_LEFT);
			done = true;
		} else {
			//in air, not high enough
			controls->m_InputData.m_Jump = 0;
		}

	} else {
		controls->m_InputData.m_Hook = 0;
		controls->m_InputData.m_Fire = 0;
		// Move to "pre target" with jump, then walk safely
		if (me->m_Pos.x < PRE_TARGET.x || me->m_Pos.y < TARGET.y) {
			BotUtil::moveTowardsWithJump(controls, me, &PRE_TARGET, true);
		} else {
			BotUtil::moveTowards(controls, me->m_Pos.x, TARGET.x);
		}
	}
}