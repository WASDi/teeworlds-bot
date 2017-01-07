#ifndef MOVETOCHAMBERSTRATEGY_H
#define MOVETOCHAMBERSTRATEGY_H

#include "../BotStrategy.h"

class MoveToChamberStrategy : public BotStrategy {
	const static int N_STAGE1_X_POS_TO_JUMP = 3;
	const static int STAGE1_X_POS_TO_JUMP[N_STAGE1_X_POS_TO_JUMP];
	const static int X_POS_JUMP_MARGIN = 32;

public:

	MoveToChamberStrategy(CGameClient* client);

	void execute(CControls* controls);

private:

	int lastStage;

	int resolveStage();

	void move(CControls *controls, int direction);
	int stage1ShouldJump();

};

enum {
	MOVE_LEFT,
	MOVE_RIGHT
};

#endif /* MOVETOCHAMBERSTRATEGY_H */