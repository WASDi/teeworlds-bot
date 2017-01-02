#include "WasdBot.h"
#include "strategies/JumpWhenFallingStrategy.h"
#include "strategies/StickToXPositionStrategy.h"
#include <game/client/components/controls.h>

WasdBot::WasdBot() {
	//botStrategy = new JumpWhenFallingStrategy();
	botStrategy = new StickToXPositionStrategy(1000);
}

void WasdBot::injectInput(CControls *controls) {
	if (!player->readyForBot) {
		return;
	}
	botStrategy->execute(player, controls);
}