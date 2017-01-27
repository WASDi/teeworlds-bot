#ifndef BOTSUBSTRATEGY_H
#define BOTSUBSTRATEGY_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>

class BotSubStrategy {
public:

	BotSubStrategy(CControls* controls, CCharacterCore* player, CCharacterCore* other);
	virtual ~BotSubStrategy();

	void execute();

	bool isDone();

protected:

	bool done;

	CControls* controls;
	CCharacterCore* player;
	CCharacterCore* other;

	virtual void executeInternal() = 0;

};

#endif /* BOTSUBSTRATEGY_H */

