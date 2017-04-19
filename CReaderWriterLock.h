#ifndef __CREADERWRITERLOCK_H__
#define __CREADERWRITERLOCK_H__

/*****************************************************************************************************
/* CReaderWriterLock
/* -----------------
/* Uses atomic operations to provide a synchronization lock, one which allows an unlimited number
/* of reader locks but only one writer lock at a time. 
/* 
/* A writer lock can only be acquired when there are 0 currently held reader locks, and 0 currently
/* held writer locks. A reader lock can be acquired only when there is no currently held writer 
/* lock. 
/*		
/****************************************************************************************************/
class CReaderWriterLock
{
private:
	long _nReaders;		// number of reader locks
	long _bWriter;		// writer-lock flag

public: 
	CReaderWriterLock();
	~CReaderWriterLock() {}

public: 
	////////////
	// LockCount
	// ---------
	// Returns the number of locks currently held (reader and writer locks combined). 
	///////////////////////////////////////////////////////////////////////////////////////////////
	long GetLockCount(); 
	////////////////////
	// AcquireReaderLock
	// -----------------
	// Attempts to acquire a new reader lock; times out after the given number of milliseconds. 
	//  
	//		dwMsTimeout - milliseconds before timeout 
	// RETURNS: TRUE if the reader lock was successfully acquired. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL AcquireReaderLock(DWORD dwMsTimeout);
	////////////////////
	// AcquireWriterLock
	// -----------------
	// Attempts to acquire a new reader lock; fails immediately (returning FALSE) if the writer 
	// lock is not immediately available. 
	//  
	// RETURNS: TRUE if the writer lock was successfully acquired. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL AcquireWriterLock();
	
	////////////////////
	// ReleaseReaderLock
	// -----------------
	// Releases one reader lock - decrements the reader-lock count by one. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	void ReleaseReaderLock();
	////////////////////
	// ReleaseWriterLock
	// -----------------
	// Releases the writer lock, if one is currently held. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	void ReleaseWriterLock();
};


#endif