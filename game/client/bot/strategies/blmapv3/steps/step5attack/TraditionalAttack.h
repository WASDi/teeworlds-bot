#ifndef TRADITIONALATTACK_H
#define TRADITIONALATTACK_H

#include "../../../BotSubStrategy.h"

class TraditionalAttack : public BotSubStrategy {
public:

	const static vec2 ATTACK_POS;

	TraditionalAttack(CControls* controls, CCharacterCore* me, CCharacterCore* otherPlayer);

	void executeInternal();

private:


	int state;

};

enum {
	INIT_ATTACK,
	WAIT_FOR_SECOND_JUMP,
	HAMMER_READY
};

#endif /* TRADITIONALATTACK_H */

