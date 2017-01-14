#ifndef STEP5_OPENTHEGATESTRATEGY_H
#define STEP5_OPENTHEGATESTRATEGY_H

#include "../../BotStrategy.h"

class Step5_OpenTheGateStrategy : public BotStrategy {
public:
	Step5_OpenTheGateStrategy(CGameClient* client);

	void execute(CControls* controls);

private:

	int nemesisClientId;
	int state;

	const static vec2 IDLE_POS1;
	const static vec2 IDLE_POS2;
	const static long IDLE_POS_CYCLE_TIME = 10000;
	vec2* getDesiredIdlePos();

	const static vec2 ATTACK_POS;
	const static int TARGET_POS_TOLERANCE = 14;

	void idle(CControls* controls);

	bool insideGateToggle(vec2* pos);

	long avoidDyingUntil;
	void maybeAvoidDying(CControls* controls);
	void toggleAvoidDying();

};

enum {
	IDLE,
	GO_TO_ATTACK,
	INIT_ATTACK,
	WAIT_FOR_SECOND_JUMP,
	HAMMER_READY,
	RETURN_TO_IDLE,
	AVOID_DYING
};

#endif /* STEP5_OPENTHEGATESTRATEGY_H */

