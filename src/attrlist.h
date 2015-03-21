#ifndef __ATTRLIST_H__
#define __ATTRLIST_H__

#include "definitions.h"

typedef struct StructAducidAttributeListItem {
    char *name;
    char *value;
    struct StructAducidAttributeListItem *next;
} AducidAttributeListItem_t;

typedef struct {
    int index;
    AducidAttributeListItem_t *firstItem;
} AducidAttributeListStruct_t;

AducidAttributeListItem_t *ll_append_attribute(AducidAttributeListItem_t *list, const char *name, const char *value);
AducidAttributeListItem_t *ll_prepend_attribute(AducidAttributeListItem_t *list, const char *name, const char *value);
AducidAttributeListItem_t *ll_free_attribute(AducidAttributeListItem_t *list, const char *name);
void ll_free_attribute_list(AducidAttributeListItem_t *list);
AducidAttributeListItem_t *ll_get_attribute(AducidAttributeListItem_t *list, const char *name);
char *ll_get_attribute_value(AducidAttributeListItem_t *list, const char *name);
AducidAttributeListItem_t *ll_free_attribute_node(AducidAttributeListItem_t *list, AducidAttributeListItem_t *tofree);

#endif
