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

#ifndef __MYXML_H__
#define __MYXML_H__

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

char *myxml_find_xpath_first(const char *doc, const char *xpath);
char *myxml_extract_node_name(char *attr, bool removeNS);
bool  myxml_is_node_single(char *attr);
char *myxml_get_node_text(char *xml);
char *myxml_get_node_attribute(char *xml, char *attrname);

#ifdef __cplusplus
}
#endif

#endif
