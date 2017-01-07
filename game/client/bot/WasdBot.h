#ifndef WASDBOT_H
#define WASDBOT_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>
#include "strategies/BotStrategy.h"
#include <list>

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
	
	std::list<class BotStrategy*> botStrategies;

};

#endif /* WASDBOT_H */