#ifndef __CWRITERLOCK_H__
#define __CWRITERLOCK_H__

#include "CReaderWriterLock.h"

/*****************************************************************************************************
/* CWriterLock
/* -----------
/* Wrapper for a CReaderWriterLock* object; attempts to acquire the writer lock in the constructor,  
/* then releases the lock in the destructor, to ensure that the lock will always be released no matter
/* what. 
/* 
/* An instance of this object should always be declared on the stack, so that the lock will be 
/* released automatically when it goes out of scope. 
/*
/*	// *pLock is a pointer to a CReaderWriterLock object
/*	CWriterLock wLock(pLock)
/*	if (wLock.IsAcquired())
/*	{
/*		// do stuff
/*	}
/*	wLock.Release(); 
/*		
/*	The Release() method can be called manually just for clarity, but if the lock is not released
/*	by a manual call to Release(), it will be done when the CWriterLock object goes out of scope, 
/*	automatically. 
/*		
/****************************************************************************************************/
class CWriterLock
{
private: 
	BOOL _bLocked;				// lock acquired? 
	CReaderWriterLock* _pLock;	// pointer to reader-writer lock

public:
	//////////////
	// Constructor
	// -----------
	// Automatically attempts to acquire a writer lock using the given CReaderWriterLock pointer.
	///////////////////////////////////////////////////////////////////////////////////////////////
	CWriterLock(CReaderWriterLock* pLock);
	/////////////
	// Destructor
	// ----------
	// Automatically calls the Release() method. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	~CWriterLock();

public:
	/////////////
	// IsAcquired
	// ----------
	// Indicates whether or not the lock has been successfully acquired. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL IsAcquired();
	//////////
	// Release
	// -------
	// Releases the lock, if it has been acquired. Automatically called from destructor. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	void Release();
};


#endif