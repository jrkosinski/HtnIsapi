#ifndef __CSEARCHBUFFER_IMPL_H__
#define __CSEARCHBUFFER_IMPL_H__

//construct - create internal buffer 
CSearchBuffer::CSearchBuffer()
{
	this->init(FILECONTENT_BUFLEN);
}

//construct - create internal buffer 
CSearchBuffer::CSearchBuffer(DWORD dwBufSize)
{
	this->init(dwBufSize);
}

//release ALL the buffered memory! 
CSearchBuffer::~CSearchBuffer()
{
	delete[] this->_lpszBuf;
}

//
void CSearchBuffer::CopyBuffer(LPCTSTR lpszBuffer)
{
	size_t x = 0;
	size_t y = 0;
	this->_dwLineSize = 0;
	this->_dwLineCount = 0; 
	size_t nLineIndex = 0; 

	//get the standardized max size (number of chars) that is present in each line of text 
	this->_dwLineSize = this->getMaxLineSize(lpszBuffer); 

	TCHAR c = lpszBuffer[x]; 
	this->_lpszBuf[y] = NULL; 
	
	while (c != NULL)
	{
		//reached end of the string buffer (null terminator) 
		if (c == NULL)
		{
			this->_lpszBuf[y] = NULL; 
			break;
		}

		//reached end of the line
		else if (c == 10 || c == 13)
		{
			if (y > 0 && (this->_lpszBuf[y-1] != NULL))
			{
				//advance to next line
				this->_lpszBuf[y] = NULL; 
				while(nLineIndex < this->_dwLineSize) {
					this->_lpszBuf[y++] = NULL; 
					nLineIndex++; 
				}

				this->_dwLineCount++; 
			}

			nLineIndex = 0; 
		}
		else if (ISWHITESPACE(c)) {
			//do nothing 
		}
		else
		{
			this->_lpszBuf[y++] = c; 
			this->_lpszBuf[y] = NULL;
			nLineIndex++; 
		}

		c = toLowerCase(lpszBuffer[++x]); 
	}
}

//search! the purpose of this class is to search efficiently for a string in a bigger string.
BOOL CSearchBuffer::Search(CSafeString* pSearch)
{
	DWORD dwLineIndex = 0; 
	DWORD dwBufIndex = 0; 
	BOOL bFound = FALSE; 

	DWORD dwPrimaryIndex = 0; 
	DWORD dwSecondaryIndex = 4;
	LPTSTR lpszBuf;

	/* get a primary search character to match; if this one doesn't match then 
	the pointer will move to the next line. */
	TCHAR cPrimary = toLowerCase(pSearch->GetChar(dwPrimaryIndex)); 
	
	if (cPrimary != NULL)
	{
		/* get a secondary search character to match; if the first one matches, 
		and the second one matches, the entire line can be searched. */
		TCHAR cSecondary = toLowerCase(pSearch->GetChar(dwSecondaryIndex)); 

		while(cSecondary == NULL) 	{
			dwSecondaryIndex--; 
			cSecondary = toLowerCase(pSearch->GetChar(dwSecondaryIndex)); 
		}

		//loop through 'lines' of buffer
		while (dwBufIndex < this->_dwBufSize)
		{
			lpszBuf = (this->_lpszBuf + dwBufIndex);
			if (lpszBuf[0] == NULL)
				break;

			//try to match the line 
			if (lpszBuf[dwSecondaryIndex] == cSecondary)
			{
				if (lpszBuf[dwPrimaryIndex] == cPrimary)
				{
					if (pSearch->Equals(lpszBuf, FALSE)) 
					{
						bFound = TRUE;
						break;
					}
				}
			}

			dwBufIndex += this->_dwLineSize;
		}
	}
	
	return bFound;
}

void CSearchBuffer::init(DWORD dwBufSize)
{
	this->_dwLineSize = 0;
	this->_dwLineCount = 0; 
	this->_dwBufSize = dwBufSize;
	this->_lpszBuf = new TCHAR[this->_dwBufSize];

	memset(this->_lpszBuf, NULL, sizeof(TCHAR) * this->_dwBufSize); 
}

DWORD CSearchBuffer::getMaxLineSize(LPCTSTR lpszBuffer)
{
	TCHAR c = lpszBuffer[0]; 
	size_t nIndex = 0; 
	size_t nLineSize = 0; 
	size_t nMaxLine = 0; 

	while (c != NULL)
	{
		nLineSize++; 

		if (nLineSize > nMaxLine)
			nMaxLine = nLineSize; 

		if (c == 13 || c == 10) {
			nLineSize = 0; 
		}

		c = lpszBuffer[++nIndex]; 
	}

	return nMaxLine + 5;
}


#endif

