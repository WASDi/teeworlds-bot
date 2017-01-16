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
	else if (player->m_HookState == HOOK_GRABBED && player->m_HookedPlayer == -1) {
		// grabbed wall, not supposed to happen when helping
		controls->m_InputData.m_Hook = 0;
		done = true;
		return;
	}
	executeInternal();
}

bool Step5HelpStrategy::isDone() {
	return done;
}