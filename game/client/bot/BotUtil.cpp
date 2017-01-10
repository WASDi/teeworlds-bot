#include "BotUtil.h"

void BotUtil::resetInput(CControls* controls) {
	controls->m_InputData.m_WantedWeapon = 1; // hammer
	controls->m_InputDirectionLeft = 0;
	controls->m_InputDirectionRight = 0;
	controls->m_InputData.m_Jump = 0;
	controls->m_InputData.m_Hook = 0;
	controls->m_InputData.m_Fire = 0;
}