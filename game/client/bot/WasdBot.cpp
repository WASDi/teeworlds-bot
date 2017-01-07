#include "WasdBot.h"
#include "strategies/AutoKillWhenFrozenForTooLongStrategy.h"
#include "strategies/blmapv3/MoveToChamberStrategy.h"
#include <stdio.h>

WasdBot::WasdBot(CGameClient* client) :
client(client),
jumpedLastStep(false),
enabled(false),
debug(false) {
	botStrategies.push_back(new AutoKillWhenFrozenForTooLongStrategy(client, 10000));
	botStrategies.push_back(new MoveToChamberStrategy(client));
}

void WasdBot::injectInput(CControls *controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	if (!client->m_Snap.m_pLocalCharacter) {
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