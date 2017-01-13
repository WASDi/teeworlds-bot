#ifndef STEP5_OPENTHEGATESTRATEGY_H
#define STEP5_OPENTHEGATESTRATEGY_H

#include "../../BotStrategy.h"

class Step5_OpenTheGateStrategy : public BotStrategy {
public:
	Step5_OpenTheGateStrategy(CGameClient* client);

	void execute(CControls* controls);

private:
	
	bool avoidedDyingManouverLastFrame;
	void avoidDying(CControls* controls);

};

#endif /* STEP5_OPENTHEGATESTRATEGY_H */

