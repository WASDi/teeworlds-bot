#include "AutoKillWhenFrozenForTooLongStrategy.h"

AutoKillWhenFrozenForTooLongStrategy::AutoKillWhenFrozenForTooLongStrategy(CGameClient* client, long maxTimeMillis) :
BotStrategy(client),
maxTimeMillis(maxTimeMillis),
freezeStartTime(0) {
}

void AutoKillWhenFrozenForTooLongStrategy::execute(CControls* controls) {
	if (isFrozen()) {
		long nowMillis = getNowMillis();
		if (freezeStartTime == 0) {
			freezeStartTime = nowMillis;
		} else {
			long timeFrozen = nowMillis - freezeStartTime;
			if (timeFrozen > maxTimeMillis) {
				freezeStartTime = 0;
				client->SendKill(-1);
			}
		}
	} else {
		freezeStartTime = 0;
	}
}