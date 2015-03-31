#ifndef __SOAP_H__
#define __SOAP_H__

#include "definitions.h"

#ifdef _HAVE_LIBCURL

typedef struct {
  char *memory;
  size_t size;
} MemoryStruct;

#endif

char *soap_request(const char *URL, const char *action, const char *request);

#endif
