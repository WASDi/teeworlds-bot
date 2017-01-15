#ifndef JUMPWHENSTUCKMOVINGSTRATEGY_H
#define JUMPWHENSTUCKMOVINGSTRATEGY_H

#include "../BotStrategy.h"

class JumpWhenStuckMovingStrategy : public BotStrategy {
	const static int PULSE_INTERVAL_MILLIS = 2000;

public:

	JumpWhenStuckMovingStrategy(CGameClient* client);

	void execute();

private:

	bool hasDirectionalInput();

	long pulseStartTime;
	vec2 posRecently;

	bool jumpedLastFrame;

};

#endif /* JUMPWHENSTUCKMOVINGSTRATEGY_H */

