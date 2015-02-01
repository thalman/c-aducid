#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if defined(_WIN32) || defined(_WIN32) 
#include<Windows.h>
#else
#include <curl/curl.h>
#endif

char *dyn_strcat(char *string1,char *string2, bool frees2) {
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

char *xml_get_single_node_text(xmlDocPtr doc, xmlChar *xpath){
    xmlChar *node = myxml_find_xpath_first(doc,xpath);
    return myxml_get_node_text(node);
}

void safe_free(void *ptr) {
    if(ptr) { free(ptr); }
}

char *url_to_host_and_port(char *URL) {
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

char *url_to_host(char *URL) {
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

char *url_to_location(char *URL) {
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

bool use_ssl(char *URL) {
    return ( URL[4] == 's' || URL[4] == 'S');
}

int url_to_port(char *URL) {
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
#ifdef _WIN32
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
        buffer = (char *)realloc(buffer,size);
        if( buffer == NULL ) {
            return NULL;
        }
        memset(buffer,0,size);
        copied = wcstombs(buffer,wch,size-1);
    }
    return buffer; 
}
#endif

char *url_decode(char *encoded) {
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

char *url_encode(char *decoded) {
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
