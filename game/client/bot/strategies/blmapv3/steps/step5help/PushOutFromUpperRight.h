#ifndef PUSHOUTFROMUPPERRIGHT_H
#define PUSHOUTFROMUPPERRIGHT_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>

#include "Step5HelpStrategy.h"

class PushOutFromUpperRight : public Step5HelpStrategy {
public:

	PushOutFromUpperRight(CControls* controls, CCharacterCore* player, CCharacterCore* other);

	static bool applicable(vec2* pos);
	
	void execute();

private:
	
	const static vec2 TARGET;
	const static vec2 PRE_TARGET;
	
	CControls* controls;
	CCharacterCore* player;
	CCharacterCore* other;

};

#endif /* PUSHOUTFROMUPPERRIGHT_H */
