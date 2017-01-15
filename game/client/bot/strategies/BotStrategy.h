#ifndef BOTSTRATEGY_H
#define BOTSTRATEGY_H

#include <game/client/components/controls.h>
#include <game/client/gameclient.h>

class BotStrategy {
public:

	BotStrategy(CGameClient* client);

	virtual void execute() = 0;

protected:

	CGameClient* client;

	bool isFrozen();

	long getNowMillis();
	
	CControls* getControls();

};

#endif /* BOTSTRATEGY_H */