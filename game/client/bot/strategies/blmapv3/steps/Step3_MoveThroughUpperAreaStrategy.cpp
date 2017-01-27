#include "Step3_MoveThroughUpperAreaStrategy.h"

#include "game/client/bot/BotUtil.h"

Step3_MoveThroughUpperAreaStrategy::Step3_MoveThroughUpperAreaStrategy(CGameClient* client) :
BotStrategy(client) {
}

const int Step3_MoveThroughUpperAreaStrategy::X_POS_TO_JUMP[] = {3180, 2800, 2550};

void Step3_MoveThroughUpperAreaStrategy::execute() {
	BotUtil::move(getControls(), MOVE_LEFT);
	getControls()->m_InputData.m_Jump = BotUtil::shouldJump(&client->m_PredictedChar.m_Pos, X_POS_TO_JUMP, N_JUMPS);
	if (client->m_PredictedChar.m_Pos.y > 500) {
		// down in a pothole, jump
		getControls()->m_InputData.m_Jump = client->m_PredictedChar.IsGrounded();
	}
}