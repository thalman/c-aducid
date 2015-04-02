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

#ifndef __ADUCIDPRIVATE_H__
#define __ADUCIDPRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

const char *
aducid_request_operation(
    AducidHandle_t handle,
    AducidOperation_t operation,
    const char* methodName,
    const AducidAttributeList_t methodParameters,
    const AducidAttributeList_t personalObject,
    const char *AAIM2,
    const char *ilData,
    const char *peigReturnName
);


#ifdef __cplusplus
}
#endif

#endif
