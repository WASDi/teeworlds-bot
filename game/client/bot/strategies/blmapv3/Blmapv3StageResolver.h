#ifndef BLMAPV3STAGERESOLVER_H
#define BLMAPV3STAGERESOLVER_H

#include <base/vmath.h>

class Blmapv3StageResolver {
public:

	static int resolveStage(vec2* pos);

private:

	const static vec4 UPPER_STAIRS_COORDINATES;
	const static vec4 LOWER_STAIRS_COORDINATES;

	static bool aboveLine(vec2* pos, const vec4* lineData);

};

#endif /* BLMAPV3STAGERESOLVER_H */

