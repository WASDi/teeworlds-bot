#include "HammerNearbyPlayerStrategy.h"

HammerNearbyPlayerStrategy::HammerNearbyPlayerStrategy(CGameClient* client) :
BotStrategy(client),
attackedLastFrame(false),
attackTime(0) {
}

void HammerNearbyPlayerStrategy::execute() {
	if (attackedLastFrame) {
		getControls()->m_InputData.m_Fire = 0;
		attackedLastFrame = false;
		return;
	}
	if (getNowMillis() < attackTime + 1000) {
		//attack max once per second
		return;
	}
	CCharacterCore* me = &client->m_PredictedChar;
	int myId = client->m_Snap.m_LocalClientID;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (i == myId || !client->m_Snap.m_aCharacters[i].m_Active)
			continue;

		CCharacterCore* otherPlayer = &client->m_aClients[i].m_Predicted;
		float distanceToOtherPlayer = distance(me->m_Pos, otherPlayer->m_Pos);
		if (distanceToOtherPlayer < 50) {
			attack(&otherPlayer->m_Pos);
			return;
		}
	}

}

void HammerNearbyPlayerStrategy::attack(vec2* targetPos) {
	vec2* myPos = &client->m_PredictedChar.m_Pos;
	getControls()->m_InputData.m_WantedWeapon = 1; //hammer
	getControls()->m_InputData.m_Fire = 1;
	getControls()->m_MousePos.x = targetPos->x - myPos->x;
	getControls()->m_MousePos.y = targetPos->y - myPos->y;
	attackedLastFrame = true;
	attackTime = getNowMillis();
}