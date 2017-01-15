#ifndef STEP5HELPSTRATEGY_H
#define STEP5HELPSTRATEGY_H

class Step5HelpStrategy {
public:

	Step5HelpStrategy();
	virtual ~Step5HelpStrategy();

	virtual void execute() = 0;
	bool isDone();
	
protected:
	
	bool done;

};

#endif /* STEP5HELPSTRATEGY_H */

