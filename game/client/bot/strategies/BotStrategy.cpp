#include "BotStrategy.h"

void BotStrategy::resetInput(CControls* controls) {
	controls->m_InputDirectionLeft = 0;
	controls->m_InputDirectionRight = 0;
	controls->m_InputData.m_Jump = 0;
}
