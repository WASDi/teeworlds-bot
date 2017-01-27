#include "AttackFromAbove.h"

#include "../../../../BotUtil.h"

AttackFromAbove::AttackFromAbove(CControls* controls, CCharacterCore* me, CCharacterCore* otherPlayer) :
BotSubStrategy(controls, me, otherPlayer),
state(INIT_WAIT),
stateStartTime(0) {
}

const vec2 AttackFromAbove::HOOK_POS = vec2(1536 + 16, 416);

void AttackFromAbove::executeInternal() {
	if (stateStartTime == 0) {
		stateStartTime = BotUtil::getNowMillis();
	}

	if (state == INIT_WAIT) {
		controls->m_MousePos.x = HOOK_POS.x - me->m_Pos.x;
		controls->m_MousePos.y = HOOK_POS.y - me->m_Pos.y;
		controls->m_InputData.m_Hook = 1;
		if (timeHasPassed(INIT_WAIT_TIME)) {
			changeState(HOOK_ENEMY);
			controls->m_InputData.m_Hook = 0;
		}
	} else if (state == HOOK_ENEMY) {
		controls->m_MousePos.x = otherPlayer->m_Pos.x - me->m_Pos.x;
		controls->m_MousePos.y = otherPlayer->m_Pos.y - me->m_Pos.y;
		controls->m_InputData.m_Hook = 1;
		changeState(WAIT_AFTER_HOOK);
	} else if (state == WAIT_AFTER_HOOK) {
		if (timeHasPassed(AFTER_HOOK_WAIT_TIME)) {
			controls->m_InputData.m_Jump = 1;
			changeState(POST_DOUBLE_JUMP);
		}
	} else if (state == POST_DOUBLE_JUMP) {
		controls->m_InputData.m_Jump = 0;
		if (distance(me->m_Pos, otherPlayer->m_Pos) < 60 || timeHasPassed(ATTACK_FAILED_TIME)) {
			controls->m_InputData.m_Fire = 1;
			done = true;
		}
	}
}

void AttackFromAbove::changeState(int newState) {
	state = newState;
	stateStartTime = BotUtil::getNowMillis();
}

bool AttackFromAbove::timeHasPassed(long timeSinceNewState) {
	return BotUtil::getNowMillis() > stateStartTime + timeSinceNewState;
}