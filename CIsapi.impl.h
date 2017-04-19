

#include "CIsapi.h"

#ifdef __DEBUG__
	#define DEBUG_WRITE(_s_) this->debugWrite(_s_); 
#else
	#define DEBUG_WRITE ;
#endif


BOOL WINAPI CIsapi::GetFilterVersion (HTTP_FILTER_VERSION* pVer)
{
	strncpy(pVer->lpszFilterDesc, "HTN Affiliate ISAPI Filter",
            SF_MAX_FILTER_DESC_LEN );

	pVer->dwFlags &= ~SF_NOTIFY_ORDER_MASK;
	pVer->dwFlags |= SF_NOTIFY_SECURE_PORT | SF_NOTIFY_NONSECURE_PORT;
    pVer->dwFlags |= SF_NOTIFY_ORDER_MEDIUM; 
	pVer->dwFlags |= SF_NOTIFY_PREPROC_HEADERS; 

	this->configureResources();

	return TRUE;
}

DWORD WINAPI CIsapi::HttpFilterProc(PHTTP_FILTER_CONTEXT pfc, DWORD dwNotificationType, LPVOID pvNotification)
{
	DEBUG_WRITE("welcome to the HttpFilterProc bitches!\n");

	switch(dwNotificationType)
	{
	case SF_NOTIFY_PREPROC_HEADERS:
		return this->OnNotifyPreprocHeaders(pfc, (PHTTP_FILTER_PREPROC_HEADERS)pvNotification); 
		break;
	}

	return SF_STATUS_REQ_NEXT_NOTIFICATION;
}

