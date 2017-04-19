#ifndef __CCONFIGFILE_H__
#define __CCONFIGFILE_H__

#include "CResourceFile.h"
#include "CSafeString.h" 

/*****************************************************************************************************
/* CConfigFile
/* -----------
/* Encapsulates the ISAPI's config file. Reads from the file and provides settings, each setting 
/* denoted by a unique constant ID. Reads from the file when first requested. 
/*
/* Stores the file in ISAPI memory, refreshes when requested again after N minutes have elapsed 
/* from the last time it was read. 
/*
/****************************************************************************************************/
class CConfigFile : public CResourceFile
{ 
private:
	TCHAR _lpszPassthruUrl[FILEPATH_MAXLEN]; 
	TCHAR _lpszDebugFilepath[FILEPATH_MAXLEN];
	TCHAR _lpszWebsiteFilepath[FILEPATH_MAXLEN];
	TCHAR _lpszIgnoreWebDirs[FILEPATH_MAXLEN]; 
	TCHAR _lpszConfigRefreshMin[10];
	TCHAR _lpszWebsiteRefreshMin[10];

	CSafeString _strPassthruUrl;
	CSafeString _strDebugFilepath;
	CSafeString _strWebsiteFilepath;
	CSafeString _strIgnoreWebDirs;
	CSafeString _strConfigRefreshMin;
	CSafeString _strWebsiteRefreshMin;


public: 
	/* if TRUE, the config file reader will stop reading a setting as soon as it 
	encounters whitespace. For example, "Setting1=john smith"
	if TRUE, this value of "Setting1" will be read as simply "john". 

	Default is TRUE 
	*/ 
	BOOL BreakOnSpace; 


public:
	//////////////
	// Constructor
	// -----------
	///////////////////////////////////////////////////////////////////////////////////////////////
	CConfigFile() : CResourceFile(DEFAULT_CONFIG_REFRESH_MIN, CONFIG_FILEPATH) { this->init();}
	~CConfigFile() {} 

public:

	//////////////
	// GetSetting
	// ----------
	// Gets the setting specified by the given setting ID, returns pointer to a stored CSafeString 
	// object. 
	//		dwSettingID - the ID of the setting to retrieve. 
	//
	// RETURNS: pointer to an internally stored CSafeString object (does not allocate new memory). 
	///////////////////////////////////////////////////////////////////////////////////////////////
	CSafeString* GetSetting(DWORD dwSettingID); 

	//////////////
	// GetSetting
	// ----------
	// Gets the setting specified by the given setting ID, reads it into the given buffer. 
	//		dwSettingID - the ID of the setting to retrieve. 
	//		pBuf - the buffer into which to read the setting value.
	//
	// RETURNS: TRUE if the setting was found and read, FALSE if it could not be found. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL GetSetting(DWORD dwSettingID, CSafeString* pBuf); 
	
protected: 
	void preRefresh(); 

private:
	void init();
};


#endif

