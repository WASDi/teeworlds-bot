#include "Step5_OpenTheGateStrategy.h"

Step5_OpenTheGateStrategy::Step5_OpenTheGateStrategy(CGameClient* client) :
BotStrategy(client) {
}

void Step5_OpenTheGateStrategy::execute(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	//TODO
}