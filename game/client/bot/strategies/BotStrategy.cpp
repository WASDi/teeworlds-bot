#include "BotStrategy.h"

BotStrategy::BotStrategy(CGameClient* client) : client(client) {
}

bool BotStrategy::isFrozen() {
	return client->m_Snap.m_pLocalCharacter->m_Weapon == WEAPON_NINJA;
}

long BotStrategy::getNowMillis() {
	return time_get() / 1000;
}