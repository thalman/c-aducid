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

#ifndef __ADUCIDSOAP_H__
#define __ADUCIDSOAP_H__

#include "attrlist.h"
#include "myxml.h"


char *create_aducid_soap_xml(const char *operation, const char *xml);
char *create_aim_request_operation_xml(const char *operationName,
                                       const char *AIMName,
                                       const char *authId,
                                       const char *bindingKey,
                                       const char *methodName,
                                       const AducidAttributeList_t methodParameter,
                                       const AducidAttributeList_t personalObject,
                                       const char *AAIM2,
                                       const char *ilData,
                                       const char *peigReturnName);
char *create_aim_get_psl_attributes_xml(const char *authId,
                                        const char *bindingId,
                                        const char *AIMName,
                                        const char *authKey,
                                        const char *attributeSetName);
char *create_aim_execute_personal_object_xml(const char *authId,
                                             const char *AIMName,
                                             const char *authKey,
                                             const char *methodName,
                                             const char *personalObjectName,
                                             const char *personalObjectAlgorithm,
                                             AducidAttributeList_t personalObjectData,
                                             const char *ILID,
                                             const char *AAIM2,
                                             const char *ilData);
AducidAttributeList_t parse_personal_object(char *doc);
char *create_aim_close_session_xml(const char *authId, const char *AIMName, const char *authKey);

#endif
