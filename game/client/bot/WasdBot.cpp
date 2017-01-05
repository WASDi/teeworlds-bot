#include "WasdBot.h"
#include "strategies/JumpWhenFallingStrategy.h"
#include "strategies/StickToXPositionStrategy.h"
#include <game/client/components/controls.h>
#include <stdio.h>

WasdBot::WasdBot() : jumpedLastStep(false), enabled(false), debug(false) {
	//botStrategy = new JumpWhenFallingStrategy();
	botStrategy = new StickToXPositionStrategy(1000);
}

void WasdBot::injectInput(CControls *controls) {
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
		botStrategy->execute(player, controls);
	}
}

void WasdBot::toggleEnabled() {
	enabled = !enabled;
}

void WasdBot::toggleDebug() {
	debug = !debug;
}