#include "JumpWhenStuckMovingStrategy.h"

JumpWhenStuckMovingStrategy::JumpWhenStuckMovingStrategy(CGameClient* client) :
BotStrategy(client),
inputStartTime(0) {
}

void JumpWhenStuckMovingStrategy::execute(CControls* controls) {
	if (hasDirectionalInput(controls)) {
		long nowMillis = time_get() / 1000;
		if (inputStartTime == 0) {
			inputStartTime = nowMillis;
			posOnInputStartTime = client->m_PredictedChar.m_Pos;
		} else {
			long millisSinceInput = nowMillis - inputStartTime;
			vec2 posNow = client->m_PredictedChar.m_Pos;
			//TODO IF millisSinceInput is high AND position near initial is far THEN jump
		}
	} else {
		inputStartTime = 0;
	}
}

bool JumpWhenStuckMovingStrategy::hasDirectionalInput(CControls* controls) {
	return controls->m_InputDirectionLeft != 0 &&
			controls->m_InputDirectionRight != 0;;
}

