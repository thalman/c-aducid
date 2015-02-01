#ifndef _DEFINITION_H_
#define _DEFINITION_H_


#if defined _WIN32 || defined _WIN64
#ifndef bool
#define bool int
#define false 0
#define true 1
#endif
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define strdup _strdup
#define sleep(x) Sleep(1000*x)
#pragma comment(lib, "winhttp.lib")
#else
#include<stdbool.h>
#endif

#endif

