#ifndef JUMPWHENFALLINGSTRATEGY_H
#define JUMPWHENFALLINGSTRATEGY_H

#include "BotStrategy.h"

class JumpWhenFallingStrategy : public BotStrategy {
public:

    void execute(CCharacterCore *player, CControls *controls);

private:
    bool jumpedLastStep;

};

#endif /* JUMPWHENFALLINGSTRATEGY_H */