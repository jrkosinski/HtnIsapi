#ifndef __CREADERLOCK_H__
#define __CREADERLOCK_H__

#include "CReaderWriterLock.h"

/*****************************************************************************************************
/* CReaderLock
/* -----------
/* Wrapper for a CReaderWriterLock* object; attempts to acquire the reader lock in the constructor,  
/* then releases the lock in the destructor, to ensure that the lock will always be releases no matter
/* what. 
/* 
/* An instance of this object should always be declared on the stack, so that the lock will be 
/* released automatically when it goes out of scope. 
/*
/*	// *pLock is a pointer to a CReaderWriterLock object
/*	CReaderLock rLock(pLock)
/*	if (rLock.IsAcquired())
/*	{
/*		// do stuff
/*	}
/*	rLock.Release(); 
/*		
/*	The Release() method can be called manually just for clarity, but if the lock is not released
/*	by a manual call to Release(), it will be done when the CReaderLock object goes out of scope, 
/*	automatically. 
/*		
/****************************************************************************************************/
class CReaderLock
{
private: 
	BOOL _bLocked;				// lock acquired? 
	CReaderWriterLock* _pLock;	// pointer to reader-writer lock

public:
	//////////////
	// Constructor
	// -----------
	// Automatically attempts to acquire a reader lock using the given CReaderWriterLock pointer.
	///////////////////////////////////////////////////////////////////////////////////////////////
	CReaderLock(CReaderWriterLock* pLock, DWORD dwMsTimeout);
	/////////////
	// Destructor
	// ----------
	// Automatically calls the Release() method. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	~CReaderLock();

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