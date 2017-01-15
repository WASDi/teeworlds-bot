#ifndef STEP5HELPSTRATEGY_H
#define STEP5HELPSTRATEGY_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>

class Step5HelpStrategy {
public:

	Step5HelpStrategy(CControls* controls, CCharacterCore* player, CCharacterCore* other);
	virtual ~Step5HelpStrategy();

	void execute();

	bool isDone();

protected:

	bool done;

	CControls* controls;
	CCharacterCore* player;
	CCharacterCore* other;

	virtual void executeInternal() = 0;

};

#endif /* STEP5HELPSTRATEGY_H */

