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
