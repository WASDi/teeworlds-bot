#include "Step5HelpStrategy.h"

Step5HelpStrategy::Step5HelpStrategy(CControls* controls, CCharacterCore* player, CCharacterCore* other) :
done(false),
controls(controls),
player(player),
other(other) {
}

Step5HelpStrategy::~Step5HelpStrategy() {
}

bool Step5HelpStrategy::isDone() {
	return done;
}