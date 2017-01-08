#include "WasdBot.h"
#include "strategies/AutoKillWhenFrozenForTooLongStrategy.h"
#include "strategies/JumpWhenStuckMovingStrategy.h"
#include "strategies/blmapv3/MoveToChamberStrategy.h"
#include <stdio.h>

WasdBot::WasdBot(CGameClient* client) :
client(client),
jumpedLastStep(false),
enabled(false),
debug(false),
resetControlsNextFrame(false) {
	//botStrategies.push_back(new HumanLikeMouseMovementStrategy(client)); //TODO, do first as others may override
	botStrategies.push_back(new AutoKillWhenFrozenForTooLongStrategy(client, 10000));
	botStrategies.push_back(new MoveToChamberStrategy(client));
	//botStrategies.push_back(new DoubleJumpIfAboveFreezeAreaStrategy(client)); // might be good, run later to override other jump behaviour
	//botStrategies.push_back(new AutoKillWhenNoBotInputRecievedForTooLongStrategy(client, 30000)); //TODO, in case of failure. LOG POSITION
	botStrategies.push_back(new JumpWhenStuckMovingStrategy(client));
}

void WasdBot::injectInput(CControls *controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	if (!client->m_Snap.m_pLocalCharacter) {
		//TODO somehow "click" for faster respawn
		return;
	}
	if (debug) {
		printf("Pos+Vel : %7.2f %+6.2f : %7.2f %+6.2f\n",
				player->m_Pos.x,
				player->m_Vel.x,
				player->m_Pos.y,
				player->m_Vel.y);
	}

	if (resetControlsNextFrame) {
		resetControlsNextFrame = false;
		//TODO deduplicate from BotStrategy::resetInput()
		controls->m_InputDirectionLeft = 0;
		controls->m_InputDirectionRight = 0;
		controls->m_InputData.m_Jump = 0;
		controls->m_InputData.m_Hook = 0;
	} else if (enabled) {
		for (std::list<BotStrategy*>::iterator it = botStrategies.begin(); it != botStrategies.end(); ++it) {
			BotStrategy* botStrategy = (*it);
			botStrategy->execute(controls);
		}
	}
}

bool WasdBot::toggleEnabled() {
	enabled = !enabled;
	if (!enabled) {
		resetControlsNextFrame = true;
	}
	return enabled;
}

bool WasdBot::toggleDebug() {
	return debug = !debug;
}