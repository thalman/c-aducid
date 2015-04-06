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

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if defined _WIN32 || defined _WIN32
#include<Windows.h>
#else
#include <curl/curl.h>
#endif

char *dyn_strcat(char *string1, char *string2, bool frees2) {
    size_t len;
    char *res;
    
    if( string2 == NULL ) { return string1; }
    if( string1 == NULL ) {
        len = strlen(string2);
        res = (char *)malloc(len+1);
        if(!res) {
            if(frees2) { free(string2); }
            return NULL;
        }
        strncpy(res,string2,len+1);
    } else {
        len = strlen(string1) + strlen(string2);
        res = (char *)realloc(string1,len+1);
        if(!res) {
            if(frees2) { free(string2); }
            return NULL;
        }
        strncat(res,string2,strlen(string2) + 1);       
    }
    if(frees2 && (string2 != NULL) ) { free(string2); }
    return res;
}

char *xml_get_single_node_text(char *doc, char *xpath){
    char *node = myxml_find_xpath_first(doc,xpath);
    return myxml_get_node_text(node);
}

void safe_free(void *ptr) {
    if(ptr) { free(ptr); }
}

char *url_to_host_and_port(const char *URL) {
    char *b,*e;
    char *result = NULL;
    int len;

    b = strstr(URL,"://");
    if(b) {
        b = &b[3];
        e = strstr(b,"/");
        if(e) {
            len = e - b;
            result = (char *)malloc(len+1);
            memset(result,0,len+1);
            strncpy(result,b,len);
            return result;
        } else {
            /* whole string */
            return strdup(b);
        }
    }
    return NULL;
}

char *url_to_host(const char *URL) {
    char *hp,*colon;

    hp = url_to_host_and_port(URL);
    if(hp) {
        colon = strstr(hp,":");
        if(colon) {
            colon[0] = 0;
        }
    }
    return hp;
}

char *url_to_location(const char *URL) {
    char *p;

    p = strstr(URL,"://");
    if(p) {
        p = &p[3];
        p = strstr(p,"/");
        if(p) {
            p++;
            if( strlen(p) ) {
                return strdup(p);
            }
        }
    }
    return NULL;
}

bool use_ssl(const char *URL) {
    return ( URL[4] == 's' || URL[4] == 'S');
}

int url_to_port(const char *URL) {
    char *hp,*colon;
    int port;

    port = 80;
    if( use_ssl(URL) ) {
        port = 443;
    }
    hp = url_to_host_and_port(URL);
    if(hp) {
        colon = strstr(hp,":");
        if(colon) {
            colon++;
            port = atoi(colon);
        }
        free(hp);
    }
    return port;
}
#if defined _WIN32 || defined _WIN64
LPWSTR char_to_wchar(char *ch) {
    LPWSTR result;
    int size;
        
    if(ch == NULL) { return NULL; }
    size = mbstowcs(NULL, ch, 0);
    result = (LPWSTR)malloc( (size + 1) * sizeof( wchar_t ) );
    if (! result) {
        return NULL;
    }
    size = mbstowcs( result, ch, size + 1);
    if (size == (size_t) (-1)) {
        free(result);
        return NULL;
    }
    return result;
}

char *wchar_to_char(LPWSTR wch) {
    int size,copied;
    char *buffer;

    size = wcslen(wch)+2;
    buffer = (char *)malloc(size);
    if(buffer == NULL) {
        return NULL;
    }
    memset(buffer,0,size);
    copied = wcstombs(buffer,wch,size-1);
    while(copied == size-1) {
        size *= 2;
        char *old = buffer;
        buffer = (char *)realloc(buffer,size);
        if( buffer == NULL ) {
            free(old);
            return NULL;
        }
        memset(buffer,0,size);
        copied = wcstombs(buffer,wch,size-1);
    }
    return buffer; 
}
#endif

