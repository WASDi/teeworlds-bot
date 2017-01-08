#ifndef HAMMERNEARBYPLAYERSTRATEGY_H
#define HAMMERNEARBYPLAYERSTRATEGY_H

#include "BotStrategy.h"

class HammerNearbyPlayerStrategy : public BotStrategy {
public:

	HammerNearbyPlayerStrategy(CGameClient* client);

	void execute(CControls* controls);

private:
	
	long attackedLastFrame;
	long attackTime;
	
	void attack(CControls* controls, vec2* targetPos);

};

#endif /* HAMMERNEARBYPLAYERSTRATEGY_H */

