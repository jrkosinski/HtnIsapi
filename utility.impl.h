#ifndef __UTILITY_IMPL_H__
#define __UTILITY_IMPL_H__

#include "utility.h"


TCHAR toLowerCase(TCHAR c)
{
	if (c > 64 && c < 91)
		c += 32; 

	return c;
}

void writeTextFile(LPCTSTR lpszPath, LPCTSTR lpszBuf, BOOL bAppend)
{
	FILE * pFile;

	pFile = (bAppend) ? (fopen(lpszPath, "a")) : (fopen(lpszPath, "w+")); 

	if (pFile!=NULL)
	{
		fputs (lpszBuf, pFile);
		fclose (pFile);
	}
}

void readTextFile(LPCTSTR lpszPath, LPTSTR lpszBuf, DWORD dwBufLen)
{
	FILE *fp;
	DWORD dwFileLen = 0;

	fopen_s(&fp, lpszPath,"rb");

	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END); 
		dwFileLen = ftell(fp); 
		fseek(fp, 0, SEEK_SET); 

		if (dwFileLen > (dwBufLen-1))
			dwFileLen = (dwBufLen-1); 

		fread(lpszBuf, dwFileLen, 1, fp); 
		fclose(fp);
	}
	else
		dwFileLen = 0;

	lpszBuf[dwFileLen] = NULL;
}	

ULONG stringToULong(LPCTSTR lpszValue, ULONG nDefault)
{
	const int MAX = 9; 

	size_t nIndex = 0; 
	size_t nCount = 0; 	
	TCHAR c = lpszValue[0]; 
	ULONG nPlace = 1; 
	ULONG nOutput = 0; 

	//count number of numeric chars (stop at MAX)
	while (c != NULL)
	{
		c = lpszValue[nIndex++]; 
		if (CHAR_ISNUMERIC(c))
		{
			nCount++; 
			if (nCount == MAX)
				break; 
		}
	}

	//count backwards from index and collect numbers
	if (nCount > 0)
	{
		nCount = 0; 
		while(nIndex > 0)
		{
			c = lpszValue[--nIndex]; 
			if (CHAR_ISNUMERIC(c))
			{
				nOutput += ((LONG)c - 48) * nPlace; 
				nPlace = (nPlace * 10);
			}
		}
	}
	else
		nOutput = nDefault;

	return nOutput;
}




#endif
