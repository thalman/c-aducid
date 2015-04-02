/* Copyright(c) 2015 ANECT a.s.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#ifdef _MSC_VER
  // this is MS compiler, let's use winhttp
  #define _HAVE_WINHTTP
  #undef  _HAVE_LIBCURL
#else
  // when there are issues with winhttp library, we can use libcurl
  // but it might come frou outside
  #ifdef _HAVE_WINHTTP
    #undef _HAVE_LIBCURL
  #else
    #define _HAVE_LIBCURL
    #undef  _HAVE_WINHTTP
  #endif
#endif

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

