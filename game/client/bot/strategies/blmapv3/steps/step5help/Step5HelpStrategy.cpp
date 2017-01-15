#include "Step5HelpStrategy.h"

Step5HelpStrategy::Step5HelpStrategy(CControls* controls, CCharacterCore* player, CCharacterCore* other) :
done(false),
controls(controls),
player(player),
other(other) {
}

Step5HelpStrategy::~Step5HelpStrategy() {
}

void Step5HelpStrategy::execute() {
	if (isDone()) {
		return;
	} else if (/* other left game TODO*/0) {
		done = true;
		return;
	}
	executeInternal();
}

bool Step5HelpStrategy::isDone() {
	return done;
}