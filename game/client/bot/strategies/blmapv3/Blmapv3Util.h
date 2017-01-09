#ifndef BLMAPV3UTIL_H
#define BLMAPV3UTIL_H

#include <game/client/gameclient.h>

class Blmapv3Util {
public:

	static bool isGateOpen(CGameClient* client);

private:

	static bool isLaserForGate(const CNetObj_Laser* laser);

};

#endif /* BLMAPV3UTIL_H */

