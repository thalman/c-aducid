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

#include "attrlist.h"
#include "utils.h"
#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ADUCID_PUBLIC_FUNC
AducidAttributeList_t aducid_attr_list_new() {
    AducidAttributeList_t list;

    list = malloc(sizeof(AducidAttributeListStruct_t));
    if(list) {
        memset(list,0,sizeof(AducidAttributeListStruct_t));
    }
    return list;
}

ADUCID_PUBLIC_FUNC
int aducid_attr_list_count( const AducidAttributeList_t handle )
{
    int i = 0;
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    AducidAttributeListItem_t *node;

    if(!h) return 0;
    node = h->firstItem;
    while(node) {
        i++;
        node = node->next;
    }
    return i;
}

ADUCID_PUBLIC_FUNC
void aducid_attr_list_first( const AducidAttributeList_t handle ) {
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    
    if(!handle) return;
    h->cursor = h->firstItem;
    h->index = 0;
}

ADUCID_PUBLIC_FUNC
void aducid_attr_list_next( const AducidAttributeList_t handle ) {
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    
    if(!handle) return;
    if(!h->cursor) return;
    h->cursor = h->cursor->next;
}
    
ADUCID_PUBLIC_FUNC
const char *aducid_attr_list_get_name( const AducidAttributeList_t handle ) {
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;

    if(!handle) return NULL;
    if(!h->cursor) return NULL;
    return h->cursor->name;
}

ADUCID_PUBLIC_FUNC
const char *aducid_attr_list_get_value( const AducidAttributeList_t handle ) {
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;

    if(!handle) return NULL;
    if(!h->cursor) return NULL;
    return h->cursor->value;
}

AducidAttributeListItem_t *aducid_attr_list_get_item( const AducidAttributeList_t handle, int idx)
{
    int i = 0;
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    AducidAttributeListItem_t *node;
    
    if(!handle) return NULL;
    node = h->firstItem;
    while( (i != idx) && (node != NULL) ) {
        i++;
        node = node->next;
    }
    return node;
}
    
ADUCID_PUBLIC_FUNC
char *aducid_attr_list_get_item_name( const AducidAttributeList_t handle,int idx)
{
    AducidAttributeListItem_t *node;
    
    if(!handle) return NULL;
    node = aducid_attr_list_get_item(handle,idx);
    return node->name;
}

ADUCID_PUBLIC_FUNC
char *aducid_attr_list_get_item_value( const AducidAttributeList_t handle,int idx)
{
    AducidAttributeListItem_t *node;
    
    if(!handle) return NULL;
    node = aducid_attr_list_get_item(handle,idx);
    return node->value;
}

ADUCID_PUBLIC_FUNC
void aducid_attr_list_append( AducidAttributeList_t handle, const char *name, const char *value)
{
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    
    if(!handle) return;
    h->firstItem = ll_append_attribute(h->firstItem,name,value);
}

ADUCID_PUBLIC_FUNC
void aducid_attr_list_insert(AducidAttributeList_t handle, const char *name, const char *value, int idx)
{
    AducidAttributeListItem_t *node,*newNode;
    
    if(!handle) return;
    if(idx == 0) {
        aducid_attr_list_prepend(handle,name,value);
        return;
    }
    node = aducid_attr_list_get_item(handle,idx-1);
    if(!node) {
        aducid_attr_list_append(handle,name,value);
        return;
    }
    newNode = ll_append_attribute(NULL,name,value);
    newNode->next = node->next;
    node->next = newNode;
}


ADUCID_PUBLIC_FUNC
void aducid_attr_list_prepend(AducidAttributeList_t handle, const char *name, const char *value)
{
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    
    if(!handle) return;
    h->firstItem = ll_prepend_attribute(h->firstItem,name,value);
}

ADUCID_PUBLIC_FUNC
char *aducid_attr_list_get_first_by_name( const AducidAttributeList_t handle, const char *name)
{
    AducidAttributeListItem_t *node;
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    
    if(!handle) return NULL;
    node = h->firstItem;
    h->index = 0;
    while(node) {
        if( strcasecmp(node->name,name) == 0 ) {
            return node->value;
        }
        h->index++;
        node = node->next;
    }
    return NULL;
}

ADUCID_PUBLIC_FUNC
char *aducid_attr_list_get_next_by_name( const AducidAttributeList_t handle, const char *name)
{
    AducidAttributeListItem_t *node;
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    
    if(!handle) return NULL;
    node = aducid_attr_list_get_item(handle,h->index);
    if(!node) { return NULL; }
    node = node->next;
    h->index++;
    while(node) {
        if( strcasecmp(node->name,name) == 0 ) {
            return node->value;
        }
        h->index++;
        node = node->next;
    }
    return NULL;
}

