#ifndef BOTSTRATEGY_H
#define BOTSTRATEGY_H

#include <game/gamecore.h>
#include <game/client/components/controls.h>

class BotStrategy {
public:

	virtual void execute(CControls* controls) = 0;
	
	void resetInput(CControls* controls);

};

#endif /* BOTSTRATEGY_H */