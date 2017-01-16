#include "BotStrategy.h"

BotStrategy::BotStrategy(CGameClient* client) : client(client) {
}

bool BotStrategy::isFrozen() {
	return client->m_Snap.m_pLocalCharacter->m_Weapon == WEAPON_NINJA;
}

long BotStrategy::getNowMillis() {
	return time_get() / 1000;
}

CControls* BotStrategy::getControls() {
	return client->m_pControls;
}

CCharacterCore* BotStrategy::getPlayerHookingMe() {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (i == client->m_Snap.m_LocalClientID || !client->m_Snap.m_aCharacters[i].m_Active)
			continue;

		CCharacterCore* otherPlayer = &client->m_aClients[i].m_Predicted;
		if(otherPlayer->m_HookState == HOOK_GRABBED && otherPlayer->m_HookedPlayer == client->m_Snap.m_LocalClientID) {
			return otherPlayer;
		}
	}
	return 0;
}