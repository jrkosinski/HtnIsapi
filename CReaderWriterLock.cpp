#ifndef __CREADERWRITERLOCK_IMPL_H__
#define __CREADERWRITERLOCK_IMPL_H__

//no readers, no writers 
CReaderWriterLock::CReaderWriterLock()
{
	this->_nReaders = 0; 
	this->_bWriter = FALSE; 
}

//get the number of locks: writer counts as 1
long CReaderWriterLock::GetLockCount()
{
	long nOut = this->_nReaders; 
	if (this->_bWriter)
		nOut++; 

	return nOut; 
}

//attempt to acquire an additional reader lock 
BOOL CReaderWriterLock::AcquireReaderLock(DWORD dwMsTimeout)
{
	DWORD dwMs = 0; 
	DWORD dwMsSleep = 100; 

	while(dwMs < dwMsTimeout)
	{
		if (!this->_bWriter)
		{
			::InterlockedIncrement(&this->_nReaders);
			if (this->_bWriter)
				::InterlockedDecrement(&this->_nReaders);
			else
				return TRUE;
		}
		if (dwMsTimeout > 0)
		{
			::Sleep(dwMsSleep);
			dwMs += dwMsSleep; 
		}
		else
			break;
 }

	return FALSE;
}

//attempt to acquire exclusive writer lock 
BOOL CReaderWriterLock::AcquireWriterLock()
{
	if (this->_nReaders < 1)
	{
		if (::InterlockedCompareExchange(&this->_bWriter, TRUE, FALSE) == FALSE)
		{
			if ((this->_nReaders > 0))
				::InterlockedExchange(&this->_bWriter, FALSE); 
			else
				return TRUE;
		}   
	}
  
	return FALSE;
}

//release one readerlock
void CReaderWriterLock::ReleaseReaderLock()
{
	::InterlockedDecrement(&this->_nReaders);
}

//release the writerlock
void CReaderWriterLock::ReleaseWriterLock()
{
	::InterlockedExchange(&this->_bWriter, FALSE); 
}


#endif