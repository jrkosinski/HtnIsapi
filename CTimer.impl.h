#ifndef __CTIMER_IMPL_H__
#define __CTIMER_IMPL_H__

#include "CTimer.h"


CTimer::CTimer()
{
	this->IsRunning = FALSE; 
	this->Reset();
}

void CTimer::Start()
{
	if (!this->IsRunning)
	{
		this->IsRunning = TRUE;
		::GetSystemTime(&this->_stStart);		
		this->_stStop = this->_stStart;
	}
}

void CTimer::Start(SYSTEMTIME startTime)
{
	if (!this->IsRunning)
	{
		this->IsRunning = TRUE;
		this->_stStart = startTime;		
		this->_stStop = this->_stStart;
	}
}

void CTimer::Stop()
{
	if (this->IsRunning)
	{
		this->IsRunning = FALSE;
		::GetSystemTime(&this->_stStop);
	}
}

void CTimer::Reset()
{
	::GetSystemTime(&this->_stStart);
	this->_stStop = this->_stStart;
}

long CTimer::GetTotalMilliseconds()
{
	SYSTEMTIME stStop;

	if (this->IsRunning)
		::GetSystemTime(&stStop);
	else
		stStop = this->_stStop;

	return this->getTotalMilliseconds(&stStop); 
}

long CTimer::GetTotalSeconds()
{
	SYSTEMTIME stStop;

	if (this->IsRunning)
		::GetSystemTime(&stStop);
	else
		stStop = this->_stStop;

	return this->getTotalSeconds(&stStop); 
}

long CTimer::GetTotalMinutes()
{
	SYSTEMTIME stStop;

	if (this->IsRunning)
		::GetSystemTime(&stStop);
	else
		stStop = this->_stStop;

	return this->getTotalMinutes(&stStop); 
}

long CTimer::getTotalMilliseconds(SYSTEMTIME* pTime)
{
	long nSec = this->getTotalSeconds(pTime);
	long nMill = ((long)pTime->wMilliseconds - (long)this->_stStart.wMilliseconds);

	long nTotal = (nSec * 1000); 
	nTotal += nMill;

	return nTotal; 
}

long CTimer::getTotalSeconds(SYSTEMTIME* pTime)
{
	long nMin = this->getTotalMinutes(pTime); 
	long nSec = ((long)pTime->wSecond - (long)this->_stStart.wSecond);

	long nTotal = (nMin * 60);
	nTotal += nSec; 

	return nTotal; 
}

long CTimer::getTotalMinutes(SYSTEMTIME* pTime)
{
	long nMax = 1440; 

	if (pTime->wYear != this->_stStart.wYear)
		return nMax;

	if (pTime->wMonth != this->_stStart.wMonth)
		return nMax;

	if (pTime->wDay != this->_stStart.wDay)
		return nMax; 

	long nHour = ((long)pTime->wHour - (long)this->_stStart.wHour);
	long nMin = ((long)pTime->wMinute - (long)this->_stStart.wMinute);

	long nTotal = (nHour * 60); 
	nTotal += (nMin); 

	return nTotal; 
}

#endif