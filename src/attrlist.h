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

#ifndef __ATTRLIST_H__
#define __ATTRLIST_H__

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
