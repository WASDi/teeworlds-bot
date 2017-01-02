#include "WasdBot.h"
#include "components/controls.h"
#include <stdio.h>

WasdBot::WasdBot() {
	// Constructor
}

void WasdBot::injectInput(CControls *controls) {
	if(!player->readyForBot){
		return;
	}
	
	if(jumpedLastStep) {
		controls->m_InputData.m_Jump = 0;
		jumpedLastStep = false;
	}
	else if (player->m_Vel.y >= 0.0f 
			&& !(player->m_Jumped & 2)
			&& !player->IsGrounded()) {
		printf("Jumped! %.2f\n", player->m_Vel.y);
		controls->m_InputData.m_Jump = 1;
		jumpedLastStep = true;
	}
}