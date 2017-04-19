
#ifndef __CCRITSECTION_H__
#define __CCRITSECTION_H__


/*****************************************************************************************************
/* CCritSection
/* ------------
/* Encapsulates functionality for implementing a thread-safe critical section in code. 
/* 
/* EXAMPLE: 
/*		
/*		// this->_pCS is pointer to CCritSection object
/*		if (this->_pCS->Try())
/*		{	
/*			// thread-safe code here
/*			
/*			this->_pCS-Leave();
/*		}
/*		
/****************************************************************************************************/
class CCritSection
{
private:
    long _nLockCount;
    long _nThreadId;
	CRITICAL_SECTION _cs;

public:
	BOOL IsLocked() { return (this->_nLockCount > 0);} 

public:
	CCritSection(); 
	~CCritSection() {}

public: 
	////////
	// Enter
	// -----
	// Attempts to enter the critical section. 
	///////////////////////////////////////////////////////////////////////////////////////////////
    void Enter();
	////////
	// Leave
	// -----
	// Leaves the critical section. 
	///////////////////////////////////////////////////////////////////////////////////////////////
    void Leave();
	//////
	// Try
	// ---
	// Attempts to enter the critical section; returns a boolean value indicating success or 
	// failure thereof. 
	//
	// RETURNS: boolean indicating success/failure to enter critical section.
	///////////////////////////////////////////////////////////////////////////////////////////////
    BOOL Try(DWORD dwMsSleep, DWORD dwMsTimeout);
	BOOL Wait(DWORD dwMsSleep, DWORD dwMsTimeout); 

private:
    BOOL setLock(long);
};


#endif