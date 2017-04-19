
#ifndef __CCONFIGFILE_IMPL_H__
#define __CCONFIGFILE_IMPL_H__

#include "CConfigFile.h"
#include "CSafeString.h"
#include "constants.h"

//get the setting from cached variable (or from source if variable is NULL) 
CSafeString* CConfigFile::GetSetting(DWORD dwSettingID)
{
	CSafeString* pOutput = NULL; 

	switch(dwSettingID)
	{
		case CFGID_PASSTHRU_URL:
			pOutput = &(this->_strPassthruUrl);
			break;

		case CFGID_DEBUG_FILEPATH:
			pOutput = &(this->_strDebugFilepath);
			break;

		case CFGID_IGNORE_WEB_DIRS:
			pOutput = &(this->_strIgnoreWebDirs);
			break;

		case CFGID_WEBSITE_FILEPATH: 
			pOutput = &(this->_strWebsiteFilepath);
			break;

		case CFGID_CONFIG_REFRESH_MIN: 
			pOutput = &(this->_strConfigRefreshMin);
			break;

		case CFGID_WEBSITE_REFRESH_MIN: 
			pOutput = &(this->_strWebsiteRefreshMin);
			break;
	}
			
	if (pOutput != NULL && (pOutput->IsEmpty()))
		this->GetSetting(dwSettingID, pOutput); 

	return pOutput;
}

//get the setting from the source and cache it in given buffer  
BOOL CConfigFile::GetSetting(DWORD dwSettingID, CSafeString* pBuf)
{
	BOOL bFound = FALSE;

	pBuf->PutChar(0, NULL);

	//string buffer to hold each line of text 
	DECLARE_SAFESTRING(strLine, (CONFIG_FILE_LINE_MAXLEN)); 
	strLine.PutChar(0, NULL);

	//ensure we have fresh text from config file 
	this->checkFileRefresh();

	//match setting IDs to strings 
	DECLARE_SAFESTRING(strSettingName, URL_MAXLEN); 
	strSettingName.PutChar(0, NULL);

	switch(dwSettingID)
	{
		case CFGID_PASSTHRU_URL:
			strSettingName.Strcpy("PassthruUrl"); 
			break;

		case CFGID_DEBUG_FILEPATH:
			strSettingName.Strcpy("DebugFilePath"); 
			break;

		case CFGID_IGNORE_WEB_DIRS:
			strSettingName.Strcpy("IgnoreWebDirs"); 
			break;

		case CFGID_WEBSITE_FILEPATH: 
			strSettingName.Strcpy("WebsiteFilePath"); 
			break;

		case CFGID_CONFIG_REFRESH_MIN: 
			strSettingName.Strcpy("ConfigFileRefreshMinutes"); 
			break;

		case CFGID_WEBSITE_REFRESH_MIN: 
			strSettingName.Strcpy("WebsiteFileRefreshMinutes"); 
			break;

		default: 
			return FALSE;
	}


	//find out if the setting exists 
	TCHAR c = 1;
	size_t nBufIndex =0;
	size_t nFileIndex =0; 
	DWORD dwBufLen = this->GetBufLen(); 
	DWORD dwLineBufLen = strLine.GetBufLen(); 

	CReaderLock rLock(&this->_rwLock, 1000); 
	if (rLock.IsAcquired())
	{
		while(c != NULL && (nFileIndex < dwBufLen))
		{
			c = this->_lpszFileBuf[nFileIndex++];

			if (c == '=')
			{
				nBufIndex = 0; 

				//line has setting name before '=' sign? 
				if (strLine.Equals(strSettingName.GetBuffer(), FALSE))	{
					bFound = TRUE;
					break;
				}
				else //add the null terminator			
					strLine.PutChar(0, NULL);
			}
			else if (c == 10 || c == 13 || c == 0 || c == 32 || (nBufIndex >= dwLineBufLen))
			{
				nBufIndex = 0; 
				strLine.PutChar(0, NULL);
			}
			else
			{
				//add the next char to the string
				strLine.PutChar(nBufIndex++, c); 
				strLine.PutChar(nBufIndex, NULL); 
			}
		}

		if (bFound)
		{
			c = this->_lpszFileBuf[nFileIndex++]; 
			nBufIndex = 0; 

			while (c != NULL)
			{
				if (c == 10 || c == 13 || c == NULL || (c == 32 && this->BreakOnSpace) ) {
					break;
				}
				else {
					pBuf->PutChar(nBufIndex++, c);
					pBuf->PutChar(nBufIndex, NULL); 
				}

				c = this->_lpszFileBuf[nFileIndex++]; 
			}
		}
	}

	rLock.Release();

	return bFound;
}



//override preRefresh to clear some stuff
void CConfigFile::preRefresh()
{
	this->_strPassthruUrl.Clear();
	this->_strDebugFilepath.Clear();
	this->_strWebsiteFilepath.Clear();
	this->_strIgnoreWebDirs.Clear();
	this->_strConfigRefreshMin.Clear();
	this->_strWebsiteRefreshMin.Clear();
}

//some initialization bullshit 
void CConfigFile::init()
{
	this->BreakOnSpace = TRUE; 
	this->_strPassthruUrl.SetString(this->_lpszPassthruUrl, FILEPATH_MAXLEN);
	this->_strDebugFilepath.SetString(this->_lpszDebugFilepath, FILEPATH_MAXLEN);
	this->_strWebsiteFilepath.SetString(this->_lpszWebsiteFilepath, FILEPATH_MAXLEN);
	this->_strIgnoreWebDirs.SetString(this->_lpszIgnoreWebDirs, FILEPATH_MAXLEN);
	this->_strConfigRefreshMin.SetString(this->_lpszConfigRefreshMin, 10); 
	this->_strWebsiteRefreshMin.SetString(this->_lpszWebsiteRefreshMin, 10); 	
}

#endif

