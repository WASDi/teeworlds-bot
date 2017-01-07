#ifndef WASDBOT_H
#define WASDBOT_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>
#include "strategies/BotStrategy.h"

class WasdBot {
public:

    WasdBot();

	void injectInput(CControls *controls);

	bool toggleEnabled();
	bool toggleDebug();

	class CCharacterCore *player;

private:

	bool jumpedLastStep;
	bool enabled;
	bool debug;

	class BotStrategy *botStrategy;

};

#endif /* WASDBOT_H */