DWORD WINAPI CIsapi::OnNotifyPreprocHeaders(PHTTP_FILTER_CONTEXT pfc, PHTTP_FILTER_PREPROC_HEADERS pRawData)
{
	DEBUG_WRITE("welcome to the OnNotifyPreprocHeaders!\n");

	DECLARE_SAFESTRING(strPassthruUrl,	URL_MAXLEN)
	DECLARE_SAFESTRING(strRedirUrl,		URL_MAXLEN); 

	DWORD dwRefererLen	= URL_MAXLEN; 
	DWORD dwUrlLen		= URL_MAXLEN;
	DWORD dwUrlError	= 0; 	
	DWORD dwRefererError= 0;

	TCHAR lpszRequestUrl[URL_MAXLEN];
	TCHAR lpszReferer[URL_MAXLEN]; 

	// get the referer 
	::SetLastError(0);
	pRawData->GetHeader(pfc, "Referer:", lpszReferer, &dwRefererLen); 
	dwRefererError = ::GetLastError(); 
	::SetLastError(0);	

	switch(dwRefererError)
	{
	case ERROR_ARITHMETIC_OVERFLOW: 
		DEBUG_WRITE("dwRefererError: ERROR_ARITHMETIC_OVERFLOW\n"); 
		::SetLastError(0);
		break;
	case ERROR_INSUFFICIENT_BUFFER:
		DEBUG_WRITE("dwRefererError: ERROR_INSUFFICIENT_BUFFER\n"); 
		::SetLastError(0);
		break;
	case ERROR_INVALID_INDEX:
		DEBUG_WRITE("dwRefererError: ERROR_INVALID_INDEX\n"); 
		::SetLastError(0);
		break;
	case ERROR_INVALID_PARAMETER:
		DEBUG_WRITE("dwRefererError: ERROR_INVALID_PARAMETER\n"); 
		::SetLastError(0);
		break;
	case ERROR_NOT_ENOUGH_MEMORY:
		DEBUG_WRITE("dwRefererError: ERROR_NOT_ENOUGH_MEMORY\n"); 
		::SetLastError(0);
		break;
	case ERROR_NOT_SUPPORTED:
		DEBUG_WRITE("dwRefererError: ERROR_NOT_SUPPORTED\n"); 
		::SetLastError(0);
		break;
	}

	//TODO: HANDLE ERRORS 

	if (dwUrlError == 0)
	{
		//get the requested URL
		::SetLastError(0);
		pRawData->GetHeader(pfc, "url", lpszRequestUrl, &dwUrlLen); 
		dwUrlError = ::GetLastError(); 
		::SetLastError(0);

		switch(dwUrlError)
		{
		case ERROR_ARITHMETIC_OVERFLOW: 
			DEBUG_WRITE("dwUrlError: ERROR_ARITHMETIC_OVERFLOW\n"); 
			::SetLastError(0);
			break;
		case ERROR_INSUFFICIENT_BUFFER:
			DEBUG_WRITE("dwUrlError: ERROR_INSUFFICIENT_BUFFER\n"); 
			::SetLastError(0);
			break;
		case ERROR_INVALID_INDEX:
			DEBUG_WRITE("dwUrlError: ERROR_INVALID_INDEX\n"); 
			::SetLastError(0);
			break;
		case ERROR_INVALID_PARAMETER:
			DEBUG_WRITE("dwUrlError: ERROR_INVALID_PARAMETER\n"); 
			::SetLastError(0);
			break;
		case ERROR_NOT_ENOUGH_MEMORY:
			DEBUG_WRITE("dwUrlError: ERROR_NOT_ENOUGH_MEMORY\n"); 
			::SetLastError(0);
			break;
		case ERROR_NOT_SUPPORTED:
			DEBUG_WRITE("dwUrlError: ERROR_NOT_SUPPORTED\n"); 
			::SetLastError(0);
			break;
		}
	}

	//if have referer and URL without errors... 
	if ((dwRefererError == 0) && (dwUrlError == 0))
	{
		CSafeString strRequestUrl(lpszRequestUrl, dwUrlLen+1); 
		CSafeString strReferer(lpszReferer, dwRefererLen+1); 	

		// if URL & referer are both non-empty... 
		if (!strReferer.IsEmpty())
		{
			DEBUG_WRITE("referer:"); 
			DEBUG_WRITE(strRequestUrl.GetBuffer());
			DEBUG_WRITE("\n");

			BOOL bIsHTMPage = FALSE;
			BOOL bIsNativeDomain = FALSE; 

			DECLARE_SAFESTRING(strDomain, URL_MAXLEN); 

			LPTSTR lpszUrl = strRequestUrl.GetBuffer(); 
			this->processUrl(lpszUrl, bIsHTMPage);

			DEBUG_WRITE(strRequestUrl.GetBuffer());
			DEBUG_WRITE("\n");
	
			if (bIsHTMPage)
			{
				this->getDomainName(lpszReferer, &strDomain, bIsNativeDomain); 

				if (!bIsNativeDomain)
				{
					//DEBUG_WRITE("not ignored dir\n");
					DEBUG_WRITE("domain: ");
					DEBUG_WRITE(strDomain.GetBuffer());
					DEBUG_WRITE("\n");

					//if referer domain is in the list of Affiliate domains... 
					if (this->_websiteList.SearchList(&strDomain)) 	
					{		
						DEBUG_WRITE("website in search list\n");

						//rewrite URL
						CSafeString* pPassthruUrl = this->_configFile.GetSetting(CFGID_PASSTHRU_URL); 
						if ((pPassthruUrl != NULL) && (!pPassthruUrl->IsNull()) && (!pPassthruUrl->IsEmpty()))
						{
							DEBUG_WRITE("URL REWRITE\n");

							//create new redir URL from passthrough URL + requested URL
							this->concatURL(pPassthruUrl, &strRequestUrl, &strRedirUrl);

							//change the URL header in the request 
							pRawData->SetHeader(pfc, "url", strRedirUrl.GetBuffer()); 
						}
					}
				}
			}
			else
			{
				DEBUG_WRITE("not HTM page\n");
			}
		}
		else
			DEBUG_WRITE("referrer is empty\n");
	}
	else
	{
		if (dwRefererError != 0)
			DEBUG_WRITE("unspecified dwRefererError"); 
		if (dwUrlError != 0)
			DEBUG_WRITE("unspecified dwUrlError"); 
	}


	return SF_STATUS_REQ_NEXT_NOTIFICATION;
}




