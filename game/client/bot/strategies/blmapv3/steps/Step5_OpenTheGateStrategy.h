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

	const static vec2 IDLE_POS;
	const static vec2 ATTACK_POS;
	const static int TARGET_POS_TOLERANCE = 8;

	void idle(CControls* controls);

	bool xInsideGateToggle(int x);

	bool avoidedDyingManouverLastFrame;
	void avoidDying(CControls* controls);

};

enum {
	IDLE,
	GO_TO_ATTACK,
	INIT_ATTACK,
	WAIT_FOR_SECOND_JUMP,
	HAMMER_READY,
	RETURN_TO_IDLE
};

#endif /* STEP5_OPENTHEGATESTRATEGY_H */

