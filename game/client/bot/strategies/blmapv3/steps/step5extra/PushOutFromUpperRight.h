#ifndef PUSHOUTFROMUPPERRIGHT_H
#define PUSHOUTFROMUPPERRIGHT_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>

class PushOutFromUpperRight {
public:

	PushOutFromUpperRight();

	bool applicable(vec2* pos);
	void execute(CControls* controls, CCharacterCore* player, CCharacterCore* other);

private:

	const static vec2 TARGET;
	const static vec2 PRE_TARGET;

};

#endif /* PUSHOUTFROMUPPERRIGHT_H */
