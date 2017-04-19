#ifndef __CTIMER_H__
#define __CTIMER_H__


/*****************************************************************************************************
/* CTimer
/* ------
/* Basic timer class; will return the amount of time between calls to the Start() and Stop() methods. 
/* 
/* If the timer is currently running (IsRunning == TRUE), will return the amount of time between 
/* the Start() call and NOW. Uses SYSTEMTIME. 
/*
/****************************************************************************************************/
class CTimer
{
private:
	SYSTEMTIME _stStart;
	SYSTEMTIME _stStop;

public:
	// TRUE if Start() has been called, but Stop() has not yet been called. 
	BOOL IsRunning; 

public:
	//////////////
	// Constructor
	// -----------
	// Sets the start and stop time to NOW, sets IsRunning = FALSE. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	CTimer();
	~CTimer() {};

public:
	////////
	// Start
	// -----
	// Sets the start and stop time to NOW, sets IsRunning = TRUE. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	void Start();
	////////
	// Start
	// -----
	// Sets the start and stop time to the given value, sets IsRunning = TRUE. 
	//		startTime - the assumed start/stop time to set. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	void Start(SYSTEMTIME startTime); 
	///////
	// Stop
	// ----
	// Sets the stop time to NOW, sets IsRunning = FALSE.
	///////////////////////////////////////////////////////////////////////////////////////////////
	void Stop(); 
	////////
	// Reset
	// -----
	// Sets the start and stop time both equal to NOW; if the timer is running, it stays running.
	// If the timer is currently stopped, stays stopped. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	void Reset();
	///////////////////////
	// GetTotalMilliseconds
	// --------------------
	// If IsRunning == TRUE, gets the total number of milliseconds elapsed between the StartTime
	// and NOW. If IsRunning == FALSE, gets the total number of milliseconds elapsed between the 
	// StartTime and the StopTime. (invalid when stop time occurs on a different day than 
	// start time) 
	///////////////////////////////////////////////////////////////////////////////////////////////
	long GetTotalMilliseconds();
	//////////////////
	// GetTotalSeconds
	// ---------------
	// If IsRunning == TRUE, gets the total number of seconds elapsed between the StartTime
	// and NOW. If IsRunning == FALSE, gets the total number of seconds elapsed between the 
	// StartTime and the StopTime.  (invalid when stop time occurs on a different day than 
	// start time)
	///////////////////////////////////////////////////////////////////////////////////////////////
	long GetTotalSeconds();
	//////////////////
	// GetTotalMinutes
	// ---------------
	// If IsRunning == TRUE, gets the total number of minutes elapsed between the StartTime
	// and NOW. If IsRunning == FALSE, gets the total number of minutes elapsed between the 
	// StartTime and the StopTime. (invalid when stop time occurs on a different day than 
	// start time)
	///////////////////////////////////////////////////////////////////////////////////////////////
	long GetTotalMinutes();

private:
	long getTotalMilliseconds(SYSTEMTIME* pTime);
	long getTotalSeconds(SYSTEMTIME* pTime);
	long getTotalMinutes(SYSTEMTIME* pTime);
};


#endif