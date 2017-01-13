#ifndef STICKTOXPOSITIONSTRATEGY_H
#define STICKTOXPOSITIONSTRATEGY_H

#include "../BotStrategy.h"

class StickToXPositionStrategy : public BotStrategy {
public:

	StickToXPositionStrategy(CGameClient* client, float targetX);

	void execute(CControls* controls);

private:

	const int targetX;

};

#endif /* STICKTOXPOSITIONSTRATEGY_H */