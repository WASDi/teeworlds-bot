#include <game/gamecore.h>
#include <game/client/components/controls.h>

#include "strategies/BotStrategy.h"

#ifndef WASDBOT_H
#define WASDBOT_H

class WasdBot {
public:

    WasdBot();

    void injectInput(CControls *controls);

    class CCharacterCore *player;

private:

    bool jumpedLastStep;

    class BotStrategy *botStrategy;

};

#endif /* WASDBOT_H */

