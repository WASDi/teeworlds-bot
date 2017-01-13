#include "Blmapv3StageResolver.h"

int Blmapv3StageResolver::resolveStage(vec2* pos) {
	//TODO code that looks better using bounding boxes
	if (pos->x < 1390) {
		// spawn area
		return 1;
	} else if (pos->y > 1006 && pos->x < 3400) {
		// lower area heading towards middle fighting area
		return 1;
	} else if (pos->y > 555 && pos->x >= 3400) {
		// in battle area
		return 2;
	}
	if (pos->y < 530 && pos->x > 2385 && pos->x < 3800) {
		// upper area heading left to behind the gate
		return 3;
	}
	if (insideChamber(pos)) {
		return 5;
	}
	if (pos->x > 1380 && pos->x <= 2385 && pos->y < 1000) {
		// within bounding box for area behind gate (stage 4 or 5)
		bool behindGateArea = aboveLine(pos, &LOWER_STAIRS_COORDINATES);
		if (behindGateArea) {
			return 4;
		}
	}
	return 0;
}

bool Blmapv3StageResolver::insideChamber(vec2* pos) {
	return pos->x > 1380
			&& pos->x < 1850
			&& pos->y > 240
			&& aboveLine(pos, &UPPER_STAIRS_COORDINATES);
}

bool Blmapv3StageResolver::insideChamberFreeze(vec2* pos) {
	return aboveLine(pos, &CHAMBER_FREEZE_COORDINATES);
}

const vec4 Blmapv3StageResolver::UPPER_STAIRS_COORDINATES = vec4(1489, 699, 1809, 539);
const vec4 Blmapv3StageResolver::LOWER_STAIRS_COORDINATES = vec4(1489, 987, 2385, 539);
const vec4 Blmapv3StageResolver::CHAMBER_FREEZE_COORDINATES = vec4(1392, 560+20, 1520, 432+20);

bool Blmapv3StageResolver::aboveLine(vec2* pos, const vec4* lineData) {
	float stairKValue = (lineData->y - lineData->w) / (lineData->z - lineData->x);
	vec2 posNorm = vec2(pos->x - lineData->x, lineData->y - pos->y);

	return posNorm.y > stairKValue * posNorm.x;
}