#include "Step2_GoFromFightingAreaToUpperAreaStrategy.h"

#include "game/client/bot/BotUtil.h"

Step2_GoFromFightingAreaToUpperAreaStrategy::Step2_GoFromFightingAreaToUpperAreaStrategy(CGameClient* client) :
BotStrategy(client) {
}

void Step2_GoFromFightingAreaToUpperAreaStrategy::execute(CControls* controls) {
	CCharacterCore* player = &client->m_PredictedChar;
	vec2 pos = player->m_Pos;

	bool rightFromCenter = pos.x > CENTER_X;
	int inv = rightFromCenter ? 1 : -1;

	bool inTheMiddleY = pos.y >= 846 && pos.y <= 945;
	bool hookedToDesiredSpot =
			player->m_HookState == HOOK_GRABBED &&
			player->m_HookPos.y > 500 &&
			player->m_HookPos.y < 545 &&
			(
			(player->m_HookPos.x > CENTER_X - 460 && player->m_HookPos.x < CENTER_X - 160) ||
			(player->m_HookPos.x > CENTER_X + 160 && player->m_HookPos.x < CENTER_X + 460)
			);

	if (hookedToDesiredSpot) {
		if (inTheMiddleY) {
			BotUtil::moveTowards(controls, pos.x, CENTER_X); // move to center
		} else if (rightFromCenter ? pos.x > CENTER_X + 180 : pos.x < CENTER_X - 180) {
			//near the upper traps, escape
			controls->m_InputData.m_Hook = 0;
			BotUtil::moveAwayFrom(controls, pos.x, CENTER_X);
		}
	} else {
		if (player->m_HookState == HOOK_RETRACTED) {
			controls->m_InputData.m_Hook = 0;
		}
		int targetX = CENTER_X + 210 * inv;
		if (inTheMiddleY) {
			targetX -= 25 * inv; // move target closer to center
		}
		float absDelta = fabs(pos.x - targetX);
		if (absDelta > 5) {
			BotUtil::moveTowards(controls, pos.x, targetX);
		} else {
			BotUtil::move(controls, DONT_MOVE);
			// aim hook up and a little outwards
			controls->m_MousePos.x = 10 * inv;
			controls->m_MousePos.y = -100;

			// maybe jump
			bool canDoubleJump = !(player->m_Jumped & 2);
			controls->m_InputData.m_Jump = pos.y > 850 && ((canDoubleJump && player->m_Vel.y > 5) || player->IsGrounded());

			if (inTheMiddleY && pos.y <= 900) {
				// HOOK
				controls->m_InputData.m_Hook = 1;
			}
		}
	}
}