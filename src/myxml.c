#include "definitions.h"
#include "myxml.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

xmlChar *myxml_find_xpath_first(xmlDocPtr doc, xmlChar *xpath) {
    xmlChar *attr, *pos, *p, *q;
    int size;
    if( ! xpath ) return NULL;
    if( ! doc ) return NULL;
    if( ( strlen(xpath) < 3 ) || xpath[0] != '/' || xpath[1] != '/' ) {
        /* invalid/not implemented xpath */
        return NULL;
    }
    size = strlen(xpath);
    attr = malloc(size);
    if(attr == NULL) return NULL;
    memset(attr,0,size);
    
    strncpy(attr,"<",size);
    strncat(attr,&xpath[2],size);

    pos = strstr(doc,attr);
    while( pos ){
        p = &pos[strlen(attr)];
        if( isspace(p[0]) || p[0] == '/' || p[0] == '>' ) {
            free(attr);
            return pos;
        }
        pos = strstr(p,attr);
    }
    /* try with namespace */
    strncpy(attr,":",size);
    strncat(attr,&xpath[2],size);
    pos = strstr(doc,attr);
    while( pos ){
        p = &pos[strlen(attr)];
        if( isspace(p[0]) || p[0] == '/' || p[0] == '>' ) {
            /* lets check ns */
            q = pos;
            while( (q != doc) && (*q != '<') ) {
                q--;
                if( *q == '<' ) {
                    free(attr);
                    return q;
                }
                if( !( isalnum(*q) || *q == '_' || *q == '-' ) ) {
                    /* this is invalid */
                    break;
                }
            }
        }
        pos = strstr(p,attr);
    }
    free(attr);
    return NULL;
}

xmlChar *myxml_extract_node_name(xmlChar *attr, bool removeNS) {
    xmlChar *b,*name,*newname;
    int cnt = 0;

    if(!attr) { return NULL; }
    if(attr[0] != '<') { return NULL; }

    b = &attr[1];
    while( b[cnt] && ( ! isspace(b[cnt]) ) &&  ( b[cnt] != '/' ) &&  ( b[cnt] != '>' ) ) {
        cnt++;
    }
    name = malloc(cnt + 1);
    if(!name) { return NULL; }
    memset(name,0,cnt+1);
    strncpy(name,b,cnt);
    if(removeNS) {
        b = strstr(name,":");
        if(b) {
            b++;
            newname = malloc(strlen(b) + 1);
            if(!newname) { free(name); return NULL; }
            strncpy(newname,b,strlen(b)+1);
            free(name);
            return newname;
        }
    }
    return name;
}


bool myxml_is_node_single(xmlChar *attr) {
    xmlChar *p;

    if( attr == NULL ) { return false; }
    if( attr[0] != '<') { return false; }
    p=attr;
    while( *p && *p != '>' ) { p++; }
    if( ! *p ) { return false; }
    p--;
    if( *p == '/' ) {
        return true;
    }
    return false;
}

xmlChar *myxml_node_end(xmlChar *attr) {
    xmlChar *p,*name,*endname;
    int size;
    
    if( attr == NULL ) { return NULL; }
    if( attr[0] != '<') { return NULL; }
    if(myxml_is_node_single(attr) ) {
        return NULL;
    }
    name = myxml_extract_node_name(attr,false);
    if( !name ) return NULL;
    size = strlen(name) + 4;
    endname = malloc(size);
    if( ! endname ) {
        free(name);
        return NULL;
    }
    memset(endname,0,size);
    strncpy(endname,"</",size);
    strncat(endname,name,size);
    strncat(endname,">",size);
    p = strstr(attr,endname);
    free(endname);
    free(name);
    return p;
}
    
xmlChar *myxml_get_node_text(xmlChar *xml) {
    xmlChar *begin,*end, *text;
    int size;

    if(!xml) { return NULL; }
    if( myxml_is_node_single(xml) ) { return NULL; }
    end = myxml_node_end(xml);
    if( !end ) { return NULL; }
    begin = xml;
    while( *begin && *begin != '>' ) { begin++; }
    if( ! *begin ) { return NULL; } 
    begin++;
    size = end - begin + 1;
    text = malloc(size);
    if( ! text ) { return NULL; }
    memset(text,0,size);
    strncpy(text,begin,size-1);
    return text;
}

xmlChar *myxml_get_node_attribute(xmlChar *xml,xmlChar *attrname) {
    xmlChar *node,*end, *p, *text, *attreq, quote;
    int size;

    if( (xml == NULL) || (attrname == NULL) ) { return NULL; }
    end = xml;
    while( *end && *end != '>' ) { end++; }
    if( ! *end ) { return NULL; } 
    size = end - xml + 2;
    node = malloc(size);
    if(!node) { return NULL; }
    memset(node,0,size);
    strncpy(node,xml,size-1);

    size = strlen(attrname)+2;
    attreq = malloc(size);
    if(!attreq) { free(node); return NULL; }
    memset(attreq,0,size);
    strncpy(attreq,attrname,size-1);
    strncat(attreq,"=",size-1);
    p = strstr(node,attreq);
    while(p) {
        p--;
        if(isspace(*p) || (*p == ':') ) {
            p++;
            p = &p[strlen(attreq)];
            quote = p[0];
            p++;
            end = strchr(p,quote);
            text = NULL;
            if(end) {
                *end = 0;
                text = strdup(p);
            }
            free(attreq);
            free(node);
            return text;
        };
        p = strstr(&p[strlen(attreq)], attreq);
    }
    free(attreq);
    free(node);
    return NULL;
}
