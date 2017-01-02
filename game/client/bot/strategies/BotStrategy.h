#include <game/gamecore.h>
#include <game/client/components/controls.h>

#include <stdio.h>

#ifndef BOTSTRATEGY_H
#define BOTSTRATEGY_H

class BotStrategy {
public:

    virtual void execute(CCharacterCore *player, CControls *controls) = 0;

};

#endif /* BOTSTRATEGY_H */

