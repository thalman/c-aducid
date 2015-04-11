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

#include "httpclient.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#if defined _WIN32 || defined _WIN64
  #include<Windows.h>
  #ifdef _HAVE_WINHTTP
    #include<winhttp.h>
  #endif
  #ifdef _HAVE_LIBCURL
    #include <curl/curl.h>
  #endif
  #include "utils.h"
#else
  #include <curl/curl.h>
#endif

void free_http_data_memory(HttpDataMemory *mem) {
    if(mem) {
        if(mem->data) { free(mem->data); }
        if(mem->header) { free(mem->header); }
    }
}

size_t http_header_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize,newsize; 
    HttpDataMemory *mem = (HttpDataMemory *)userp;
        char *newmem;

    realsize = size * nmemb;
    if(mem == NULL) { return 0; } 
    if(mem->header) {
        newsize = realsize + strlen(mem->header) + 1;
        newmem = (char *)realloc(mem->header, newsize);
        if (newmem) { mem->header = newmem; } else { return 0; }
        strncat(mem->header,(char *)contents,realsize + 1);
    } else {
        newsize = realsize + 1;
        mem->header = (char *)malloc(newsize);
        if( mem->header == NULL ) { return 0; }
        strncpy(mem->header,(char *)contents,newsize);
    }
    mem->header[newsize-1] = 0;
    return realsize;
}

size_t http_data_memory_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize,newsize; 
    HttpDataMemory *mem = (HttpDataMemory *)userp;
        char *newmem;

    realsize = size * nmemb;
    newsize = realsize + mem->length;
    if(mem == NULL) { return 0; }
    if(mem->data) {
        newmem = (char *)realloc(mem->data, newsize);
        if (newmem) { mem->data = newmem; }
        else { return 0; }
    } else {
        mem->data = (char *)malloc(newsize);
    }
    if(mem->data == NULL) {
        /* out of memory! */ 
        return 0;
    }
    memcpy(&(mem->data[mem->length]), contents, realsize);
    mem->length += realsize;
    return realsize;
}

HttpDataMemory *http_get(char *url,bool useProxy) {
#ifdef _HAVE_WINHTTP
    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;
    char *host,*location, *newmem;
    LPWSTR hostw,locationw,buffer;
    int port;
    int error = 0;
    BOOL  bResults = FALSE;
    DWORD dwSize = 0,newSize;
    DWORD dwDownloaded = 0;
    HttpDataMemory *mem = NULL;

    mem = (HttpDataMemory *)malloc(sizeof(HttpDataMemory));
    if(!mem) return NULL;
    memset(mem,0,sizeof(HttpDataMemory));

    host = url_to_host(url);
    hostw = char_to_wchar(host);
    free(host);
    port = url_to_port(url);
    location = url_to_location(url);
    locationw = char_to_wchar(location);
    free(location);

    hSession = WinHttpOpen(L"libaducid/1.0", 
                           WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                           WINHTTP_NO_PROXY_NAME, 
                           WINHTTP_NO_PROXY_BYPASS, 0);
    if(hSession) {
        hConnect = WinHttpConnect( hSession, hostw, port, 0);
        if (hConnect)
            hRequest = WinHttpOpenRequest( hConnect, L"GET", locationw,
                                           NULL, WINHTTP_NO_REFERER, 
                                           WINHTTP_DEFAULT_ACCEPT_TYPES,
                                           (use_ssl(url) ? WINHTTP_FLAG_SECURE : 0) );
        if (hRequest) {
            DWORD dwOptionValue = WINHTTP_DISABLE_REDIRECTS;
            BOOL b = WinHttpSetOption(hRequest, WINHTTP_OPTION_DISABLE_FEATURE, &dwOptionValue, sizeof(dwOptionValue));
            bResults = WinHttpSendRequest( hRequest,
                                           WINHTTP_NO_ADDITIONAL_HEADERS,
                                           0, WINHTTP_NO_REQUEST_DATA, 0, 
                                           0, 0);
        }
        /* End the request. */
        if (bResults) {
            bResults = WinHttpReceiveResponse( hRequest, NULL);
            /* read headers first */
            WinHttpQueryHeaders( hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF,
                                 WINHTTP_HEADER_NAME_BY_INDEX, NULL,
                                 &dwSize, WINHTTP_NO_HEADER_INDEX);
            /* Allocate memory for the buffer. */
            if( GetLastError( ) == ERROR_INSUFFICIENT_BUFFER )
                {
                    buffer = (LPWSTR)malloc(dwSize);
                    /* Now, use WinHttpQueryHeaders to retrieve the header. */
                    bResults = WinHttpQueryHeaders( hRequest,
                                                    WINHTTP_QUERY_RAW_HEADERS_CRLF,
                                                    WINHTTP_HEADER_NAME_BY_INDEX,
                                                    buffer, &dwSize,
                                                    WINHTTP_NO_HEADER_INDEX);
                    mem->header = wchar_to_char(buffer);
                    free(buffer);
                }
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
                                newmem = (char *)realloc(mem->data, newSize);
                                if (newmem) { mem->data = newmem; }
                                else { safe_free(mem->data); mem->data = NULL; }
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
    /* if error ...*/
    return mem;
#else
    CURL *handle;
    HttpDataMemory *chunk;

   
    chunk = (HttpDataMemory *)malloc(sizeof(HttpDataMemory));
    if(!chunk) return NULL;
    memset(chunk,0,sizeof(HttpDataMemory));

    handle = curl_easy_init();
    if(!handle) {
        free(chunk);
        return NULL;
    }
    curl_easy_setopt(handle, CURLOPT_URL, url);
    if(!useProxy) {
        curl_easy_setopt(handle, CURLOPT_PROXY, "");
    }
    /* send all data to this function  */ 
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, http_data_memory_callback);
    /* we pass our 'chunk' struct to the callback function */ 
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)chunk);
    
    curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, http_header_memory_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEHEADER, (void *)chunk);
    
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, false);
    /* Perform the request, res will get the return code */ 
    chunk->result = curl_easy_perform(handle);
    /* Check for errors */
    curl_easy_cleanup(handle);
    return chunk;
#endif
}

char *http_get_text(char *url,bool useProxy){
    HttpDataMemory *chunk;
    char *result;
    
    chunk = http_get(url,useProxy);
    if( (chunk == NULL) || (chunk->data == NULL) ) { free_http_data_memory(chunk); return NULL; }
    result = (char *)malloc(chunk->length+1);
    if(result == NULL) {
        /* out of memory */
        free_http_data_memory(chunk);
        return NULL;
    }
    memcpy(result,chunk->data,chunk->length);
    result[chunk->length] = 0;
    free_http_data_memory(chunk);
    return result;
}
