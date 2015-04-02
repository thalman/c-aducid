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
#include "soap.h"
#include "utils.h"
#include "httpclient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _HAVE_WINHTTP
/* windows soap request */
#include <windows.h>
#include <winhttp.h>

char *soap_request_raw(const char *URL, const char *action, const char *request)
{
    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;
    char *host,*location,*result;
    LPWSTR hostw,locationw;
    int port;
    BOOL  bResults = FALSE;
    DWORD dwSize = 0,newSize;
    DWORD dwDownloaded = 0;
    HttpDataMemory *mem = NULL;
    int error = 0;

    const char *headerFormat = "Content-Type: Text/xml\nSOAPAction: \"%s\"";
    LPWSTR headerw = NULL;
    char *header;

    /* check params */
    if( URL == NULL || action == NULL || request == NULL ) { return NULL; }

    mem = (HttpDataMemory *)malloc(sizeof(HttpDataMemory));
    if(!mem) return NULL;
    memset(mem,0,sizeof(HttpDataMemory));

    host = url_to_host(URL);
    hostw = char_to_wchar(host);
    free(host);

    port = url_to_port(URL);

    location = url_to_location(URL);
    locationw = char_to_wchar(location);
    free(location);

    dwSize = strlen(headerFormat) + strlen(action);
    header = (char *)malloc(dwSize);
    if(header) {
        memset(header,0,dwSize);
        _snprintf(header,dwSize-1,headerFormat,action);
        headerw = char_to_wchar(header);
        free(header);
    }
    hSession = WinHttpOpen(L"libaducid/1.0", 
                           WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                           WINHTTP_NO_PROXY_NAME, 
                           WINHTTP_NO_PROXY_BYPASS, 0);
    if(hSession) {
        hConnect = WinHttpConnect( hSession, hostw, port, 0);
        if (hConnect)
            hRequest = WinHttpOpenRequest( hConnect, L"POST", locationw,
                                           NULL, WINHTTP_NO_REFERER, 
                                           WINHTTP_DEFAULT_ACCEPT_TYPES,
                                           (use_ssl(URL) ? WINHTTP_FLAG_SECURE : 0) );
        if (hRequest) {
            DWORD dwOptionValue = WINHTTP_DISABLE_REDIRECTS;
            WinHttpSetOption(hRequest, WINHTTP_OPTION_DISABLE_FEATURE, &dwOptionValue, sizeof(dwOptionValue));
            WinHttpAddRequestHeaders( hRequest, 
                                      headerw,
                                      (ULONG)-1L,
                                      WINHTTP_ADDREQ_FLAG_ADD );
			char *rq = strdup(request);
            bResults = WinHttpSendRequest( hRequest,
                                           WINHTTP_NO_ADDITIONAL_HEADERS,
                                           0, rq, strlen(rq),
                                           strlen(rq), 0);
			safe_free(rq);
        }
        /* End the request. */
        if (bResults) {
            bResults = WinHttpReceiveResponse( hRequest, NULL);
            /* Keep checking for data until there is nothing left. */
            if (bResults)
                do 
                {
                    /* Check for available data. */
                    dwSize = 0;
                    if (!WinHttpQueryDataAvailable( hRequest, &dwSize))
                        error = GetLastError();
                    if(dwSize) {
                        /* Allocate space for the buffer. */
                        newSize = dwSize + mem->length ;
                        if(mem->data) {
                            mem->data = (char *)realloc(mem->data, newSize);
                        } else {
                            mem->data = (char *)malloc(newSize);
                        }
                        if(mem->data) {
                            /* Read the Data. */
                            if (!WinHttpReadData( hRequest, (LPVOID)&(mem->data[mem->length]), 
                                                  dwSize, &dwDownloaded)) {
                                error = GetLastError();
                            } else {
                                mem->length = newSize;
                            }
                        }
                    }
                } while (dwSize > 0);
        }
        /* Report any errors. */
        if (!bResults) {
            error = GetLastError();
        }
    }
    /* Close any open handles. */
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
    if (hostw) free(hostw);
    if (locationw) free(locationw);
    if (headerw) free(headerw);
    result = NULL;
    if( error == 0) {
        if(mem && mem->length) {
            result = (char *)malloc(mem->length+1);
            if(result) {
                memset(result,0,mem->length+1);
                memcpy(result,mem->data,mem->length);
            }
        }
    }
    /* free mem */
    if(mem) {
        if(mem->header) free(mem->header);
        if(mem->data) free(mem->data);
        free(mem);
    }
    return result;
}
/* windows soap request - end*/
char *soap_request(const char *URL, const char *action, const char *request)
{
    char *result = NULL;
    int retry = 3;
    while( result == NULL && retry ) {
        retry--;
        result = soap_request_raw( URL, action, request);
    }
    return result;
}

#else
/* libcurl soap request */
#include <curl/curl.h>

size_t
write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userp;
 
    mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) {
        /* out of memory! */ 
        return 0;
    }
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
 
    return realsize;
}
 
char *soap_request(const char *URL, const char *action, const char *request)
{
    CURL *curl_handle;
    CURLcode res;
    struct curl_slist *headers = NULL;
    MemoryStruct chunk;
    char soapAction[256];
 
    chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */ 
    chunk.size = 0;    /* no data at this point */ 
 
    curl_global_init(CURL_GLOBAL_ALL);
 
    /* init the curl session */ 
    curl_handle = curl_easy_init();
 
    /* specify URL to get */ 
    curl_easy_setopt(curl_handle, CURLOPT_URL, URL);
 
    /* send all data to this function  */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_memory_callback);
 
    /* we pass our 'chunk' struct to the callback function */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        
    /* some servers don't like requests that are made without a user-agent
       field, so we provide one */ 
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "aducid-sdk-agent/1.0");

    curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, request);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, strlen (request)); /* Not strictly necessary, but eh. */
    /* SOAP headers */
    headers = curl_slist_append(headers,"Content-Type: text/xml");
    snprintf(soapAction,sizeof(soapAction)-1,"SOAPAction: \"%s\"",action);
    headers = curl_slist_append(headers,soapAction);
    res = curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);
    /* get it! */
    res = curl_easy_perform(curl_handle);

    curl_slist_free_all(headers);
    /* check for errors */
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        if(chunk.memory) {
            free(chunk.memory);
            chunk.memory = NULL;
        }
    }
    /* cleanup curl stuff */ 
    curl_easy_cleanup(curl_handle);
    /* we're done with libcurl, so clean it up */ 
    curl_global_cleanup();
    return chunk.memory;
}
/* linux soap request - end */
#endif
