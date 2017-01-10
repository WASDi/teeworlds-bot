#include "BotUtil.h"

void BotUtil::resetInput(CControls* controls) {
	controls->m_InputData.m_WantedWeapon = 1; // hammer //TODO should we do this?
	controls->m_InputDirectionLeft = 0;
	controls->m_InputDirectionRight = 0;
	controls->m_InputData.m_Jump = 0;
	controls->m_InputData.m_Hook = 0;
	controls->m_InputData.m_Fire = 0;
}

void BotUtil::move(CControls* controls, int directon) {
	if (directon == DONT_MOVE) {
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

void BotUtil::moveTowards(CControls* controls, int xPos, int xTarget) {
	if (xPos == xTarget) {
		move(controls, DONT_MOVE);
	} else {
		move(controls, xPos < xTarget ? MOVE_RIGHT : MOVE_LEFT);
	}

}

void BotUtil::moveAwayFrom(CControls* controls, int xPos, int xAvoid) {
	move(controls, xPos > xAvoid ? MOVE_RIGHT : MOVE_LEFT);
}

bool BotUtil::shouldJump(vec2* pos, const int* posXJumps, const int arrLength) {
	for (int i = 0; i < arrLength; i++) {
		int xPos = posXJumps[i];
		if (fabs(pos->x - xPos) < X_POS_JUMP_MARGIN) {
			return true;
		}
	}
	return false;

}