//should be called once upon application startup 
void CIsapi::configureResources()
{
	CSafeString* pCfgRefresh = NULL;
	CSafeString* pWebRefresh = NULL; 

	//read config in from file
	this->_configFile.Refresh();

	//get settings for refresh times 
	pCfgRefresh = this->_configFile.GetSetting(CFGID_CONFIG_REFRESH_MIN);
	pWebRefresh = this->_configFile.GetSetting(CFGID_WEBSITE_REFRESH_MIN);

	//apply refresh time to config file
	if ((pCfgRefresh != NULL) && (!pCfgRefresh->IsNull()) && (!pCfgRefresh->IsEmpty()))
	{
		ULONG nMin = stringToULong(pCfgRefresh->GetBuffer(), DEFAULT_CONFIG_REFRESH_MIN); 
		this->_configFile.SetRefreshMinutes((DWORD)nMin); 
	}

	//apply refresh time to websites list file 
	if ((pWebRefresh != NULL) && (!pWebRefresh->IsNull()) && (!pWebRefresh->IsEmpty()))
	{
		ULONG nMin = stringToULong(pWebRefresh->GetBuffer(), DEFAULT_WEBSITE_REFRESH_MIN); 
		this->_configFile.SetRefreshMinutes((DWORD)nMin); 
	}

	//read websites list in from file
	this->_websiteList.Refresh();
}

//basically, returns true if and only if the URL ends with '.htm' 
BOOL CIsapi::isUIPage(CSafeString* pUrl)
{
	BOOL bOutput = FALSE; 
	size_t nLen = pUrl->GetStrLen(); 
	TCHAR c = 0; 
	size_t nIndex = 0; 
 
	//if the length is < 4, it is not worth considering 
	if (nLen > 4)
	{
		//count backwards from end of string and find '.' 
		for(size_t n=(nLen-1); n> 0; n--)
		{
			c = pUrl->GetChar(n); 
			if (c == '.')
			{
				nIndex = n; 
				break;
			}
		}
		
		//if '.' not found, ignore 
		if (nIndex > 0)
		{
			//hardcoded ".htm"  
			TCHAR lpszTemp[5] = ".htm";

			//count fwd from the '.' and match ".htm" 
			bOutput = TRUE; 
			for(size_t n=0; n<4; n++)
			{
				c = (pUrl->GetChar(nIndex + n)); 

				if (c != lpszTemp[n]) 	{
					bOutput = FALSE; 
					break; 
				}
			}

			//has to be at the end of the string,too 
			//   (in other words, for example, '.htm' matches but '.html' does not) 
			if (bOutput == TRUE)
			{
				if (pUrl->GetChar(nIndex+4) != NULL)
					bOutput = FALSE;
			}
		}
	}

	return bOutput; 
}

//removes the querystring, and converts the URL to lowercase 
void CIsapi::adjustRequestUrl(CSafeString* pUrl)
{
	size_t szLen = pUrl->GetStrLen(); 

	for(size_t n=0; n<szLen; n++)
	{
		TCHAR c = toLowerCase(pUrl->GetChar(n)); 
		
		if (c == NULL)
			break;

		if (c == '?')
		{
			pUrl->PutChar(n, NULL);
			break;
		}

		pUrl->PutChar(n, c);
	}
}

//
BOOL CIsapi::isIgnoreDir(CSafeString* pUrl)
{
	BOOL bOutput = FALSE;
	DECLARE_SAFESTRING(strIgnoreDirs, URL_MAXLEN); 
	CSafeString* pIgnoreDirs = this->_configFile.GetSetting(CFGID_IGNORE_WEB_DIRS);

	if ((pIgnoreDirs != NULL) && (!pIgnoreDirs->IsNull()) && (!pIgnoreDirs->IsEmpty()))
	{
		TCHAR c = 1;
		size_t szLen = pIgnoreDirs->GetStrLen(); 

		if ((szLen > 0) && (szLen < pUrl->GetStrLen()))
		{
			bOutput = TRUE;

			for(size_t n=0; n<szLen; n++)
			{
				c = toLowerCase(pIgnoreDirs->GetChar(n)); 
	
				if (c != toLowerCase(pUrl->GetChar(n)))
				{
					bOutput = FALSE;
					break;
				}
			}
		}
	}

	return bOutput;
}

