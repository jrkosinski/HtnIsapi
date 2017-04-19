#ifndef __CSEARCHBUFFER_H__
#define __CSEARCHBUFFER_H__


/*****************************************************************************************************
/* CSearchBuffer
/* -------------
/*  
/* Encapsulates a buffer containing lines of text. Provides a facility to search through lines of 
/* that text for a given value.
/*
/* Given a buffer of lines of text, it will organize it into a new buffer in which each line is a 
/* fixed known size, for faster searching. During a search it will attempt to match a few characters
/* at the beginning of the string first; if no match is found it can simply jump to the next string
/* in the buffer. The purpose is to facilitate faster searching for known values inside of a 
/* string (specific settings within a config file, for example) 
/*
/****************************************************************************************************/
class CSearchBuffer
{
private:
	LPTSTR _lpszBuf;		// the encapsulted buffer
	DWORD _dwLineSize;		// the size of the longest line in the buffer (plus a few extra bytes for safety)
	DWORD _dwBufSize;		// the size of the buffer 
	DWORD _dwLineCount;		// number of lines in the buffer 

public:
	//////////////
	// Constructor
	// -----------
	// Sets the buffer size to a default value. Allocates memory for a buffer of that size.
	///////////////////////////////////////////////////////////////////////////////////////////////
	CSearchBuffer();
	//////////////
	// Constructor
	// -----------
	// Sets the buffer size to the given value. Allocates memory for a buffer of that size.
	///////////////////////////////////////////////////////////////////////////////////////////////
	CSearchBuffer(DWORD dwBufSize); 
	//////////////
	// Destructor
	// -----------
	// Frees memory allocated for the buffer. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	~CSearchBuffer();

public:
	//////////////
	// CopyBuffer
	// ----------
	// Copies the given buffer into the object, re-organizing it in such a way as to facilitate
	// faster searching. The given buffer is not modified. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	void CopyBuffer(LPCTSTR lpszBuffer); 
	//////////
	// Search
	// ------
	// Does a case-insensitive search for the given string, in the encapsulated buffer. Returns 
	// TRUE only if the given string is an exact match with at least one full line of text 
	// (case-insensitive). 
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL Search(CSafeString* pSearch);

private:
	void init(DWORD dwBufSize);
	DWORD getMaxLineSize(LPCTSTR lpszBuffer); 
};


#endif

