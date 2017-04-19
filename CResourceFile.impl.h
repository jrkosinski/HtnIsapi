#ifndef __CRESOURCEFILE_IMPL_H__
#define __CRESOURCEFILE_IMPL_H__

#include "CResourceFile.h"
#include "CSafeString.h"
#include "CReaderWriterLock.h"
#include "CReaderLock.h"
#include "CWriterLock.h" 

#include <httpfilt.h>

CResourceFile::CResourceFile(DWORD dwRefreshMinutes, LPCSTR lpszFilepath)
{
	this->_dwRefreshMinutes = dwRefreshMinutes;
	this->_lpszFilepath = lpszFilepath;
	this->_lpszFileBuf = new TCHAR[this->_dwBufLen]; 

	this->_timer.Start(); 
}

//destroy! the buffer, release ALL the memory !
CResourceFile::~CResourceFile()
{
	delete[] this->_lpszFileBuf;
}

//set the number of minutes between refreshes, then reset the timer :|
void CResourceFile::SetRefreshMinutes(DWORD dwRefreshMinutes)
{
	this->_dwRefreshMinutes = dwRefreshMinutes;
	this->_timer.Reset(); 
}

//refresh data from source file, using writer lock 
// (writer lock is not to write to the file, but to the variable that holds the file data) 
void CResourceFile::Refresh()
{
	//ENTER CRITICAL SECTION
	CWriterLock wLock(&this->_rwLock); 
	if (wLock.IsAcquired() && this->_rwLock.GetLockCount() == 1)
	{
		this->preRefresh(); 

		//copy buffer into buffer 
		this->_lpszFileBuf[0] = NULL; 
		readTextFile(this->_lpszFilepath, this->_lpszFileBuf, this->_dwBufLen); 

		this->postRefresh(); 

		//reset timer 
		this->_timer.Reset(); 
	}

	wLock.Release();
}

//is it time for the file to refresh yet? if so, refresh it
void CResourceFile::checkFileRefresh()
{
	//has the buffer (a) not yet been initialized, or (b) expired? 
	if (this->_timer.GetTotalMinutes() >= this->_dwRefreshMinutes)
	{	
		this->Refresh(); 
	}
}


#endif