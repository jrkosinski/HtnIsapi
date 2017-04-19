
#ifndef __CSAFESTRING_H__
#define __CSAFESTRING_H__

/* automatically declares a TCHAR array on the stack, 
	and wraps it in a CSafeString object 

	Declares a CSafeString object on the stack, named [name] 
	with max buffer size [size].   
	
	Example: 
		DECLARE_SAFESTRING(strInstance, 255)		
		(Results in a CSafeString object named strInstance, wrapping a TCHAR array of size 255.)

*/ 
#define DECLARE_SAFESTRING(name, size)		\
	TCHAR lpsz ## name[size];						\
	CSafeString name(lpsz ## name, size);			\



/*****************************************************************************************************
/* CSafeString
/* -----------
/* String class, for implementing buffer-safe opertions on TCHAR strings, where the memory is 
/* declared on the stack only. 
/* 
/* For memory safety, no memory for strings in this ISAPI are allocated on the heap. Strings are 
/* stored on the stack only, and wrapped in this class in order to prevent buffer overruns. Operations
/* on strings encapsulated in this class do automatic buffer checks where the risk of buffer overrun
/* exists. 
/*
/* In addition to buffer overrun checks, this class reserves the very last index in the encapsulated 
/* array, for the NULL TERMINATOR. Will attempt to always guarantee a NULL TERMINATOR at the end.
/*
/* Declaration of CSafeString objects should also be done in stack memory. USE THE MACRO.... 
/* 
/*		DECLARE_SAFESTRING(strInstance, 255)
/*		
/* Results in an object named strInstance, wrapping a TCHAR array of size 255. 
/*
/****************************************************************************************************/
class CSafeString
{
private:
	LPTSTR _lpszBuf;
	DWORD _dwBufLen;

public:
	//////////////
	// Constructor
	// -----------
	// Default constructor; the encapsulated buffer will be NULL, max size 0. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	CSafeString();
	//////////////
	// Constructor
	// -----------
	// Pass in the buffer size, and a pointer to the buffer. 
	// It's recommended to use the DECLARE_SAFESTRING macro instead. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	CSafeString(LPTSTR lpszBuf, DWORD dwBufLen);
	//////////////
	// Destructor
	// ----------
	// Empty
	///////////////////////////////////////////////////////////////////////////////////////////////
	~CSafeString() {}

public:
	////////////
	// SetString
	// ---------
	// Changes the currently encapsulated buffer with the given one. 
	//		lpszBuf - the new TCHAR buffer to encapsulate
	//		dwBufLen - the array size of the given buffer
	///////////////////////////////////////////////////////////////////////////////////////////////
	void SetString(LPTSTR lpszBuf, DWORD dwBufLen);
	//////////
	// PutChar
	// -------
	// Writes the given character to the given index in the encapsulated buffer.
	//		dwIndex - the index to which to write the character
	//		c - the character to write at the given index
	// 
	// RETURNS: TRUE if the new char could be put in place; FALSE if the operation was cancelled
	//			due to imminent buffer overrun. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL PutChar(DWORD dwIndex, TCHAR c);
	//////////
	// GetChar
	// -------
	// Returns the character located at the given index, or 0 if the index is invalid.
	//		dwIndex - the index of the character to return.
	// 
	// RETURNS: the character at the given index in the encapsulated buffer, or NULL (0) if 
	//			the index is located past the end of the buffer. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	TCHAR GetChar(DWORD dwIndex); 
	////////////
	// GetBuffer
	// ---------
	// Returns a pointer to the encapsulated buffer. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	LPTSTR GetBuffer(); 
	////////////
	// GetStrLen
	// ---------
	// Returns the length of the STRING encapsulated in the given buffer; in other words, the 
	// number of characters in the string before the first NULL terminator. Not the same as 
	// the BUFFER SIZE (i.e., if buffer size is 255, the max StrLen SHOULD only be 254)
	//
	// See also GetBufLen()
	///////////////////////////////////////////////////////////////////////////////////////////////
	DWORD GetStrLen();
	////////////
	// GetBufLen
	// ---------
	// Returns the max size of the encapsulated buffer. Not the same as the length of the string 
	// contained therein. 
	//
	// See also GetStrLen()
	///////////////////////////////////////////////////////////////////////////////////////////////
	DWORD GetBufLen();
	/////////
	// Strcpy
	// ------
	// Copies the given string to the encapsulated buffer, insofar as the length of the string 
	// to copy does not exceed the buffer size. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	DWORD Strcpy(LPCTSTR lpszSrc); 
	/////////
	// Equals
	// ------
	// Does a case-sensitive comparison with the given string; returns TRUE if the string is 
	// equal to the string in the encapsulated buffer. 
	//
	// RETURNS: TRUE if the string is equal to the encapsulated one.
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL Equals(LPCTSTR lpszString);
	/////////
	// Equals
	// ------
	// Does a case-sensitive or case-insensitive comparison with the given string; returns TRUE 
	// if the string is equal to the string in the encapsulated buffer. 
	//
	// RETURNS: TRUE if the string is equal to the encapsulated one.
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL Equals(LPCTSTR lpszString, BOOL bCaseSensitive);
	//////////
	// IsEmpty
	// -------
	// Returns a value indicating whether or not the string is empty, without having to iterate
	// the string to find the length. 
	//
	// RETURNS: TRUE if the string is empty (first is NULL), false otherwise. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL IsEmpty(); 
	//////////
	// Clear
	// -----
	// Makes the string empty (first char is NULL). 
	///////////////////////////////////////////////////////////////////////////////////////////////
	void Clear();
	//////////
	// IsNull
	// ------
	// Returns a value indicating whether or not the inner TCHAR array is a null pointer. 
	//
	// RETURNS: TRUE if the inner TCHAR array is a null pointer. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL IsNull();
	//////////
	// MakeNull
	// --------
	// Sets the inner TCHAR array equal to a null pointer. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	void MakeNull();
};



#endif