#ifndef __CREADERLOCK_IMPL_H__
#define __CREADERLOCK_IMPL_H__

#include "CReaderWriterLock.h"
#include "CReaderLock.h" 

//acquire lock on construction  
CReaderLock::CReaderLock(CReaderWriterLock* pLock, DWORD dwMsTimeout)
{
	this->_pLock = pLock;
	this->_bLocked = pLock->AcquireReaderLock(dwMsTimeout); 
}

//release the lock on destruction
CReaderLock::~CReaderLock()
{
	this->Release();
}

//is the lock acquired? 
BOOL CReaderLock::IsAcquired() 
{ 
	return this->_bLocked; 
}

//release the lock if acquired
void CReaderLock::Release()
{
	if (this->_bLocked)
	{
		this->_pLock->ReleaseReaderLock();
		this->_bLocked = FALSE;
	}
}

#endif