char *url_decode(const char *encoded) {
    char c, *result = NULL,hex[5];
    unsigned int i,j;
    unsigned int x = 0;

    if( ! encoded ) { return NULL; }
    result = (char *)malloc( strlen(encoded) + 1 );
    if(!result) { return NULL; }
    if(!result) { free(result); return NULL; }
    memset(result,0,strlen(encoded) + 1);
    if(result) {
        i = 0;
        j = 0;
        while(i < strlen(encoded) ) {
            c = encoded[i];
            if(c == '+' ) {
                result[j] = ' ';
            } else if( c == '%' ) {
                if(strlen(&encoded[i]) >= 3 ) {
                    /* decode */
                    hex[0] = encoded[i+1];
                    hex[1] = encoded[i+2];
                    hex[3] = 0;
                    x = 0;
                    if( sscanf(hex, "%x", &x) != EOF ) {
                        result[j] = x;
                    } else {
                        result[j] = ' ';
                    }
                    i += 2;
                }
            } else {
                result[j] = c;
            }
            i++;
            j++;

        }
    }
    return result;
}

char *url_encode(const char *decoded) {
    char *result = NULL,c;
    unsigned int i,j;

    result = (char *)malloc( strlen(decoded) * 3 + 1 ); /* max size if every character escaped */
    memset(result,0, strlen(decoded) * 3 + 1 );
    if(result) {
        i = 0;
        j = 0;
        while(i < strlen(decoded) ) {
            c = decoded[i];
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                result[j] = c;
            }
            else if (c == ' ')  {
                result[j] = '+';
            }
            else {
                result[j] = '%';
                sprintf(&result[j+1],"%02X",c);
                j += 2;
            }
            i++;
            j++;
        }
    }
    return result;
}

//  return str_replace( array( "&", "\"", "<", ">" ), array( "&amp;", "&quot;", "&lt;", "&gt;"), $text );

char *
xml_encode( const char *text )
{
    const char *p;
    char *newtext;
    static int step = 100;
    int index;
    
    if( ! text ) return NULL;
    int size = strlen(text) + step;
    newtext = malloc(size);
    if( ! newtext ) return NULL;
    p = text;
    index = 0;
    while( *p ) {
        switch( *p ) {
        case '&':
            memcpy(&newtext[index],"&amp;",5);
            index += 5;
            ++p;
            break;
        case '"':
            memcpy(&newtext[index],"&quot;",6);
            index += 6;
            ++p;
            break;
        case '<':
            memcpy(&newtext[index],"&lt;",4);
            index += 4;
            ++p;
            break;
        case '>':
            memcpy(&newtext[index],"&gt;",4);
            index += 4;
            ++p;
            break;
        default:
            newtext[index] = *p;
            ++index;
            ++p;
        }
        if( index + 10 > size ) {
            size += step;
            char *newt = realloc( newtext, size );
            if( !newt ) { free(newtext); return NULL; }
            newtext = newt;
        }
    }
    newtext[index] = 0;
    return newtext;
}

char *
xml_decode( const char *text )
{
    const char *src;
    char *newtext, *dst;
    int index;
    
    if( ! text ) return NULL;
    newtext = malloc( strlen(text) + 1 );
    if( ! newtext ) return NULL;

    src = text;
    dst = newtext;
    index = 0;
    while( *src ) {
        if( *src == '&' ) {
            if( strncmp( src, "&amp;", 5 ) == 0 ) {
                *dst = '&';
                src = &src[5];
            } else if ( strncmp( src, "&quot;", 6) == 0 ) {
                *dst = '"';
                src = &src[6];
            } else if ( strncmp( src, "&gt;", 4) == 0 ) {
                *dst = '>';
                src = &src[4];
            } else if ( strncmp( src, "&lt;", 4) == 0 ) {
                *dst = '<';
                src = &src[4];
            } else {
                // unknown tag, copy it
                *dst = *src;
                ++src;
                ++dst;
            }
            ++dst;
        } else {
            *dst = *src;
            ++src;
            ++dst;
        }
    }
    *dst = 0;
    return newtext;
}
