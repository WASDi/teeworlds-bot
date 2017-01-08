#ifndef WASDBOT_H
#define WASDBOT_H

#include <game/gamecore.h>
#include "strategies/BotStrategy.h"
#include <list>

class WasdBot {
public:

	WasdBot(CGameClient* gameClient);

	void injectInput(CControls* controls);

	bool toggleEnabled();
	bool toggleDebug();

private:

	CGameClient* client;
	
	bool jumpedLastStep;
	bool enabled;
	bool debug;
	bool resetControlsNextFrame;
	
	std::list<class BotStrategy*> botStrategies;

};

#endif /* WASDBOT_H */