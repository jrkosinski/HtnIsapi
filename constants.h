
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__


/*****************************************************************************************************
/* constants.h
/* -----------
/* Application global constants. 
/*
/****************************************************************************************************/

//buffer sizes 
#define DEFAULT_BUFLEN				355
#define URL_MAXLEN					1024
#define FILEPATH_MAXLEN				512
#define FILECONTENT_BUFLEN			524288
#define CONFIG_FILE_LINE_MAXLEN		4096

//config setting IDs
#define CFGID_WEBSITE_FILEPATH		110
#define CFGID_DEBUG_FILEPATH		120

//default refresh times
#define DEFAULT_CONFIG_REFRESH_MIN	60
#define DEFAULT_WEBSITE_REFRESH_MIN	5

//urls
#define CFGID_PASSTHRU_URL			130
#define CFGID_IGNORE_WEB_DIRS		140
#define CFGID_CONFIG_REFRESH_MIN	150
#define CFGID_WEBSITE_REFRESH_MIN	160


//environment variable setting
#define LOCATION_LIVE

#ifdef LOCATION_LOCALHOST
	#define WEBROOT						"C:\\inetpub\\wwwroot\\"
	#define CONFIG_FILEPATH				WEBROOT ## "agents\\config.txt"
	#define WEBSITES_FILEPATH			WEBROOT ## "agents\\websites.txt"
#endif 

#ifdef LOCATION_INTERNAL3
	#define WEBROOT						"D:\\webs\\hoteltravel\\"
	#define CONFIG_FILEPATH				WEBROOT ## "ISAPI\\HTNAffiliate\\config.txt"
	#define WEBSITES_FILEPATH			WEBROOT ## "ISAPI\\HTNAffiliate\\websites.txt"
#endif			

#ifdef LOCATION_LIVE
	//#define WEBROOT						"E:\\webs\\hoteltravel-V4\\"
	#define WEBROOT						"D:\\webs\\hoteltravelv4\\"
	#define CONFIG_FILEPATH				WEBROOT ## "agents\\config.txt"
	#define WEBSITES_FILEPATH			WEBROOT ## "agents\\websites.txt"
#endif			

#ifdef LOCATION_PRERELEASE101
	#define WEBROOT						"E:\\webs\\prerelease\\"
	#define CONFIG_FILEPATH				WEBROOT ## "agents\\config.txt"
	#define WEBSITES_FILEPATH			WEBROOT ## "agents\\websites.txt"
#endif									 


/* *** DEBUG MODE ***
	Comment this out to turn off debug mode
	Uncomment to turn on debug mode
*/
//#define __DEBUG__
/* *** DEBUG MODE ****/


//automatic shut-off of DEBUG when in live 
#ifdef LOCATION_LIVE
	#undef __DEBUG__
#endif



#endif