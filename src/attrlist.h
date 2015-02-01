#ifndef __ATTRLIST_H__
#define __ATTRLIST_H__

#if defined(_WIN32) || defined(_WIN64) 
/* nothing for win */
#else
#include <stdbool.h>
#endif
#include "aducid.h"

typedef struct StructAducidAttributeListItem {
    char *name;
    char *value;
    struct StructAducidAttributeListItem *next;
} AducidAttributeListItem;

typedef struct {
    int index;
    AducidAttributeListItem *firstItem;
} AducidAttributeListStruct;

AducidAttributeListItem *ll_append_attribute(AducidAttributeListItem *list, char *name, char *value);
AducidAttributeListItem *ll_prepend_attribute(AducidAttributeListItem *list, char *name, char *value);
AducidAttributeListItem *ll_free_attribute(AducidAttributeListItem *list, char *name);
void ll_free_attribute_list(AducidAttributeListItem *list);
AducidAttributeListItem *ll_get_attribute(AducidAttributeListItem *list, char *name);
char *ll_get_attribute_value(AducidAttributeListItem *list, char *name);
AducidAttributeListItem *ll_free_attribute_node(AducidAttributeListItem *list, AducidAttributeListItem *tofree);

#endif
