#ifndef JUMPWHENFALLINGSTRATEGY_H
#define JUMPWHENFALLINGSTRATEGY_H

#include "BotStrategy.h"

class JumpWhenFallingStrategy : public BotStrategy {
public:

	JumpWhenFallingStrategy(CGameClient* client);

	void execute(CControls *controls);

private:

	CGameClient* client;

	bool jumpedLastStep;

};

#endif /* JUMPWHENFALLINGSTRATEGY_H */