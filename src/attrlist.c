#include "attrlist.h"
#include "utils.h"
#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DLL_PUBLIC
AducidAttributeList aducid_attr_list_new() {
    AducidAttributeList list;

    list = malloc(sizeof(AducidAttributeListStruct));
    if(list) {
	memset(list,0,sizeof(AducidAttributeListStruct));
    }
    return list;
}

DLL_PUBLIC
int aducid_attr_list_count(AducidAttributeList handle) {
    int i = 0;
    AducidAttributeListStruct *h = (AducidAttributeListStruct *)handle;
    AducidAttributeListItem *node;

    if(!h) return 0;
    node = h->firstItem;
    while(node) {
	i++;
	node = node->next;
    }
    return i;
}

AducidAttributeListItem *aducid_attr_list_get_item(AducidAttributeList handle,int idx) {
    int i = 0;
    AducidAttributeListStruct *h = (AducidAttributeListStruct *)handle;
    AducidAttributeListItem *node;
    
    if(!handle) return NULL;
    node = h->firstItem;
    while( (i != idx) && (node != NULL) ) {
	i++;
	node = node->next;
    }
    return node;
}
    
DLL_PUBLIC
char *aducid_attr_list_get_item_name(AducidAttributeList handle,int idx) {
    AducidAttributeListItem *node;
    
    if(!handle) return NULL;
    node = aducid_attr_list_get_item(handle,idx);
    return node->name;
}

DLL_PUBLIC
char *aducid_attr_list_get_item_value(AducidAttributeList handle,int idx) {
    AducidAttributeListItem *node;
    
    if(!handle) return NULL;
    node = aducid_attr_list_get_item(handle,idx);
    return node->value;
}

DLL_PUBLIC
void aducid_attr_list_append(AducidAttributeList handle,char *name,char *value) {
    AducidAttributeListStruct *h = (AducidAttributeListStruct *)handle;
    
    if(!handle) return;
    h->firstItem = ll_append_attribute(h->firstItem,name,value);
}

DLL_PUBLIC
void aducid_attr_list_insert(AducidAttributeList handle,char *name,char *value,int idx) {
    AducidAttributeListItem *node,*newNode;
    
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


DLL_PUBLIC
void aducid_attr_list_prepend(AducidAttributeList handle,char *name,char *value) {
    AducidAttributeListStruct *h = (AducidAttributeListStruct *)handle;
    
    if(!handle) return;
    h->firstItem = ll_prepend_attribute(h->firstItem,name,value);
}

DLL_PUBLIC
char *aducid_attr_list_get_first_by_name(AducidAttributeList handle,char *name) {
    AducidAttributeListItem *node;
    AducidAttributeListStruct *h = (AducidAttributeListStruct *)handle;
    
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

DLL_PUBLIC
char *aducid_attr_list_get_next_by_name(AducidAttributeList handle,char *name) {
    AducidAttributeListItem *node;
    AducidAttributeListStruct *h = (AducidAttributeListStruct *)handle;
    
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

DLL_PUBLIC
int aducid_attr_list_get_count_by_name(AducidAttributeList handle,char *name) {
    AducidAttributeListItem *node;
    int cnt = 0;
    AducidAttributeListStruct *h = (AducidAttributeListStruct *)handle;
    
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

bool aducid_attr_list_delete_node(AducidAttributeList handle,AducidAttributeListItem *item) {
    AducidAttributeListStruct *h = (AducidAttributeListStruct *)handle;
    
    if(!handle) { return false; }
    h->firstItem = ll_free_attribute_node(h->firstItem,item);
    return true;
}

DLL_PUBLIC
bool aducid_attr_list_delete(AducidAttributeList handle,int idx) {
    AducidAttributeListItem *node;
    
    if(!handle) { return false; }
    node = aducid_attr_list_get_item(handle,idx);
    if(!node) { return false; }
    aducid_attr_list_delete_node(handle,node);
    return true;
}

DLL_PUBLIC
bool aducid_attr_list_delete_by_name(AducidAttributeList handle,char *name) {
    AducidAttributeListItem *node;
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

DLL_PUBLIC
void aducid_attr_list_free(AducidAttributeList handle) {
    AducidAttributeListStruct *h = (AducidAttributeListStruct *)handle;

    if(!handle) return;
    ll_free_attribute_list(h->firstItem);
    free(handle);
}

AducidAttributeListItem *ll_append_attribute(AducidAttributeListItem *list, char *name, char *value) {
    AducidAttributeListItem *node,*newNode;

    if( (name == NULL) || (value == NULL) ) { return list; }
    newNode = (AducidAttributeListItem *)malloc(sizeof(AducidAttributeListItem));
    if(newNode == NULL) {
	ll_free_attribute_list(list);
	return NULL;
    }
    memset(newNode,0,sizeof(AducidAttributeListItem));
    newNode->name = strdup(name);
    newNode->value = strdup(value);
    if(list == NULL) { return newNode; }
    node = list;
    while( node->next ) { node = node->next; }
    node->next = newNode;
    return list;
}

AducidAttributeListItem *ll_prepend_attribute(AducidAttributeListItem *list, char *name, char *value) {
    AducidAttributeListItem *newNode;

    if( (name == NULL) || (value == NULL) ) { return list; }
    newNode = (AducidAttributeListItem *)malloc(sizeof(AducidAttributeListItem));
    if(newNode == NULL) {
	ll_free_attribute_list(list);
	return NULL;
    }
    memset(newNode,0,sizeof(AducidAttributeListItem));
    newNode->name = strdup(name);
    newNode->value = strdup(value);
    newNode->next = list;
    return newNode;
}

AducidAttributeListItem *ll_free_attribute(AducidAttributeListItem *list, char *name){
    AducidAttributeListItem *nodeToDelete;
    nodeToDelete = ll_get_attribute(list, name);
    if(nodeToDelete == NULL) { return list; }
    return ll_free_attribute_node(list,nodeToDelete);
}

AducidAttributeListItem *ll_free_attribute_node(AducidAttributeListItem *list, AducidAttributeListItem *tofree){
    AducidAttributeListItem *node;
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

void ll_free_attribute_list(AducidAttributeListItem *list){
    AducidAttributeListItem *node;
    while(list) {
	node = list;
	list = list->next;
	safe_free(node->name);
	safe_free(node->value);
	free(node);
    }
}

AducidAttributeListItem *ll_get_attribute(AducidAttributeListItem *list, char *name) {
    AducidAttributeListItem *node = list;

    while(node) {
	if( strcmp(node->name,name) == 0 ) {
	    return node;
	}
	node = node->next;
    }
    return NULL;
}

/**
   char *ll_get_attribute_value(AducidAttributeListItem *list, char *name) {
   AducidAttributeListItem *node;
   node = get_attribute(list, name);
   if( node == NULL ) { return NULL; }
   return node->value;
   }
*/
