#include "JumpWhenStuckMovingStrategy.h"

JumpWhenStuckMovingStrategy::JumpWhenStuckMovingStrategy(CGameClient* client) :
BotStrategy(client),
pulseStartTime(0),
jumpedLastFrame(false) {
}

void JumpWhenStuckMovingStrategy::execute() {
	if (isFrozen()) {
		// "AutoKillWhenFrozenForTooLongStrategy" handles this
		pulseStartTime = 0;
		return;
	}

	if (jumpedLastFrame) {
		getControls()->m_InputData.m_Jump = 0;
		pulseStartTime = 0;
		jumpedLastFrame = false;
	} else if (hasDirectionalInput()) {
		long nowMillis = getNowMillis();
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
					getControls()->m_InputData.m_Jump = 1; //TODO if can't jump, do what?
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

bool JumpWhenStuckMovingStrategy::hasDirectionalInput() {
	return getControls()->m_InputDirectionLeft != 0 ||
			getControls()->m_InputDirectionRight != 0;
}

