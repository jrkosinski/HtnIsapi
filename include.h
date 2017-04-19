
#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/*****************************************************************************************************
/* includes.h
/* ----------
/* Application global 'includes' file - #include all necessary files. 
/*
/****************************************************************************************************/

// Windows 
#include <afx.h>
#include <afxwin.h>
#include <afxmt.h>		
#include <afxext.h>
#include <afxisapi.h>
#include <tchar.h>

// util
#include "constants.h"
#include "utility.h"

// classes 
#include "CIsapi.h"
#include "CSafeString.h"
#include "CTimer.h"
#include "CResourceFile.h"
#include "CWebsiteList.h"
#include "CConfigFile.h"
#include "CReaderWriterLock.h"
#include "CWriterLock.h"
#include "CReaderLock.h"
#include "CSearchBuffer.h"


//implementations
#include "utility.impl.h"
#include "CSafeString.impl.h"
#include "CTimer.impl.h"
#include "CResourceFile.impl.h"
#include "CWebsiteList.impl.h"
#include "CConfigFile.impl.h"
#include "CReaderWriterLock.impl.h"
#include "CWriterLock.impl.h"
#include "CReaderLock.impl.h"
#include "CSearchBuffer.impl.h"


#endif