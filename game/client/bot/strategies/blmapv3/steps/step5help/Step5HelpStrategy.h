#ifndef STEP5HELPSTRATEGY_H
#define STEP5HELPSTRATEGY_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>

class Step5HelpStrategy {
public:

	Step5HelpStrategy(CControls* controls, CCharacterCore* player, CCharacterCore* other);
	virtual ~Step5HelpStrategy();

	virtual void execute() = 0;
	bool isDone();
	
protected:
	
	bool done;
	
	CControls* controls;
	CCharacterCore* player;
	CCharacterCore* other;

};

#endif /* STEP5HELPSTRATEGY_H */

