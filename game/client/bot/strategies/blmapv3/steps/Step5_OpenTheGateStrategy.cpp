#include "Step5_OpenTheGateStrategy.h"
#include "game/client/bot/strategies/blmapv3/Blmapv3StageResolver.h"
#include "game/client/bot/BotUtil.h"

Step5_OpenTheGateStrategy::Step5_OpenTheGateStrategy(CGameClient* client) :
BotStrategy(client),
avoidedDyingManouverLastFrame(false) {
}

void Step5_OpenTheGateStrategy::execute(CControls* controls) {
	//CCharacterCore* player = &client->m_PredictedChar;

	bool dontAvoidDying = false;
	if (avoidedDyingManouverLastFrame) {
		BotUtil::resetInput(controls);
		avoidedDyingManouverLastFrame = false;
	}

	int myId = client->m_Snap.m_LocalClientID;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (i == myId || !client->m_Snap.m_aCharacters[i].m_Active)
			continue;

		CCharacterCore* otherPlayer = &client->m_aClients[i].m_Predicted;
		if (Blmapv3StageResolver::insideChamber(&otherPlayer->m_Pos)) {
			// enemy detected. If many enemies, cycle for 20 seconds each?
		}
	}

	if (!dontAvoidDying) {
		// end of method to override input unless disabled for frame
		avoidDying(controls);
	}
}

void Step5_OpenTheGateStrategy::avoidDying(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	vec2* currPos = &player->m_Pos;
	vec2 expectedPos = vec2(currPos->x + player->m_Vel.x * 10,
			currPos->y + player->m_Vel.y * 10);

	if (expectedPos.x > 1800) {
		//heading freeze zone to the right
		avoidedDyingManouverLastFrame = true;
		BotUtil::move(controls, MOVE_LEFT);
		//TODO hook up left
	} else if (expectedPos.x < 1440) {
		avoidedDyingManouverLastFrame = true;
		BotUtil::move(controls, MOVE_RIGHT);
		if (currPos->y > 689) {
			controls->m_InputData.m_Jump = 1;
		}
		//TODO hook up right
	} else if (Blmapv3StageResolver::insideChamberFreeze(&expectedPos)) {
		avoidedDyingManouverLastFrame = true;
		BotUtil::move(controls, MOVE_RIGHT);
		controls->m_MousePos.x = 100;
		controls->m_MousePos.y = 100;
		controls->m_InputData.m_Hook = 1;
		//TODO hook down right, use intersect to try not grab players
	}
}