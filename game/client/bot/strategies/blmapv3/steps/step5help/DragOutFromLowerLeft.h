#ifndef DRAGOUTFROMLOWERLEFT_H
#define DRAGOUTFROMLOWERLEFT_H

#include "Step5HelpStrategy.h"

class DragOutFromLowerLeft : public Step5HelpStrategy {
public:

	DragOutFromLowerLeft(CControls* controls, CCharacterCore* player, CCharacterCore* other);

	static bool applicable(vec2* pos);

	void executeInternal();

private:

	const static int LEFT_BOUNDARY = 1390;
	const static int RIGHT_BOUNDARY = 1471;
	const static int DANGEROUS_THRESHOLD = 1435;
	
	const static int Y_MIN = 750;
	const static int LOWER_BOUNDARY = 785;

	const static vec2 PRE_START_POS;
	const static vec2 START_POS;

	int state;

};

enum {
	PRE_INIT, // move to pre pos
	MOVE_TO_START_POS, // then jump when not moving
	JUMPED, // wait until velocity is downwards

	FALLING_HOOKING, // Move right, when other player outside boundary, release hook
	DANGEROUS_FALLING, // started falling, move left. When reached target y, hook player, jump, go to FALLING
};

#endif /* DRAGOUTFROMLOWERLEFT_H */