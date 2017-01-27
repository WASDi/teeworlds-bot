#ifndef ATTACKFROMABOVE_H
#define ATTACKFROMABOVE_H

#include "../../../BotSubStrategy.h"

class AttackFromAbove : public BotSubStrategy {
public:

	AttackFromAbove(CControls* controls, CCharacterCore* me, CCharacterCore* otherPlayer);

	void executeInternal();

private:

	const static vec2 HOOK_POS;

	const static long INIT_WAIT_TIME = 900;
	const static long AFTER_HOOK_WAIT_TIME = 200;
	const static long ATTACK_FAILED_TIME = 1000;

	int state;

	long stateStartTime;

	void changeState(int newState);
	bool timeHasPassed(long timeSinceNewState);

};

enum {
	INIT_WAIT,
	HOOK_ENEMY,
	WAIT_AFTER_HOOK,
	POST_DOUBLE_JUMP
};

#endif /* ATTACKFROMABOVE_H */
