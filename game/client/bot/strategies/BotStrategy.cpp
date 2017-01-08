#include "BotStrategy.h"

BotStrategy::BotStrategy(CGameClient* client) : client(client) {
}

void BotStrategy::resetInput(CControls* controls) {
	controls->m_InputData.m_WantedWeapon = 1; // hammer
	controls->m_InputDirectionLeft = 0;
	controls->m_InputDirectionRight = 0;
	controls->m_InputData.m_Jump = 0;
	controls->m_InputData.m_Hook = 0;
}

bool BotStrategy::isFrozen() {
	return client->m_Snap.m_pLocalCharacter->m_Weapon == WEAPON_NINJA;
}

long BotStrategy::getNowMillis() {
	return time_get() / 1000;
}