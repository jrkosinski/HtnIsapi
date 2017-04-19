#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "CCritSection.h"

/*****************************************************************************************************
/* CLock
/* -----
/* Wraps the functionality of CCritSection such that CCritSection::Leave() can always be guaranteed
/* to be called. CLock must always be declared on the stack; when implemented in this way, it 
/* guarantees that the critical section is always exited, because it will automatically be exited 
/* when the destructor for this class is called (i.e., when it goes out of scope). 
/* 
/* EXAMPLE: 
/*		
/*		// pCS is pointer to CCritSection object
/*		{
/*			CLock lock(pCS); 
/*			if (lock.IsLocked)
/*			{	
/*				// thread-safe code here
/*			}
/*		} 
/*		// here the CLock object is out of scope; 
/*		// destructor has been called, critical section exited.
/*		
/****************************************************************************************************/
class CLock
{
private:
	CCritSection* _pCS; 
	BOOL _isLocked;

public: 
	BOOL IsLocked();

public:
	//////////////
	// Constructor
	// -----------
	// Pass in a pointer to a CCritSection object; automatically enters the critical section.  
	///////////////////////////////////////////////////////////////////////////////////////////////
	CLock(CCritSection* pCS, DWORD dwMsSleep, DWORD dwMsTimeout);
	/////////////
	// Destructor
	// ----------
	// Automatically leaves the critical section that was entered in the constructor.  
	///////////////////////////////////////////////////////////////////////////////////////////////
	~CLock();
};


#endif