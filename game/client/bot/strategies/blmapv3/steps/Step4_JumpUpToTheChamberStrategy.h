#ifndef STEP4_JUMPUPTOTHECHAMBERSTRATEGY_H
#define STEP4_JUMPUPTOTHECHAMBERSTRATEGY_H

#include "../../BotStrategy.h"

class Step4_JumpUpToTheChamberStrategy : public BotStrategy {
public:
	Step4_JumpUpToTheChamberStrategy(CGameClient* client);

	void execute();

private:

	const static vec2 TARGET_POS;

};

#endif /* STEP4_JUMPUPTOTHECHAMBERSTRATEGY_H */

