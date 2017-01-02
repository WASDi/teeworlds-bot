#include <game/gamecore.h>
#include "components/controls.h"

#ifndef WASDBOT_H
#define WASDBOT_H

class WasdBot {
    
public:
    
    WasdBot();
    
    void injectInput(CControls *controls);
    
    class CCharacterCore *player;
    
private:
    
    bool jumpedLastStep;

};

#endif /* WASDBOT_H */

