#include "TraditionalAttack.h"

#include "../../../../BotUtil.h"

TraditionalAttack::TraditionalAttack(CControls* controls, CCharacterCore* me, CCharacterCore* otherPlayer) :
BotSubStrategy(controls, me, otherPlayer),
state(INIT_ATTACK) {
}

const vec2 TraditionalAttack::ATTACK_POS = vec2(1648, 593);

void TraditionalAttack::executeInternal() {
	if (state == INIT_ATTACK) {
		controls->m_MousePos.x = otherPlayer->m_Pos.x - me->m_Pos.x;
		controls->m_MousePos.y = otherPlayer->m_Pos.y - me->m_Pos.y - 10; // a little above to don't hook ground
		controls->m_InputData.m_Hook = 1;
		controls->m_InputData.m_Jump = 1;
		state = WAIT_FOR_SECOND_JUMP;
	} else if (state == WAIT_FOR_SECOND_JUMP) {
		if (me->m_HookState == HOOK_GRABBED && me->m_HookedPlayer == -1) {
			//accidentally hooked wall
			done = true;
		}
		BotUtil::moveTowards(controls, me->m_Pos.x, ATTACK_POS.x); // TODO another attack pos or something if occupied
		controls->m_InputData.m_Jump = 0;
		if (me->m_Vel.y > 0.5) {
			controls->m_InputData.m_Jump = 1;
			state = HAMMER_READY;
		}
	} else if (state == HAMMER_READY) {
		BotUtil::moveTowards(controls, me->m_Pos.x, ATTACK_POS.x);
		if (me->m_HookState != HOOK_GRABBED || me->IsGrounded()) {
			done = true; // fail, try again
		} else if (distance(me->m_Pos, otherPlayer->m_Pos) < 55) {
			controls->m_InputData.m_Fire = 1;
			done = true; // hope that enemy went away
		}
	}
}