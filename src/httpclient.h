#ifndef __HTTPCLIENT_H__
#define __HTTPCLIENT_H__
#include "definitions.h"
#include <stddef.h>

typedef struct {
    int result;
    char *data;
    size_t length;
    char *header;
} HttpDataMemory;

void free_http_data_memory(HttpDataMemory *mem);
HttpDataMemory *http_get(char *url,bool useProxy);
char *http_get_text(char *url,bool useProxy);

#endif
