

#include "include.h"
#include "CIsapi.impl.h"


CIsapi* pIsapi = new CIsapi();


BOOL WINAPI GetFilterVersion(HTTP_FILTER_VERSION* pVer)
{
	return pIsapi->GetFilterVersion(pVer);
}

DWORD WINAPI HttpFilterProc(PHTTP_FILTER_CONTEXT pfc, DWORD dwNotificationType, LPVOID pvNotification)
{
	return pIsapi->HttpFilterProc(pfc, dwNotificationType, pvNotification);
}




