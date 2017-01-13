#ifndef STEP2_GOFROMFIGHTINGAREATOUPPERAREASTRATEGY_H
#define STEP2_GOFROMFIGHTINGAREATOUPPERAREASTRATEGY_H

#include "../../BotStrategy.h"

class Step2_GoFromFightingAreaToUpperAreaStrategy : public BotStrategy {
public:
	Step2_GoFromFightingAreaToUpperAreaStrategy(CGameClient* client);

	void execute(CControls* controls);

private:

	const static int CENTER_X = 3760; // middle of fight area

};

#endif /* STEP2_GOFROMFIGHTINGAREATOUPPERAREASTRATEGY_H */

