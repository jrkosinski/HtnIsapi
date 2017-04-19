#ifndef __CWEBSITELIST_IMPL_H__
#define __CWEBSITELIST_IMPL_H__

#include "CWebsiteList.h"
#include "utility.h" 


BOOL CWebsiteList::SearchList(CSafeString* pSearch)
{
	BOOL bResult = FALSE; 

	this->checkFileRefresh(); 

	CReaderLock rLock(&this->_rwLock, 1000); 
	if (rLock.IsAcquired())
	{
		bResult = this->_searchBuffer.Search(pSearch);
	}

	rLock.Release(); 

	return bResult;
}

void CWebsiteList::postRefresh()
{
	this->_searchBuffer.CopyBuffer(this->_lpszFileBuf); 
}


#endif