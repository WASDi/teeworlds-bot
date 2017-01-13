#ifndef STEP3_MOVETHROUGHUPPERAREASTRATEGY_H
#define STEP3_MOVETHROUGHUPPERAREASTRATEGY_H

#include "../../BotStrategy.h"

class Step3_MoveThroughUpperAreaStrategy : public BotStrategy {
public:
	Step3_MoveThroughUpperAreaStrategy(CGameClient* client);

	void execute(CControls* controls);

private:
	
	const static int N_JUMPS = 3;
	const static int X_POS_TO_JUMP[N_JUMPS];

};

#endif /* STEP3_MOVETHROUGHUPPERAREASTRATEGY_H */

