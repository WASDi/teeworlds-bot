#ifndef BOTSUBSTRATEGY_H
#define BOTSUBSTRATEGY_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>

class BotSubStrategy {
public:

	BotSubStrategy(CControls* controls, CCharacterCore* me, CCharacterCore* otherPlayer);
	virtual ~BotSubStrategy();

	void execute();

	bool isDone();

protected:

	bool done;

	CControls* controls;
	CCharacterCore* me;
	CCharacterCore* otherPlayer;

	virtual void executeInternal() = 0;

};

#endif /* BOTSUBSTRATEGY_H */

