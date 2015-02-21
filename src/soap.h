#ifndef __SOAP_H__
#define __SOAP_H__

#if defined _WIN32 || defined _WIN64
#include <windows.h>

#else
#include <stddef.h>

typedef struct {
  char *memory;
  size_t size;
} MemoryStruct;
#endif

/* size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp); */

char *soap_request(const char *URL, const char *action, const char *request);

#endif
