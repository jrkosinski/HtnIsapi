#ifndef __CRESOURCEFILE_H__
#define __CRESOURCEFILE_H__

#include "CTimer.h"
#include "CSafeString.h"
#include "CReaderWriterLock.h"


/*****************************************************************************************************
/* CResourceFile
/* -------------
/* Base class for encapsulating a buffer of text, read in from a text file when first requested. 
/* 
/* After first request, buffer refreshes again from the text file when requested again, IF n minutes
/* have elapsed since it was last read. 
/*
/****************************************************************************************************/
class CResourceFile
{
private:
	CTimer _timer;
	DWORD _dwRefreshMinutes;
	LPCTSTR _lpszFilepath;
	
	static const DWORD _dwBufLen = FILECONTENT_BUFLEN;

protected:
	// the buffer into which the text resource is read & stored
	LPTSTR _lpszFileBuf; 
	CReaderWriterLock _rwLock; 

public:
	CResourceFile(DWORD dwRefreshMinutes, LPCTSTR lpszFilepath);
	~CResourceFile(); 

public:
	void SetRefreshMinutes(DWORD dwRefreshMinutes); 
	void Refresh();
	DWORD GetBufLen() { return CResourceFile::_dwBufLen;}

protected:
	void checkFileRefresh();
	//////////////
	// preRefresh
	// ----------
	// May be overridden in child classes to provide some extra functionality AFTER THE write-lock
	// has been acquired, but BEFORE the source file is read and the internal buffer refreshed. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	virtual void preRefresh() {}  
	///////////////
	// postRefresh
	// -----------
	// May be overridden in child classes to provide some extra functionality AFTER the internal
	// buffer is refreshed, but BEFORE the writer-lock has been released. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	virtual void postRefresh() {}  
}; 

#endif