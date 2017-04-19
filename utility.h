#ifndef __UTILITY_H__
#define __UTILITY_H__

/*****************************************************************************************************
/* utility.h
/* ----------
/* Application global utility functions. 
/*
/****************************************************************************************************/

#include "CSafeString.h"


#define ISWHITESPACE(_c)	(_c == 8 || _c == ' ')
#define CHAR_ISNUMERIC(_c)	(_c >= 48 && _c <= 57)


/* converts given char to lowercase */
TCHAR toLowerCase(TCHAR c);

/* writes the given string buffer to specified file */
void writeTextFile(LPCTSTR lpszPath, LPCTSTR lpszBuf, BOOL bAppend);

/* reads from specified file into given TCHAR buffer, up to [dwBufLen] max size */
void readTextFile(LPCTSTR lpszPath, LPTSTR lpszBuf, DWORD dwBufLen);

/* converts a string to an integer, ignores non-numeric characters */ 
ULONG stringToULong(LPCTSTR lpszValue, ULONG nDefault);



#endif
