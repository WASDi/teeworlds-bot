#ifndef JUMPWHENSTUCKMOVINGSTRATEGY_H
#define JUMPWHENSTUCKMOVINGSTRATEGY_H

#include "BotStrategy.h"

class JumpWhenStuckMovingStrategy : public BotStrategy {
	const static int PULSE_INTERVAL_MILLIS = 2500;

public:

	JumpWhenStuckMovingStrategy(CGameClient* client);

	void execute(CControls* controls);

private:

	bool hasDirectionalInput(CControls* controls);

	long pulseStartTime;
	vec2 posRecently;

	bool jumpedLastFrame;

};

#endif /* JUMPWHENSTUCKMOVINGSTRATEGY_H */

