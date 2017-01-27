#include "BotSubStrategy.h"

BotSubStrategy::BotSubStrategy(CControls* controls, CCharacterCore* me, CCharacterCore* otherPlayer) :
done(false),
controls(controls),
me(me),
otherPlayer(otherPlayer) {
}

BotSubStrategy::~BotSubStrategy() {
}

void BotSubStrategy::execute() {
	if (isDone()) {
		return;
	} else if (/* TODO other left game */0) {
		done = true;
		return;
	}
	executeInternal();
}

bool BotSubStrategy::isDone() {
	return done;
}