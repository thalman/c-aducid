#ifndef __MYXML_H__
#define __MYXML_H__

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

char *myxml_find_xpath_first(const char *doc, const char *xpath);
char *myxml_extract_node_name(char *attr, bool removeNS);
bool  myxml_is_node_single(char *attr);
char *myxml_get_node_text(char *xml);
char *myxml_get_node_attribute(char *xml, char *attrname);

#ifdef __cplusplus
}
#endif

#endif
