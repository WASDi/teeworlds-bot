#include "PushOutFromUpperRight.h"

#include "../../../../BotUtil.h"

PushOutFromUpperRight::PushOutFromUpperRight(CControls* controls, CCharacterCore* player, CCharacterCore* other) :
Step5HelpStrategy(controls, player, other) {
}

bool PushOutFromUpperRight::applicable(vec2* pos) {
	return pos->x >= 1824 && pos->x < 1888 && pos->y == 497;
}

const vec2 PushOutFromUpperRight::TARGET = vec2(1809, 529);
const vec2 PushOutFromUpperRight::PRE_TARGET = vec2(TARGET.x - 48, TARGET.y);

void PushOutFromUpperRight::executeInternal() {
	if(!applicable(&other->m_Pos)) {
		done = true;
		return;
	}
	if (player->m_Pos.x == TARGET.x) {
		if (player->m_Pos.y == TARGET.y) {
			controls->m_MousePos.x = 200;
			controls->m_MousePos.y = -100;
			if (distance(player->m_Pos, other->m_Pos) < 60) {
				controls->m_InputData.m_Hook = 0;
				controls->m_InputData.m_Jump = 1;
			} else {
				controls->m_InputData.m_Hook = player->m_HookState != HOOK_RETRACTED;
			}
		} else if (player->m_Pos.y < TARGET.y - 32) {
			//has jumped high enough, attack!
			controls->m_MousePos.x = 100;
			controls->m_MousePos.y = 0;
			controls->m_InputData.m_Fire = 1;
			BotUtil::move(controls, MOVE_LEFT);
			done = true;
		} else {
			//in air, not high enough
			controls->m_InputData.m_Jump = 0;
		}

	} else {
		controls->m_InputData.m_Hook = 0;
		controls->m_InputData.m_Fire = 0;
		// Move to "pre target" with jump, then walk safely
		if (player->m_Pos.x < PRE_TARGET.x || player->m_Pos.y < TARGET.y) {
			BotUtil::moveTowardsWithJump(controls, player, &PRE_TARGET, true);
		} else {
			BotUtil::moveTowards(controls, player->m_Pos.x, TARGET.x);
		}
	}
}