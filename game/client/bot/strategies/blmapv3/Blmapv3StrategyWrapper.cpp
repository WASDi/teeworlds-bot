#include "Blmapv3StrategyWrapper.h"

#include "game/client/gameclient.h"
#include "MoveToChamberStrategy.h"
#include "Blmapv3StageResolver.h"
#include "../../BotUtil.h"

Blmapv3StrategyWrapper::Blmapv3StrategyWrapper(CGameClient* client) : BotStrategy(client), lastStage(0) {
	// 4 steps to get to the chamber
	//strategies[0] = new Step1_MoveRightUnlessGateOpenStrategy(client);
	//strategies[1] = new Step2_GoFromFightingAreaToUpperAreaStrategy(client);
	//strategies[2] = new Step3_MoveThroughUpperAreaStrategy(client);
	//strategies[3] = new Step4_JumpToBehindTheChamberStrategy(client);
	// final step: 
	//strategies[4] = new Step5_OpenTheGateStrategy(client);
}

void Blmapv3StrategyWrapper::execute(CControls* controls) {
	if (isFrozen()) {
		BotUtil::resetInput(controls);
		return;
	}

	vec2* pos = &client->m_PredictedChar.m_Pos;
	if (pos->x > 4200 || pos->y > 1300) {
		// It's easier to just respawn than to program return from this point
		client->SendKill(-1);
	}
	int stage = Blmapv3StageResolver::resolveStage(&pos);
	if (stage != lastStage) {
		BotUtil::resetInput(controls);
	}

	if (stage != 0) {
		// zero indexed
		strategies[stage - 1]->execute(controls);
	}

	lastStage = stage;
}