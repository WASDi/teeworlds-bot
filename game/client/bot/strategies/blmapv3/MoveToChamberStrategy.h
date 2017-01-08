#ifndef MOVETOCHAMBERSTRATEGY_H
#define MOVETOCHAMBERSTRATEGY_H

#include "../BotStrategy.h"

class MoveToChamberStrategy : public BotStrategy {
	const static int N_JUMPS_STAGE_1 = 3;
	const static int STAGE1_X_POS_TO_JUMP[N_JUMPS_STAGE_1];

	const static int N_JUMPS_STAGE_2 = 3;
	const static int STAGE2_X_POS_TO_JUMP[N_JUMPS_STAGE_2];

	const static int X_POS_JUMP_MARGIN = 32;
	
	const static vec4 UPPER_STAIRS_COORDINATES;
	const static vec4 LOWER_STAIRS_COORDINATES;

public:

	MoveToChamberStrategy(CGameClient* client);

	void execute(CControls* controls);

private:

	int lastStage;

	int resolveStage();

	void goFromFightingAreaToUpperArea(CControls* controls);
	void moveThroughUpperArea(CControls* controls);

	void move(CControls* controls, int direction);
	int shouldJump(const int* posXJumps, const int length);
	
	bool aboveLine(vec2 pos, vec4 lineData);

};

enum {
	MOVE_LEFT,
	MOVE_RIGHT,
	DONT_MOVE
};

#endif /* MOVETOCHAMBERSTRATEGY_H */