//adds a HARD-CODED value to the end of the URL (the value is important for the passthrough page) 
void CIsapi::concatURL(CSafeString* pUrl, CSafeString* pRedirUrl, CSafeString* pBuf)
{
	//hard-coded querystring value to add 
	TCHAR lpszQS[32] = "?isapi=1&rt=";

	size_t n1 = pUrl->GetStrLen();
	size_t n2 = (n1 + _tcslen(lpszQS)); 
	size_t n3 = (n2 + pRedirUrl->GetStrLen());
	
	//copy original URL to buffer 
	for(size_t n=0; n<n1; n++)	{
		pBuf->PutChar(n, pUrl->GetChar(n)); 
		pBuf->PutChar(n+1, NULL); 
	}
	
	//add querystring 
	for(size_t n=n1; n<n2; n++)	{
		pBuf->PutChar(n, lpszQS[n-n1]); 
		pBuf->PutChar(n+1, NULL);
	}

	//add redirect URL to querystring 
	for(size_t n=n2; n<n3; n++) {
		pBuf->PutChar(n, pRedirUrl->GetChar(n-n2)); 
		pBuf->PutChar(n+1, NULL); 
	}
}

//
void CIsapi::processUrl(LPTSTR lpszBuf, BOOL& bIsHTMPage)
{
	bIsHTMPage = FALSE; 
	size_t nIndex = 0; 
	size_t nLen = 0; 
	size_t nDomainIndex = 0;

	if (lpszBuf != NULL)
	{
		//adjust request URL 
		TCHAR c = lpszBuf[nIndex]; 

		while(c != NULL)
		{
			lpszBuf[nIndex] = toLowerCase(lpszBuf[nIndex]); 

			if ((c == '?') || (c == ' ') || (c == '#'))
			{
				lpszBuf[nIndex] = NULL; 
				nLen = (nIndex); 
				break;
			}

			
			c = lpszBuf[++nIndex]; 
			nLen = nIndex; 
		}

		//is it an HTM page? 
		if (nLen > 4)
		{
			bIsHTMPage = (	(lpszBuf[nLen-4] == '.') && 
							(lpszBuf[nLen-3] == 'h') && 
							(lpszBuf[nLen-2] == 't') && 
							(lpszBuf[nLen-1] == 'm') 
						); 
		}
	}
}

//
void CIsapi::getDomainName(LPTSTR lpszReferer, CSafeString* pBuf, BOOL& bIsNativeDomain)
{
	bIsNativeDomain		= FALSE;
	size_t nIndex		= 0; 
	BOOL bDomainStart	= FALSE;
	BOOL bDomainEnd		= FALSE; 
	size_t nDomainIndex = 0;
	TCHAR lpszNativeDomain[] = "www.hoteltravel.com"; 

	pBuf->PutChar(0, NULL); 

	if (lpszReferer != NULL)
	{
		//adjust request URL 
		TCHAR c = lpszReferer[nIndex]; 
		bIsNativeDomain = TRUE;

		while(c != NULL)
		{
			lpszReferer[nIndex] = toLowerCase(lpszReferer[nIndex]); 

			//get start index of domain 
			if (!bDomainStart) 
			{
				if ((c == '/') && (nIndex > 4))
				{
					if ((lpszReferer[nIndex-1] == '/') && 
						(lpszReferer[nIndex-2] == ':')
						)
					{
						bDomainStart = TRUE; 
					}
				}
			}
			else if (!bDomainEnd)
			{
				if (c == '/')
				{
					if (bIsNativeDomain)
						return; 

					bDomainEnd = TRUE;
				}
				else
				{
					pBuf->PutChar(nDomainIndex, c); 
					pBuf->PutChar(nDomainIndex+1, NULL); 

					if (c != lpszNativeDomain[nDomainIndex])
						bIsNativeDomain = FALSE; 

					nDomainIndex++; 
				}
			}

			c = lpszReferer[++nIndex]; 
		}

		if (pBuf->IsEmpty())
			bIsNativeDomain = FALSE; 
	}
}

//writes a debug message to the debug file if the __DEBUG__ directive is defined 
void CIsapi::debugWrite(LPCTSTR lpszText)
{
#ifdef __DEBUG__
	//get the file path
	CSafeString* pDebugFile = this->_configFile.GetSetting(CFGID_DEBUG_FILEPATH); 

	//write to the file 
	if ((pDebugFile != NULL) && (!pDebugFile->IsNull()) && (!pDebugFile->IsEmpty()))
		writeTextFile(pDebugFile->GetBuffer(), lpszText, TRUE);
#endif
}
