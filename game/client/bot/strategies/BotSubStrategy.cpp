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
	} else if (/* other left game TODO*/0) {
		done = true;
		return;
	}
	else if (me->m_HookState == HOOK_GRABBED && me->m_HookedPlayer == -1) {
		// grabbed wall, not supposed to happen when helping
		controls->m_InputData.m_Hook = 0;
		done = true;
		return;
	}
	executeInternal();
}

bool BotSubStrategy::isDone() {
	return done;
}