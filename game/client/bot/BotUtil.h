#ifndef BOTUTIL_H
#define BOTUTIL_H

#include <game/client/components/controls.h>

class BotUtil {
	
public:
	
	static void resetInput(CControls* controls);
	
	static void move(CControls* controls, int direction);
	static void moveTowards(CControls *controls, int xPos, int xTarget);
	static void moveAwayFrom(CControls *controls, int xPos, int xTarget);
	
private:

};

enum {
	MOVE_LEFT,
	MOVE_RIGHT,
	DONT_MOVE
};

#endif /* BOTUTIL_H */

