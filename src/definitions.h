#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  /* on windows */
  #ifdef __GNUC__
    #define ADUCID_PUBLIC_FUNC __attribute__ ((dllexport))
  #else
    #define ADUCID_PUBLIC_FUNC __declspec(dllexport)
  #endif
  #define ADUCID_LOCAL_FUNC
#else
  /* on posix */
  #if __GNUC__ >= 4
    #define ADUCID_PUBLIC_FUNC __attribute__ ((visibility ("default")))
    #define ADUCID_LOCAL_FUNC  __attribute__ ((visibility ("hidden")))
  #else
    #define ADUCID_PUBLIC_FUNC
    #define ADUCID_LOCAL_FUNC
  #endif
#endif


#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
/* windows includes */
#include<stdbool.h>
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
/* posix includes */
#include<stdbool.h>
#endif

/* common includes */
#include "aducid.h"
#include "aducidprivate.h"

#endif