ADUCID_PUBLIC_FUNC
int aducid_attr_list_get_count_by_name( const AducidAttributeList_t handle, const char *name)
{
    AducidAttributeListItem_t *node;
    int cnt = 0;
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    
    if(!handle) return 0;
    node = h->firstItem;

    while(node) {
        if( strcasecmp(node->name,name) == 0 ) {
            cnt++;
        }
        node = node->next;
    }
    return cnt;
}

bool aducid_attr_list_delete_node( AducidAttributeList_t handle, AducidAttributeListItem_t *item )
{
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;
    
    if(!handle) { return false; }
    h->firstItem = ll_free_attribute_node(h->firstItem,item);
    return true;
}

ADUCID_PUBLIC_FUNC
bool aducid_attr_list_delete(AducidAttributeList_t handle, int idx)
{
    AducidAttributeListItem_t *node;
    
    if(!handle) { return false; }
    node = aducid_attr_list_get_item(handle,idx);
    if(!node) { return false; }
    aducid_attr_list_delete_node(handle,node);
    return true;
}

ADUCID_PUBLIC_FUNC
bool aducid_attr_list_delete_by_name(AducidAttributeList_t handle, const char *name) {
    AducidAttributeListItem_t *node;
    bool result = false;
    int cnt,i;
    
    if(!handle) return 0;
    cnt = aducid_attr_list_count(handle);
    for(i=cnt-1; i>=0; i--) {
        node = aducid_attr_list_get_item(handle,i);
        if(node && (strcasecmp(node->name,name) == 0) ) {
            result = true;
            aducid_attr_list_delete(handle,i);
        }
    }
    return result;
}

ADUCID_PUBLIC_FUNC
void aducid_attr_list_free(AducidAttributeList_t handle) {
    AducidAttributeListStruct_t *h = (AducidAttributeListStruct_t *)handle;

    if(!handle) return;
    ll_free_attribute_list(h->firstItem);
    free(handle);
}

AducidAttributeListItem_t *ll_append_attribute( AducidAttributeListItem_t *list, const char *name, const char *value) {
    AducidAttributeListItem_t *node,*newNode;

    if( (name == NULL) || (value == NULL) ) { return list; }
    newNode = (AducidAttributeListItem_t *)malloc(sizeof(AducidAttributeListItem_t));
    if(newNode == NULL) {
        ll_free_attribute_list(list);
        return NULL;
    }
    memset(newNode,0,sizeof(AducidAttributeListItem_t));
    newNode->name = strdup(name);
    newNode->value = strdup(value);
    if(list == NULL) { return newNode; }
    node = list;
    while( node->next ) { node = node->next; }
    node->next = newNode;
    return list;
}

AducidAttributeListItem_t *ll_prepend_attribute(AducidAttributeListItem_t *list, const char *name, const char *value) {
    AducidAttributeListItem_t *newNode;

    if( (name == NULL) || (value == NULL) ) { return list; }
    newNode = (AducidAttributeListItem_t *)malloc(sizeof(AducidAttributeListItem_t));
    if(newNode == NULL) {
        ll_free_attribute_list(list);
        return NULL;
    }
    memset(newNode,0,sizeof(AducidAttributeListItem_t));
    newNode->name = strdup(name);
    newNode->value = strdup(value);
    newNode->next = list;
    return newNode;
}

AducidAttributeListItem_t *ll_free_attribute(AducidAttributeListItem_t *list,  const char *name){
    AducidAttributeListItem_t *nodeToDelete;
    nodeToDelete = ll_get_attribute(list, name);
    if(nodeToDelete == NULL) { return list; }
    return ll_free_attribute_node(list,nodeToDelete);
}

AducidAttributeListItem_t *ll_free_attribute_node(AducidAttributeListItem_t *list, AducidAttributeListItem_t *tofree){
    AducidAttributeListItem_t *node;
    if(!list) { return NULL; }
    node = list;
    if(node == tofree) {
        /* deleting first item */
        list = list->next;
        safe_free(node->name);
        safe_free(node->value);
        safe_free(node);
        return list;
    }
    while( node->next ) {
        if(node->next == tofree ) {
            node->next = tofree->next;
            safe_free(tofree->name);
            safe_free(tofree->value);
            safe_free(tofree);
            return list;
        }
        node = node->next;
    }
    return list;
}

void ll_free_attribute_list(AducidAttributeListItem_t *list){
    AducidAttributeListItem_t *node;
    while(list) {
        node = list;
        list = list->next;
        safe_free(node->name);
        safe_free(node->value);
        free(node);
    }
}

AducidAttributeListItem_t *ll_get_attribute(AducidAttributeListItem_t *list, const char *name) {
    AducidAttributeListItem_t *node = list;

    while(node) {
        if( strcmp(node->name,name) == 0 ) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

/**
   char *ll_get_attribute_value(AducidAttributeListItem_t *list, char *name) {
   AducidAttributeListItem_t *node;
   node = get_attribute(list, name);
   if( node == NULL ) { return NULL; }
   return node->value;
   }
*/
