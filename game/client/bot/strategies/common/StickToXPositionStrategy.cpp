#include "StickToXPositionStrategy.h"

StickToXPositionStrategy::StickToXPositionStrategy(CGameClient* client, float targetX) : BotStrategy(client), targetX(targetX) {
}

void StickToXPositionStrategy::execute() {
	CCharacterCore* player = &client->m_PredictedChar;

	const float sensitivity = 4;
	const float veloFactor = 2;

	float delta = player->m_Pos.x - this->targetX;
	float expectedNextDelta = delta + player->m_Vel.x * veloFactor;

	if (delta * expectedNextDelta < 0 && fabs(expectedNextDelta) < sensitivity) {
		//different signs AND not too severe movement
		return;
	}

	getControls()->m_InputDirectionRight = 0;
	getControls()->m_InputDirectionLeft = 0;

	if (expectedNextDelta < -sensitivity) {
		getControls()->m_InputDirectionRight = 1;
	} else if (expectedNextDelta > sensitivity) {
		getControls()->m_InputDirectionLeft = 1;
	}

}
