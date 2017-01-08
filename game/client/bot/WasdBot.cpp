#include "WasdBot.h"
#include "strategies/AutoKillWhenFrozenForTooLongStrategy.h"
#include "strategies/JumpWhenStuckMovingStrategy.h"
#include "strategies/HammerNearbyPlayerStrategy.h"
#include "strategies/blmapv3/MoveToChamberStrategy.h"
#include <stdio.h>

WasdBot::WasdBot(CGameClient* client) :
client(client),
jumpedLastStep(false),
enabled(false),
debug(false),
resetControlsNextFrame(false) {
	/* TODO strategies: 
	 * HumanLikeMouseMovementStrategy - To appear more humanlike
	 * DoubleJumpIfAboveFreezeAreaStrategy - Can avoid being killed, perhaps only helps rarely
	 * AutoKillWhenNoBotInputRecievedForTooLongStrategy - If no strategy changes input for a long time, respawn
	 */
	botStrategies.push_back(new AutoKillWhenFrozenForTooLongStrategy(client, 10000));
	botStrategies.push_back(new MoveToChamberStrategy(client));
	botStrategies.push_back(new JumpWhenStuckMovingStrategy(client));
	botStrategies.push_back(new HammerNearbyPlayerStrategy(client));
}

void WasdBot::injectInput(CControls *controls) {
	if (!client->m_Snap.m_pLocalCharacter) {
		//TODO somehow "click" for faster respawn
		return;
	}
	if (debug) {
		CCharacterCore* player = &client->m_PredictedChar;
		printf("Pos+Vel : %7.2f %+6.2f : %7.2f %+6.2f\n", player->m_Pos.x, player->m_Vel.x, player->m_Pos.y, player->m_Vel.y);
		//printf("Aim %3d %3d\n", controls->m_InputData.m_TargetX, controls->m_InputData.m_TargetY);
		//printf("%4.0f %4.0f\n", controls->m_MousePos.x, controls->m_MousePos.y);
	}

	if (resetControlsNextFrame) {
		resetControlsNextFrame = false;
		//TODO deduplicate from BotStrategy::resetInput()
		controls->m_InputDirectionLeft = 0;
		controls->m_InputDirectionRight = 0;
		controls->m_InputData.m_Jump = 0;
		controls->m_InputData.m_Hook = 0;
	} else if (enabled) {
		for (std::list<BotStrategy*>::iterator it = botStrategies.begin(); it != botStrategies.end(); ++it) {
			BotStrategy* botStrategy = (*it);
			botStrategy->execute(controls);
		}
	}
}

bool WasdBot::toggleEnabled() {
	enabled = !enabled;
	if (!enabled) {
		resetControlsNextFrame = true;
	}
	return enabled;
}

bool WasdBot::toggleDebug() {
	return debug = !debug;
}