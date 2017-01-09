#include "Blmapv3Util.h"

#include <stdio.h>

bool Blmapv3Util::isGateOpen(CGameClient* client) {
	IClient* iClient = client->Client();
	int numSnapItems = iClient->SnapNumItems(IClient::SNAP_CURRENT);
	for (int i = 0; i < numSnapItems; i++) {
		IClient::CSnapItem item;
		const void *pData = iClient->SnapGetItem(IClient::SNAP_CURRENT, i, &item);
		if (item.m_Type == NETOBJTYPE_LASER) {
			const CNetObj_Laser* laser = (const CNetObj_Laser *) pData;

			if (isLaserForGate(laser)) {
				return laser->m_FromX == 0 || laser->m_FromX == laser->m_X;
			}
		}
	}

	return false;
}

bool Blmapv3Util::isLaserForGate(const CNetObj_Laser* laser) {
	return laser->m_Y == 1008 &&
			(laser->m_X == 1424 || laser->m_X == 1456);
}