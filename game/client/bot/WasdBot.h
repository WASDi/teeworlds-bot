#ifndef WASDBOT_H
#define WASDBOT_H

#include <game/gamecore.h>
#include <game/client/components/emoticon.h>
#include "strategies/BotStrategy.h"
#include <list>

class WasdBot {
public:

	WasdBot(CGameClient* gameClient, CEmoticon* emoticon);

	void injectInput();

	bool toggleEnabled();
	bool toggleDebug();

private:

	CGameClient* client;
	CEmoticon* emoticon;

	bool jumpedLastStep;
	bool enabled;
	bool debug;
	bool resetControlsNextFrame;

	std::list<class BotStrategy*> botStrategies;

};

#endif /* WASDBOT_H */