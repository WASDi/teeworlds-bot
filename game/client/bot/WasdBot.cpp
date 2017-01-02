#include "WasdBot.h"
#include <game/client/components/controls.h>
#include "strategies/JumpWhenFallingStrategy.h"

#include <stdio.h>

WasdBot::WasdBot() {
	botStrategy = new JumpWhenFallingStrategy();
}

void WasdBot::injectInput(CControls *controls) {
	if (!player->readyForBot) {
		return;
	}
	botStrategy->execute(player, controls);
}