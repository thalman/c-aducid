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

#include "definitions.h"
#include "httpclient.h"
#include "utils.h"
#include <string.h>

#if defined _WIN32 || defined _WIN64
/* nothing for win */
#else
#include <curl/curl.h>
#endif

#include "definitions.h"

static char *peigProxyInterface = "http://127.0.0.1:44240/ADUCID/PEIG/auth";

ADUCID_PUBLIC_FUNC bool
aducid_peig_invoke(AducidHandle_t handle)
{
    char *encoded;
    char *raurl = NULL;
    char *raReply;
    bool result;

    if(!handle) return false;
    if( handle->authId == NULL ) return false;

    raurl = dyn_strcat(raurl,peigProxyInterface,false);

    if(handle->authId) {
        encoded = url_encode(handle->authId);
        raurl = dyn_strcat(raurl,"?id=",false);
        raurl = dyn_strcat(raurl,encoded,false);
        free(encoded);
    }
    if(handle->bindingId) {
        encoded = url_encode(handle->bindingId);
        raurl = dyn_strcat(raurl,"&bindingId=",false);
        raurl = dyn_strcat(raurl,encoded,false);
        free(encoded);
    }
    if(handle->bindingKey) {
        encoded = url_encode(handle->bindingKey);
        raurl = dyn_strcat(raurl,"&bindingKey=",false);
        raurl = dyn_strcat(raurl,encoded,false);
        free(encoded);
    }
    if(handle->R3) {
        encoded = url_encode(handle->R3);
        raurl = dyn_strcat(raurl,"&url=",false);
        raurl = dyn_strcat(raurl,encoded,false);
        free(encoded);
    }
    raReply = http_get_text(raurl,false);
    free(raurl);
    if(raReply == NULL) {
        return false;
    } else {
        result = strncasecmp(raReply,"true",4) == 0;
        free(raReply);
        return result;
    }
}

ADUCID_PUBLIC_FUNC const char *
aducid_peig_get_authkey(AducidHandle_t handle)
{
    static char *notUsed = "http://not.used/";
    char *encodedAuthId;
    char *encodedReturnUrl;
    char *curlAuthKey = NULL;
    char *raurl = NULL;
    HttpDataMemory *raReply;
    char *i,*j;

    if(!handle || !handle->authId) return NULL;

    aducid_set_authkey(handle,NULL);
    encodedAuthId = url_encode(handle->authId);
    encodedReturnUrl = url_encode(notUsed);

    raurl = dyn_strcat(raurl,peigProxyInterface,false);
    raurl = dyn_strcat(raurl,"?authId=",false);
    raurl = dyn_strcat(raurl,encodedAuthId,false);
    raurl = dyn_strcat(raurl,"&returnUrl=",false);
    raurl = dyn_strcat(raurl,encodedReturnUrl,false);

    raReply = http_get(raurl,false);

    free(raurl);
    free(encodedReturnUrl);
    free(encodedAuthId);
    if(raReply == NULL) {
        return NULL;
    }
    i = strstr(raReply->header,"\nLocation:");
    if(i) {
        i++;
        j = strstr(i,"\n");
        if(j) { *j = 0; }
        j = strstr(i,"&authKey=");
        if( j == NULL ) {
            j = strstr(i,"?authKey=");
        }
        if(j) {
            j = &j[9];
	    /* remove following parameter */
            i = strstr(j,"&");
            if(i) { *i = 0; }
	    /* remove trailing whitespace */
            i = strstr(j," ");
            if(i) { *i = 0; }
            i = strstr(j,"\r");
            if(i) { *i = 0; }
            i = strstr(j,"\n");
            if(i) { *i = 0; }
            curlAuthKey = url_decode(j);
            if(curlAuthKey) { aducid_set_authkey(handle,curlAuthKey); }
            free(curlAuthKey);
        }
    }
    free_http_data_memory(raReply);
    return (const char *)aducid_get_authkey(handle);
}

ADUCID_PUBLIC_FUNC char *
aducid_get_aimproxy_url(AducidHandle_t handle)
{
    char *aimproxyurl;
    char *p;
    char *encoded;
    
    if(! handle) return NULL;
    if(! handle->R4) return NULL;

    aimproxyurl = strdup(handle->R4);
    if(!aimproxyurl) return NULL;
    p = strstr(aimproxyurl,"://");
    if(p) {
        p = &p[3];
        p = strstr(p,"/");
        if(p) { p[0] = 0; }
    }
    aimproxyurl =  dyn_strcat(aimproxyurl, "/AIM-proxy/process?",false);
    if(handle->authId) {
        encoded = url_encode(handle->authId);
        aimproxyurl =  dyn_strcat(aimproxyurl, "authId=",false);
        aimproxyurl =  dyn_strcat(aimproxyurl, encoded,false);
        free(encoded);
    }
    if(handle->bindingId) {
        encoded = url_encode(handle->bindingId);
        if(aimproxyurl[strlen(aimproxyurl)-1] != '?') aimproxyurl = dyn_strcat(aimproxyurl, "&",false);
        aimproxyurl =  dyn_strcat(aimproxyurl, "bindingId=",false);
        aimproxyurl =  dyn_strcat(aimproxyurl, encoded,false);
        free(encoded);
    }
    if(handle->bindingKey) {
        encoded = url_encode(handle->bindingKey);
        if(aimproxyurl[strlen(aimproxyurl)-1] != '?') aimproxyurl = dyn_strcat(aimproxyurl, "&",false);
        aimproxyurl = dyn_strcat(aimproxyurl, "bindingKey=",false);
        aimproxyurl = dyn_strcat(aimproxyurl, encoded,false);
        free(encoded);
    }
    return aimproxyurl;
}

ADUCID_PUBLIC_FUNC char *
aducid_get_aducid_url(AducidHandle_t handle)
{
    char *url = NULL;
    char *encoded;
    
    if(! handle ) return NULL;
    url = dyn_strcat(url,"aducid://callback?",false);
    if(handle->authId) {
        encoded = url_encode(handle->authId);
        url = dyn_strcat(url, "authId=",false);
        url = dyn_strcat(url, encoded,false);
        free(encoded);
    }
    if(handle->R3) {
        encoded = url_encode(handle->R3);
        if(url[strlen(url)-1] != '?') url = dyn_strcat(url, "&",false);
        url = dyn_strcat(url, "r3Url=",false);
        url = dyn_strcat(url, encoded,false);
        free(encoded);
    }
    if(handle->bindingId) {
        encoded = url_encode(handle->bindingId);
        url = dyn_strcat(url, "&bindingId=",false);
        url = dyn_strcat(url, encoded,false);
        free(encoded);
    }
    if(handle->bindingKey) {
        encoded = url_encode(handle->bindingKey);
        url = dyn_strcat(url, "&bindingKey=",false);
        url = dyn_strcat(url, encoded,false);
        free(encoded);
    }
    return url;
}
