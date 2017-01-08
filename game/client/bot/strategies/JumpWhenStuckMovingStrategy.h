#ifndef JUMPWHENSTUCKMOVINGSTRATEGY_H
#define JUMPWHENSTUCKMOVINGSTRATEGY_H

#include "BotStrategy.h"

class JumpWhenStuckMovingStrategy : public BotStrategy {
public:

	JumpWhenStuckMovingStrategy(CGameClient* client);
	
	void execute(CControls* controls);

private:
	
	bool hasDirectionalInput(CControls* controls);
	
	long inputStartTime;
	vec2 posOnInputStartTime;

};

#endif /* JUMPWHENSTUCKMOVINGSTRATEGY_H */

