#include "WasdBot.h"
#include "strategies/JumpWhenFallingStrategy.h"
//#include "strategies/AutoKillWhenFrozenForTooLongStrategy.h"
#include <stdio.h>

WasdBot::WasdBot(CGameClient* client) : client(client), jumpedLastStep(false), enabled(false), debug(false) {
	botStrategies.push_back(new JumpWhenFallingStrategy(client));
	//botStrategies.push_back(new AutoKillWhenFrozenForTooLongStrategy(client, 1000));
}

void WasdBot::injectInput(CControls *controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	if (!player->readyForBot) {
		return;
	}
	if (debug) {
		printf("%7.2f %+6.2f : %7.2f %+6.2f\n",
				player->m_Pos.x,
				player->m_Vel.x,
				player->m_Pos.y,
				player->m_Vel.y);
	}
	
	if (enabled) {
		for (std::list<BotStrategy*>::iterator it = botStrategies.begin(); it != botStrategies.end(); ++it) {
			BotStrategy* botStrategy = (*it);
			botStrategy->execute(controls);
		}
	}
}

bool WasdBot::toggleEnabled() {
	enabled = !enabled;
	if (!enabled) {
		//TODO reset controls
	}
	return enabled;
}

bool WasdBot::toggleDebug() {
	return debug = !debug;
}