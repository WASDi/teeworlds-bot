#ifndef PUSHOUTFROMUPPERRIGHT_H
#define PUSHOUTFROMUPPERRIGHT_H

#include "Step5HelpStrategy.h"

class PushOutFromUpperRight : public Step5HelpStrategy {
public:

	PushOutFromUpperRight(CControls* controls, CCharacterCore* player, CCharacterCore* other);

	static bool applicable(vec2* pos);
	
	void executeInternal();

private:
	
	const static vec2 TARGET;
	const static vec2 PRE_TARGET;

};

#endif /* PUSHOUTFROMUPPERRIGHT_H */
