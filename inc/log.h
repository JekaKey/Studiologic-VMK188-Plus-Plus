#ifndef SYSLOG_H_
#define SYSLOG_H_

#include <stdio.h>

//#define DEBUG_SD
//#define DEBUG

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


#endif /* SYSLOG_H_ */
