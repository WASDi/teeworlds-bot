#include "AutoKillWhenFrozenForTooLongStrategy.h"

AutoKillWhenFrozenForTooLongStrategy::AutoKillWhenFrozenForTooLongStrategy(CGameClient* client, long maxTimeMillis) :
client(client),
maxTimeMillis(maxTimeMillis),
freezeStartTime(0) {
}

void AutoKillWhenFrozenForTooLongStrategy::execute(CControls *controls) {
	if (isFrozen()) {
		long nowMillis = time_get() / 1000;
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

bool AutoKillWhenFrozenForTooLongStrategy::isFrozen() {
	return client->m_Snap.m_pLocalCharacter->m_Weapon == WEAPON_NINJA;
}