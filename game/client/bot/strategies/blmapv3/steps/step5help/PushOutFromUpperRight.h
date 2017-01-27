#ifndef PUSHOUTFROMUPPERRIGHT_H
#define PUSHOUTFROMUPPERRIGHT_H

#include "../../../BotSubStrategy.h"

class PushOutFromUpperRight : public BotSubStrategy {
public:

	PushOutFromUpperRight(CControls* controls, CCharacterCore* me, CCharacterCore* otherPlayer);

	static bool applicable(vec2* pos);

	void executeInternal();

private:

	const static vec2 TARGET;
	const static vec2 PRE_TARGET;

};

#endif /* PUSHOUTFROMUPPERRIGHT_H */
