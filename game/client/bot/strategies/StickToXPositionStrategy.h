#ifndef STICKTOXPOSITIONSTRATEGY_H
#define STICKTOXPOSITIONSTRATEGY_H

#include "BotStrategy.h"

class StickToXPositionStrategy : public BotStrategy {
public:
    StickToXPositionStrategy(float targetX);
    void execute(CCharacterCore *player, CControls *controls);

private:
    const int targetX;

};

#endif /* STICKTOXPOSITIONSTRATEGY_H */