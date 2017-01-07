#ifndef BOTSTRATEGY_H
#define BOTSTRATEGY_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>

class BotStrategy {
public:

	BotStrategy(CGameClient* client);

	virtual void execute(CControls* controls) = 0;

	void resetInput(CControls* controls);

protected:

	CGameClient* client;

	bool isFrozen();


};

#endif /* BOTSTRATEGY_H */