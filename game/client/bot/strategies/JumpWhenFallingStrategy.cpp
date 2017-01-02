#include "JumpWhenFallingStrategy.h"

void JumpWhenFallingStrategy::execute(CCharacterCore *player, CControls *controls) {
	if (jumpedLastStep) {
		controls->m_InputData.m_Jump = 0;
		jumpedLastStep = false;
	} else if (player->m_Vel.y >= 0.0f
			&& !(player->m_Jumped & 2)
			&& !player->IsGrounded()) {
		controls->m_InputData.m_Jump = 1;
		jumpedLastStep = true;
	}
}
