#ifndef BLMAPV3STRATEGYWRAPPER_H
#define BLMAPV3STRATEGYWRAPPER_H

#include "../BotStrategy.h"

class Blmapv3StrategyWrapper : public BotStrategy {
	
public:
	
	Blmapv3StrategyWrapper(CGameClient* client);
	
	void execute(CControls* controls);

private:

	int lastStage;

	const static int NUM_STAGES = 5;
	BotStrategy* stages[NUM_STAGES];

};

#endif /* BLMAPV3STRATEGYWRAPPER_H */

