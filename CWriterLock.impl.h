#ifndef __CWRITERLOCK_IMPL_H__
#define __CWRITERLOCK_IMPL_H__

#include "CReaderWriterLock.h"
#include "CWriterLock.h" 

CWriterLock::CWriterLock(CReaderWriterLock* pLock)
{
	this->_pLock = pLock;
	this->_bLocked = pLock->AcquireWriterLock(); 
}

CWriterLock::~CWriterLock()
{
	this->Release();
} 

BOOL CWriterLock::IsAcquired() 
{ 
	return this->_bLocked; 
}

void CWriterLock::Release()
{
	if (this->_bLocked)
	{
		this->_pLock->ReleaseWriterLock();
		this->_bLocked = FALSE;
	}
}

#endif

