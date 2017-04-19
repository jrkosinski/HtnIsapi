
#ifndef __CISAPI_H__
#define __CISAPI_H__

#include "CSafeString.h"
#include "CWebsiteList.h"
#include "CConfigFile.h"

/*****************************************************************************************************
/* CIsapi
/* ------
/* The ISAPI filter. 
/****************************************************************************************************/
class CIsapi
{
public: 
	CWebsiteList _websiteList;		// encapsulate list of Affiliate websites
	CConfigFile _configFile;		// encapsulate configuration file

public:
	CIsapi(){}
	~CIsapi(){}

public:
	///////////////////
	// GetFilterVersion
	// ----------------
	// Runs exactly once upon loading of the filter; use to register for event notifications.
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL WINAPI GetFilterVersion(HTTP_FILTER_VERSION* pVer);
	/////////////////
	// HttpFilterProc
	// --------------
	// Main ISAPI method; intercepts all notification types
	///////////////////////////////////////////////////////////////////////////////////////////////
	DWORD WINAPI HttpFilterProc(PHTTP_FILTER_CONTEXT pfc, DWORD dwNotificationType, LPVOID pvNotification);
	/////////////////////////
	// OnNotifyPreprocHeaders
	// ----------------------
	// Main ISAPI method; handles the SF_NOTIFY_PREPROC_HEADERS notification. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	DWORD WINAPI OnNotifyPreprocHeaders(PHTTP_FILTER_CONTEXT pfc, PHTTP_FILTER_PREPROC_HEADERS dwRawData);


private:

	//writes a given debug message to the debug file (only if the __DEBUG__ directive is defined)
	void debugWrite(LPCTSTR lpszText);

	//should be called once upon application startup
	void configureResources();

	//
	void concatURL(CSafeString* pUrl, CSafeString* pRedirUrl, CSafeString* pBuf);
	void adjustRequestUrl(CSafeString* pUrl);
	void processUrl(LPTSTR lpszBuf, BOOL& bIsHTMPage); 
	void getDomainName(LPTSTR lpszReferer, CSafeString* pBuf, BOOL& bIsNativeDomain); 
	BOOL isUIPage(CSafeString* pUrl);

	//should the given URL directory be ignored? 
	BOOL isIgnoreDir(CSafeString* pUrl);	
};

#endif