#ifndef __MYXML_H__
#define __MYXML_H__

#include "definitions.h"

typedef char *xmlDocPtr;
typedef char xmlChar;

xmlChar *myxml_find_xpath_first(xmlDocPtr doc, xmlChar *xpath);
xmlChar *myxml_extract_node_name(xmlChar *attr, bool removeNS);
bool     myxml_is_node_single(xmlChar *attr);
xmlChar *myxml_get_node_text(xmlChar *xml);
xmlChar *myxml_get_node_attribute(xmlChar *xml,xmlChar *attrname);


#endif
