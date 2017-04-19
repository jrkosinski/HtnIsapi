
#ifndef __CSAFESTRING_IMPL_H__
#define __CSAFESTRING_IMPL_H__

#include "utility.h"
#include "CSafeString.h"

//initialize to null, 0 
CSafeString::CSafeString()
{
	this->_dwBufLen=0; 
	this->_lpszBuf=NULL; 
}

//intialize to given values 
CSafeString::CSafeString(LPTSTR lpszBuf, DWORD dwBufLen)
{
	this->_dwBufLen=0; 
	this->_lpszBuf=NULL; 
	this->SetString(lpszBuf, dwBufLen);
}

//open the string buffer 
void CSafeString::SetString(LPTSTR lpszBuf, DWORD dwBufLen)
{
	this->_lpszBuf = lpszBuf;
	this->_dwBufLen = dwBufLen;
	
	if (this->_lpszBuf != NULL)
		this->_lpszBuf[dwBufLen-1] = NULL;
}

//put a single character there 
BOOL CSafeString::PutChar(DWORD dwIndex, TCHAR c)
{
	BOOL bOutput = (dwIndex < (this->_dwBufLen-1));

	if (bOutput)
		this->_lpszBuf[dwIndex] = c; 

	return bOutput;
}

//get the character which is there (or NULL if index invalid) 
TCHAR CSafeString::GetChar(DWORD dwIndex)
{
	TCHAR c = NULL; 

	if (dwIndex < (this->_dwBufLen-1))
		c = this->_lpszBuf[dwIndex]; 

	return c; 
}

//return the whole buffer 
LPTSTR CSafeString::GetBuffer()
{
	return this->_lpszBuf;
}

//claculate the string length stored in the buffer 
DWORD CSafeString::GetStrLen()
{
	DWORD dwLen = _tcslen(this->_lpszBuf); 

	if (dwLen >= this->_dwBufLen)
	{
		dwLen = this->_dwBufLen-1; 
		this->_lpszBuf[dwLen] = NULL;
	}

	return dwLen;
}

//return the previously declared buffer length 
DWORD CSafeString::GetBufLen()
{
	return this->_dwBufLen;
}

//copies everything from the given string to the internal string 
// if given string overruns internal buffer, copying just ends 
// null-terminator will not be overwritten 
DWORD CSafeString::Strcpy(LPCTSTR lpszSrc)
{
	DWORD dwIndex = 0; 

	while(dwIndex < (this->_dwBufLen-1))
	{
		TCHAR c = lpszSrc[dwIndex];
		this->_lpszBuf[dwIndex] = c;

		if (c == NULL)
			break;

		dwIndex++; 
	}

	return dwIndex;
}

//is the given string equal to the internal one? (case-sensitive) 
BOOL CSafeString::Equals(LPCTSTR lpszString)
{
	return this->Equals(lpszString, TRUE);
}

//is the given string equal to the internal one? 
BOOL CSafeString::Equals(LPCTSTR lpszString, BOOL bCaseSensitive)
{
	size_t nIndex = 0; 
	BOOL bMatch = TRUE; 
	DWORD dwLen = this->GetStrLen();

	while(nIndex < dwLen)
	{
		TCHAR c1 = this->_lpszBuf[nIndex];
		TCHAR c2 = lpszString[nIndex]; 

		if (!bCaseSensitive)
		{
			c1 = toLowerCase(c1);
			c2 = toLowerCase(c2);
		}

		if (c1 != c2) 	{
			bMatch = FALSE; 
			break; 
		}

		if (c1 == NULL || c2 == NULL)
			break; 

		nIndex++; 
	}

	return bMatch; 
}

//is it an empty string? 
BOOL CSafeString::IsEmpty()
{
	return ((this->_dwBufLen == 0) ||
			(this->_lpszBuf == NULL) ||
			(this->_lpszBuf[0] == NULL)
		  ); 
}

//writes a null terminator to the first byte, making the string 'empty' 
void CSafeString::Clear()
{
	if (!this->IsNull())
		this->PutChar(0, 0); 
}

//is the buffer null? (is it a null pointer?) 
BOOL CSafeString::IsNull()
{
	return (this->_lpszBuf == NULL); 
}

//set internal buffer pointer to NULL 
void CSafeString::MakeNull()
{
	this->SetString(NULL,0);
}

#endif