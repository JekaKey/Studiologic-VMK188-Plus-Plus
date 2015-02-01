#ifndef SYSLOG_H_
#define SYSLOG_H_

#include <stdio.h>

//#define DEBUG_SD
//#define DEBUG
//#define DEBUG_MENU

#ifdef DEBUG_SD
#define logf(...) printf (__VA_ARGS__);
#else
#define logf(...)
#endif



#ifdef DEBUG
#define PRINTF(...) printf (__VA_ARGS__);
#else
#define PRINTF(...)
#endif



#ifdef DEBUG_MENU
#define LOG(...) printf (__VA_ARGS__);
#else
#define LOG(...)
#endif


#endif /* SYSLOG_H_ */
