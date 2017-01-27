#ifndef STEP5_OPENTHEGATESTRATEGY_H
#define STEP5_OPENTHEGATESTRATEGY_H

#include "../../BotStrategy.h"
#include "../../BotSubStrategy.h"

class Step5_OpenTheGateStrategy : public BotStrategy {
public:
	Step5_OpenTheGateStrategy(CGameClient* client);

	void execute();

private:

	int nemesisClientId;
	int state;

	const static vec2 IDLE_POS1;
	const static vec2 IDLE_POS2;
	const static long IDLE_POS_CYCLE_TIME = 10000;
	const static vec2 DANGEROUS_HOOKER_POS;
	const vec2* getDesiredIdlePos();

	const static int TARGET_POS_TOLERANCE = 16;

	void idle();
	void maybeHelpSomeone();

	bool insideGateToggle(vec2* pos);

	long avoidDyingUntil;
	void maybeAvoidDying();
	void toggleAvoidDying();

	BotSubStrategy* helpStrategy;
	BotSubStrategy* attackStrategy;

};

enum {
	IDLE,

	ATTACK_STRATEGY,

	RETURN_TO_IDLE,
	AVOID_DYING,
	HELPING
};

#endif /* STEP5_OPENTHEGATESTRATEGY_H */

