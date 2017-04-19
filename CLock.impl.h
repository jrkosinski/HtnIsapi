#ifndef __CLOCK_IMPL_H__
#define __CLOCK_IMPL_H__

#include "CLock.h"

BOOL CLock::IsLocked()
{
	return this->_isLocked;
}

CLock::CLock(CCritSection* pCS, DWORD dwMsSleep, DWORD dwMsTimeout)
{
	this->_isLocked = FALSE; 
	this->_pCS = pCS;

	if (this->_pCS) {
		this->_isLocked = this->_pCS->Try(dwMsSleep, dwMsTimeout); 
	}
}

CLock::~CLock()
{
	if (this->_isLocked && this->_pCS)
		this->_pCS->Leave();
}

#endif