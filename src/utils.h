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

#ifndef __UTILS_H__
#define __UTILS_H__

#include "definitions.h"
#include "myxml.h"
#if defined _WIN32 || defined _WIN64
#include<Windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

char *dyn_strcat(char *string1,char *string2, bool frees2);
char *xml_get_single_node_text(char *doc, char *xpath);
void safe_free(void *ptr);
char *url_decode(const char *encoded);
char *url_encode(const char *decoded);
char *url_to_host_and_port(const char *URL);
char *url_to_host(const char *URL);
char *url_to_location(const char *URL);
bool use_ssl(const char *URL);
int url_to_port(const char *URL);
char *xml_decode( const char *text );
char *xml_encode( const char *text );

#if defined _WIN32 || defined _WIN64
LPWSTR char_to_wchar(char *ch);
char *wchar_to_char(LPWSTR wch);
#endif

#ifdef __cplusplus
}
#endif

#endif
