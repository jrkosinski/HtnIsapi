#ifndef __CWEBSITELIST_H__
#define __CWEBSITELIST_H__

#include "CTimer.h"
#include "CSafeString.h"
#include "CResourceFile.h"
#include "CSearchBuffer.h"


/*****************************************************************************************************
/* CWebsiteList
/* ------------
/* Encapsulates the ISAPI's list of Affiliate websites, read in from a text file and refreshed every
/* N minutes (read in on first time requested, then refreshed first time requested after N minutes). 
/*
/* Stores the text in ISAPI memory.
/*
/****************************************************************************************************/
class CWebsiteList : public CResourceFile
{
private:
	CSearchBuffer _searchBuffer;

public:
	//////////////
	// Constructor
	// -----------
	///////////////////////////////////////////////////////////////////////////////////////////////
	CWebsiteList() : CResourceFile(DEFAULT_WEBSITE_REFRESH_MIN, WEBSITES_FILEPATH) { }
	~CWebsiteList() {}

public:
	/////////////
	// SearchList
	// ----------
	// Searches the list for the given string. Method returns TRUE if the string is an exact 
	// match with one line of text (lines delimited by standard ASCII linebreak). 
	// 
	// String comparison is case-insensitive. 
	///////////////////////////////////////////////////////////////////////////////////////////////
	BOOL SearchList(CSafeString* pSearch); 

protected: 
	void postRefresh(); 
};


#endif