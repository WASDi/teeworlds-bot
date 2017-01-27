#include "Step1_MoveRightUnlessGateOpenStrategy.h"
#include "game/client/bot/BotUtil.h"
#include "../Blmapv3Util.h"

Step1_MoveRightUnlessGateOpenStrategy::Step1_MoveRightUnlessGateOpenStrategy(CGameClient* client) :
BotStrategy(client) {
}

const int Step1_MoveRightUnlessGateOpenStrategy::X_POS_TO_JUMP[] = {2200, 2400, 2725, 3050};

void Step1_MoveRightUnlessGateOpenStrategy::execute() {
	CCharacterCore* player = &client->m_PredictedChar;

	bool tooLateToMoveBack = player->m_Pos.x > 1900;
	//TODO if player blocking the gate is reachable from bellow and not hooking, grab him away
	if (!tooLateToMoveBack && Blmapv3Util::isGateOpen(client)) {
		float absDelta = fabs(GATE_X_POS - player->m_Pos.x);
		if (absDelta > 10) {
			BotUtil::moveTowards(getControls(), player->m_Pos.x, GATE_X_POS);
			getControls()->m_InputData.m_Hook = 0;
		}

		if (player->m_HookState == HOOK_GRABBED && player->m_HookPos.y > 950) {
			//accidentally hooked too low
			getControls()->m_InputData.m_Hook = 0;
		} else if (absDelta < 20) {
			//close enough, jump and hook
			getControls()->m_InputData.m_Jump = player->IsGrounded();
			getControls()->m_MousePos.x = 0;
			getControls()->m_MousePos.y = -100;
			getControls()->m_InputData.m_Hook = player->m_HookState != HOOK_RETRACTED; //always hook, rehook if retracted
		}
	} else {
		//TODO hook the ceiling. Often falls down when jumping near other players
		BotUtil::move(getControls(), MOVE_RIGHT);
		getControls()->m_InputData.m_Jump = BotUtil::shouldJump(&player->m_Pos, X_POS_TO_JUMP, N_JUMPS);
	}
}