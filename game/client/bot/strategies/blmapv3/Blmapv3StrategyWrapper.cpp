#include "Blmapv3StrategyWrapper.h"

#include "game/client/gameclient.h"
#include "Blmapv3StageResolver.h"
#include "game/client/bot/BotUtil.h"

#include "steps/steps.h"

Blmapv3StrategyWrapper::Blmapv3StrategyWrapper(CGameClient* client) : BotStrategy(client), lastStage(0) {
	// 4 steps to get to the chamber
	stages[0] = new Step1_MoveRightUnlessGateOpenStrategy(client);
	stages[1] = new Step2_GoFromFightingAreaToUpperAreaStrategy(client);
	stages[2] = new Step3_MoveThroughUpperAreaStrategy(client);
	stages[3] = new Step4_JumpUpToTheChamberStrategy(client);
	// final step: 
	stages[4] = new Step5_OpenTheGateStrategy(client);
}

void Blmapv3StrategyWrapper::execute() {
	if (isFrozen()) {
		BotUtil::resetInput(getControls());
		return;
	}

	vec2* pos = &client->m_PredictedChar.m_Pos;
	if (pos->x > 4200 || pos->y > 1300) {
		// It's easier to just respawn than to program return from this point
		client->SendKill(-1);
	}
	int stage = Blmapv3StageResolver::resolveStage(pos);
	if (stage != lastStage) {
		BotUtil::resetInput(getControls());
	}

	if (stage > 0 && stage <= NUM_STAGES) {
		// execute stage from 1 to NUM_STAGES
		stages[stage - 1]->execute();
	}

	lastStage = stage;
}