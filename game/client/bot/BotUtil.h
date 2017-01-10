#ifndef BOTUTIL_H
#define BOTUTIL_H

#include <game/client/components/controls.h>

class BotUtil {
	
public:

	static void resetInput(CControls* controls);

	static void move(CControls* controls, int direction);
	static void moveTowards(CControls *controls, int xPos, int xTarget);
	static void moveAwayFrom(CControls *controls, int xPos, int xTarget);

	static bool shouldJump(vec2* pos, const int* posXJumps, const int arrLength);

private:

	const static int X_POS_JUMP_MARGIN = 32;

};

enum {
	MOVE_LEFT,
	MOVE_RIGHT,
	DONT_MOVE
};

#endif /* BOTUTIL_H */

