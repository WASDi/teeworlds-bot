#ifndef AUTOKILLWHENFROZENFORTOOLONGSTRATEGY_H
#define AUTOKILLWHENFROZENFORTOOLONGSTRATEGY_H

#include "BotStrategy.h"

class AutoKillWhenFrozenForTooLongStrategy : public BotStrategy {
public:

	AutoKillWhenFrozenForTooLongStrategy(CGameClient* client, long maxTimeMillis);

	void execute(CControls *controls);

private:

	CGameClient* client;

	const long maxTimeMillis;
	long freezeStartTime;
	
	bool isFrozen();

};

#endif /* AUTOKILLWHENFROZENFORTOOLONGSTRATEGY_H */

