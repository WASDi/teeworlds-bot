#include "MoveToChamberStrategy.h"

MoveToChamberStrategy::MoveToChamberStrategy(CGameClient* client) : client(client), lastStage(0) {
}

void MoveToChamberStrategy::execute(CControls *controls) {
	int stage = resolveStage();
	if (stage != lastStage) {
		resetInput(controls);
	}
	if (stage == 1) {
		move(controls, MOVE_RIGHT);
		controls->m_InputData.m_Jump = stage1ShouldJump();
	}
	lastStage = stage;
}

int MoveToChamberStrategy::resolveStage() {
	vec2 pos = client->m_PredictedChar.m_Pos;
	if (pos.x < 1390) {
		// spawn area
		return 1;
	} else if (pos.y > 1006 && pos.x < 3400) {
		// towards middle fighting area
		return 1;
	}
	return 0;
}

void MoveToChamberStrategy::move(CControls *controls, int directon) {
	if (client->m_Snap.m_pLocalCharacter->m_Weapon == WEAPON_NINJA) {
		//TODO make above into method "isFrozen" in superclass
		controls->m_InputDirectionLeft = 0;
		controls->m_InputDirectionRight = 0;
	} else if (directon == MOVE_LEFT) {
		controls->m_InputDirectionLeft = 1;
	} else if (directon == MOVE_RIGHT) {
		controls->m_InputDirectionRight = 1;
	}
}

const int MoveToChamberStrategy::STAGE1_X_POS_TO_JUMP[] = {2380, 2700, 3020};

int MoveToChamberStrategy::stage1ShouldJump() {
	vec2 pos = client->m_PredictedChar.m_Pos;
	for (int i = 0; i < N_STAGE1_X_POS_TO_JUMP; i++) {
		int xPos = STAGE1_X_POS_TO_JUMP[i];
		if (fabs(pos.x - xPos) < X_POS_JUMP_MARGIN) {
			return 1;
		}
	}
	return 0;

}