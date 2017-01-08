#include "JumpWhenStuckMovingStrategy.h"

JumpWhenStuckMovingStrategy::JumpWhenStuckMovingStrategy(CGameClient* client) :
BotStrategy(client),
pulseStartTime(0),
jumpedLastFrame(false) {
}

void JumpWhenStuckMovingStrategy::execute(CControls* controls) {
	if (isFrozen()) {
		// "AutoKillWhenFrozenForTooLongStrategy" handles this
		pulseStartTime = 0;
		return;
	}

	if (jumpedLastFrame) {
		controls->m_InputData.m_Jump = 0;
		pulseStartTime = 0;
		jumpedLastFrame = false;
	} else if (hasDirectionalInput(controls)) {
		long nowMillis = time_get() / 1000;
		if (pulseStartTime == 0) {
			pulseStartTime = nowMillis;
			posRecently = client->m_PredictedChar.m_Pos;
		} else {
			long millisSinceInput = nowMillis - pulseStartTime;
			if (millisSinceInput > PULSE_INTERVAL_MILLIS) {
				vec2 posNow = client->m_PredictedChar.m_Pos;
				float delta = fabs(posNow.x - posRecently.x) + fabs(posNow.y - posRecently.y);
				if (delta < 50) {
					// about the same state two pulses in a row, we think we are stuck
					controls->m_InputData.m_Jump = 1; //TODO if can't jump, do what?
					jumpedLastFrame = true;
				} else {
					//start new pulse
					pulseStartTime = nowMillis;
					posRecently = client->m_PredictedChar.m_Pos;
				}
			}
		}
	} else {
		pulseStartTime = 0;
	}
}

bool JumpWhenStuckMovingStrategy::hasDirectionalInput(CControls* controls) {
	return controls->m_InputDirectionLeft != 0 &&
			controls->m_InputDirectionRight != 0;
}

