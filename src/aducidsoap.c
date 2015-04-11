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

#include "definitions.h"
#include "aducidsoap.h"
#include "utils.h"
#include "attrlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined _WIN32 || defined _WIN64
/* nothing for win */
#else
#include <curl/curl.h>
#endif

#include "definitions.h"
#include "myxml.h"

char *create_aducid_soap_xml(const char *operation, const char *xml) {
    static char *xmlHead = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	"<SOAP-ENV:Envelope SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" "
	"xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\" "
	"xmlns:xsi=\"http://www.w3.org/1999/XMLSchema-instance\" "
	"xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" "
	"xmlns:xsd=\"http://www.w3.org/1999/XMLSchema\">\n"
	"<SOAP-ENV:Body>\n";
    static char *xmlFoot = "</SOAP-ENV:Body>\n</SOAP-ENV:Envelope>\n";
    
    char *result = NULL;
    
    result = dyn_strcat(result,xmlHead,false);
    result = dyn_strcat(result,"<iface:",false);
    result = dyn_strcat(result,(char *)operation,false);
    result = dyn_strcat(result," xmlns:iface=\"http://iface.aducid.com\" SOAP-ENC:root=\"1\">\n",false);
    result = dyn_strcat(result,(char *)xml,false);
    result = dyn_strcat(result,"</iface:",false);
    result = dyn_strcat(result,(char *)operation,false);
    result = dyn_strcat(result,">\n",false);
    result = dyn_strcat(result,xmlFoot,false);
    return result;
}

char *create_xml_attribute(const char *name, const char *value) {
    char *attr = NULL;
    const char *format = "<%s xsi:type=\"xsd:string\">%s</%s>\n";
    int len;
    
    len = strlen(format) + strlen(name)*2 + strlen(value) - 5; /* - 3 x strlen("%s") + trailing \00 */
    attr = (char *)malloc(len);
    memset(attr,0,len);
    if(attr == NULL) { return NULL; }
    snprintf(attr,len,format,name,value,name);
    return attr;
}

char *create_method_params_xml(const AducidAttributeList_t list)
{
    char *xml = NULL;
    int a;
    
    for( a = 0; a < aducid_attr_list_count(list); a++ ) {
        xml = dyn_strcat(xml, "<methodParameter>\n  <parameterName xsi:type=\"xsd:string\">", false);
        xml = dyn_strcat(xml, aducid_attr_list_get_item_name(list,a), false);
        xml = dyn_strcat(xml, "</parameterName>\n  <parameterValue xsi:type=\"xsd:string\">", false);
        xml = dyn_strcat(xml, aducid_attr_list_get_item_value(list, a), false);
        xml = dyn_strcat(xml, "</parameterValue>\n</methodParameter>\n",false);
    }
    return xml;
}

char *create_personal_object_xml(const char *name, const char *typeName, const char *algorithm, AducidAttributeList_t attributes) {
    static const char *poaformat = "<personalObjectAttribute iface:attributeName=\"%s\">\n"
	"<attributeValue xmlns:s115=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:s116=\"http://www.w3.org/2001/XMLSchema\" s115:type=\"s116:string\">%s</attributeValue>\n"
	"</personalObjectAttribute>\n";
    int attrLength;
    char *buffer;
    AducidAttributeListItem_t *attr = NULL;
    char *XML = NULL;
    const char *N = name, *T = typeName, *A = algorithm;

    if( attributes )
        attr = ((AducidAttributeListStruct_t *)attributes)->firstItem;
    if( name == NULL && typeName == NULL && algorithm == NULL && attr != NULL ) {
        // attributes are in list if param is null
        if( strcmp( attr->name, "personalObjectName" ) == 0 ) {
            N = attr->value;
            attr = attr->next;
        }
        if( strcmp( attr->name, "personalObjectTypeName" ) == 0 ) {
            T = attr->value;
            attr = attr->next;
        }
        if( strcmp( attr->name, "personalObjectAlgorithmName" ) == 0 ) {
            A = attr->value;
            attr = attr->next;
        }
    }
    XML = dyn_strcat(XML,"<personalObject>\n",false);
    if( N ) XML = dyn_strcat(XML,create_xml_attribute("personalObjectName",N),true );
    if( T ) XML = dyn_strcat(XML,create_xml_attribute("personalObjectTypeName",T),true );
    if( A )XML = dyn_strcat(XML,create_xml_attribute("personalObjectAlgorithmName",A),true );
    while(attr) {
        attrLength = strlen(poaformat) - 4 + strlen(attr->name) + strlen(attr->value);
        buffer = (char *)malloc(attrLength+1);
        if(buffer) {
            snprintf(buffer,attrLength+1,poaformat,attr->name,attr->value);
            XML = dyn_strcat(XML,buffer,true);
        }
        attr = attr->next;
    }
    XML = dyn_strcat(XML,"</personalObject>\n",false);
    return XML;
}




char *create_aim_request_operation_xml(
    const char *operationName,
    const char *AIMName,
    const char *authId,
    const char *bindingKey,
    const char *methodName,
    const AducidAttributeList_t methodParameters,
    const AducidAttributeList_t personalObject,
    const char *AAIM2,
    const char *ilData,
    const char *peigReturnName)
{
    char *XML = NULL;
    char *XMLC;
    /**	
	# wsdl request
        #
        #<xs:element name="operationName" type="nameType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="AIMname" type="nameType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="authId" type="authidType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="methodName" type="nameType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="methodParameter" type="methodParameterType" minOccurs="0" maxOccurs="unbounded"/>
        #<xs:element name="personalObject" type="personalObjectType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="AIM2name" type="nameType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="ilData" type="ildataType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="peigReturnName" type="nameType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="peigReturnSecret" type="secretType" minOccurs="0" maxOccurs="1"/>
        #
    */
    /* create soap xml */
    if( operationName != NULL ) { XML = dyn_strcat(XML,create_xml_attribute("operationName",operationName),true ); }
    if( AIMName != NULL )       { XML = dyn_strcat(XML,create_xml_attribute("AIMname",AIMName),true ); }
    if( authId != NULL )        { XML = dyn_strcat(XML,create_xml_attribute("authId",authId),true ); }
    if( bindingKey != NULL )    { XML = dyn_strcat(XML,create_xml_attribute("bindingKey",bindingKey),true ); }
    if( methodName != NULL )    { XML = dyn_strcat(XML,create_xml_attribute("methodName",methodName),true ); }
    if( methodParameters != NULL ) { XML = dyn_strcat(XML, create_method_params_xml( methodParameters ),true ); }
    if( personalObject != NULL ) {
        XML = dyn_strcat(
            XML,
            create_personal_object_xml( NULL, NULL, NULL, personalObject ),
            true);
    }
    /* FIXME: aaim2, ildata */
    if( peigReturnName != NULL ){ XML = dyn_strcat(XML,create_xml_attribute("peigReturnName",peigReturnName),true ); }
    XMLC = create_aducid_soap_xml("AIMrequestOperation",XML);
    if( XML ){ free(XML); };
    return XMLC;
}


char *create_aim_get_psl_attributes_xml(const char *authId,
					const char *bindingId,
					const char *AIMName,
					const char *authKey,
					const char *attributeSetName)
{
    char *XML = NULL;
    char *XMLC;
    /**	
	# wsdl request
        #
	#<xs:element name="authId" type="authidType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="AIMname" type="nameType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="authKey" type="authkeyType" minOccurs="0" maxOccurs="1"/>
        #<xs:element name="attributeSetName" type="nameType" minOccurs="0" maxOccurs="1"/>
    */
    if( authId != NULL ) {
	XML = dyn_strcat(XML,create_xml_attribute("authId",authId),true );
    }
    if( bindingId != NULL ) {
	XML = dyn_strcat(XML,create_xml_attribute("bindingId",bindingId),true );
    }
    if(AIMName != NULL ) {
	XML = dyn_strcat(XML,create_xml_attribute("AIMName",AIMName),true);
    }
    if( authKey != NULL ) {
	XML = dyn_strcat(XML,create_xml_attribute("authKey",authKey),true );
    }
    if( attributeSetName != NULL ) {
	XML = dyn_strcat(XML,create_xml_attribute("attributeSetName",attributeSetName),true );
    }
    XMLC = create_aducid_soap_xml("AIMgetPSLAttributes",XML);
    if( XML ){ free(XML); };
    return XMLC;
}


char *create_aim_execute_personal_object_xml(const char *authId,
					     const char *AIMName,
					     const char *authKey,
					     const char *methodName,
					     const char *personalObjectName,
					     const char *personalObjectAlgorithm,
					     AducidAttributeList_t personalObjectData,
					     const char *ILID,
					     const char *AAIM2,
					     const char *ilData) {
    char *XML = NULL;
    char *XMLC;
    /**
       #<xs:element name="authId" type="authidType" minOccurs="0" maxOccurs="1"/>
       #<xs:element name="AIMname" type="nameType" minOccurs="0" maxOccurs="1"/>
       #<xs:element name="authKey" type="authkeyType" minOccurs="0" maxOccurs="1"/>
       #<xs:element name="methodName" type="nameType" minOccurs="0" maxOccurs="1"/>
       #<xs:element name="personalObject" type="personalObjectType" minOccurs="0" maxOccurs="1"/>..
       #<xs:element name="ILID" type="ILIDType" minOccurs="0" maxOccurs="1"/>
       #<xs:element name="AAIM2" type="aimUrlType" minOccurs="0" maxOccurs="1"/>
       #<xs:element name="ilData" type="ildataType" minOccurs="0" maxOccurs="1"/>
    */
    if( authId != NULL ) {
        XML = dyn_strcat(XML,create_xml_attribute("authId",authId),true );
    }
    if(AIMName != NULL ) {
        XML = dyn_strcat(XML,create_xml_attribute("AIMname",AIMName),true );
    }
    if( authKey != NULL ) {
        XML = dyn_strcat(XML,create_xml_attribute("authKey",authKey),true );
    }
    if( methodName != NULL ) {
        XML = dyn_strcat(XML,create_xml_attribute("methodName",methodName),true );
    }
    if( personalObjectName ) {
        XML = dyn_strcat(XML,create_personal_object_xml( personalObjectName, NULL, personalObjectAlgorithm, personalObjectData),true );
    }
    if( ILID != NULL ) {
        XML = dyn_strcat(XML,create_xml_attribute("ILID",ILID),true );
    }
    if( AAIM2 != NULL ) {
        XML = dyn_strcat(XML,create_xml_attribute("AAIM2",AAIM2),true );
    }
    if( ilData != NULL ) {
        XML = dyn_strcat(XML,create_xml_attribute("ilData",ilData),true );
    }

    XMLC = create_aducid_soap_xml("AIMexecutePersonalObject",XML);
    if( XML ){ free(XML); };
    return XMLC;
}

AducidAttributeList_t parse_personal_object( char *doc ) {

    /**
     //FIXME:Personal Object
     <personalObject>
     <personalObjectAttribute ns1:attributeName="aducidRole">
     <attributeValue xmlns:s333="http://www.w3.org/2001/XMLSchema-instance" xmlns:s334="http://www.w3.org/2001/XMLSchema" s333:type="s334:string">UIM_U</attributeValue>
     </personalObjectAttribute>
     <personalObjectAttribute ns1:attributeName="aducidRole">
     <attributeValue xmlns:s335="http://www.w3.org/2001/XMLSchema-instance" xmlns:s336="http://www.w3.org/2001/XMLSchema" s335:type="s336:string">UIM_RM</attributeValue>
     </personalObjectAttribute>
     <personalObjectAttribute ns1:attributeName="aducidRole">
     <attributeValue xmlns:s337="http://www.w3.org/2001/XMLSchema-instance" xmlns:s338="http://www.w3.org/2001/XMLSchema" s337:type="s338:string">UIM_SM</attributeValue>
     </personalObjectAttribute>
     <personalObjectAttribute ns1:attributeName="aducidRole">
     <attributeValue xmlns:s339="http://www.w3.org/2001/XMLSchema-instance" xmlns:s340="http://www.w3.org/2001/XMLSchema" s339:type="s340:string">UIM_UM</attributeValue>
     </personalObjectAttribute><personalObjectAttribute ns1:attributeName="aducidAuthorized">
     <personalObjectAttribute ns1:attributeName="givenName">
     <attributeValue xmlns:s351="http://www.w3.org/2001/XMLSchema-instance" xmlns:s352="http://www.w3.org/2001/XMLSchema" s351:type="s352:string">Tomas</attributeValue>
     </personalObjectAttribute>
     </personalObject>
    */
    AducidAttributeList_t list;
    char *name, *value, *p, *q;
    char *txt, *valueAttr;
    
    list = aducid_attr_list_new();
    txt = myxml_get_node_text(myxml_find_xpath_first(doc,"//personalObject"));
    p = myxml_find_xpath_first(txt,"//personalObjectAttribute");
    while(p) {
        name = NULL;
        value = NULL;
        valueAttr = myxml_get_node_text(p);
        if(valueAttr) {
            name = myxml_get_node_attribute(p,"attributeName");
            if(name) {
                q = myxml_find_xpath_first(valueAttr,"//attributeValue");
                if(q) {
                    value = myxml_get_node_text(q);
                }
            }
            if( name && value ) {
                aducid_attr_list_append(list,name,value);
            }
            if(name) { free(name); }
            if(value) { free(value); }
            free(valueAttr);
        }
        p = myxml_find_xpath_first(&p[2],"//personalObjectAttribute");
    }
    free(txt);
    return list;

    /*
      xmlXPathContextPtr context;
      xmlXPathObjectPtr result;
      xmlNodePtr node,subNode;
      xmlAttrPtr attr;
      AducidAttributeList_t *list;
      char *name,*value;
      int i;
    
      list = aducid_attr_list_new();
      context = xmlXPathNewContext(doc);
      if (context == NULL) {
      return NULL;
      }
      result = xmlXPathEvalExpression(BAD_CAST "//personalObjectAttribute", context);
      xmlXPathFreeContext(context);
      if (result == NULL) {
      return NULL;
      }
      if( xmlXPathNodeSetIsEmpty(result->nodesetval) ){
      xmlXPathFreeObject(result);
      return NULL;
      }
      for( i = 0; i < result->nodesetval->nodeNr; i++) {
      node = result->nodesetval->nodeTab[i];
      name = NULL;
      value = NULL;
      attr = node->properties;
      if( attr && attr->children && attr->children->content ) {
      name = (char *)(attr->children->content);
      subNode = node->children;
      if( subNode && subNode->children && (subNode->children->type == XML_TEXT_NODE) ) { value = (char *)subNode->children->content; }
      }
      aducid_attr_list_append(list,name,value);
      }
      xmlXPathFreeObject(result);
      return list;
    */
}

char *create_aim_close_session_xml(const char *authId, const char *AIMName, const char *authKey)
{
    char *XML = NULL;
    char *XMLC;
    /* create soap xml */
    if( authId != NULL )  { XML = dyn_strcat(XML,create_xml_attribute("authId",authId),true ); }
    if( AIMName != NULL ) { XML = dyn_strcat(XML,create_xml_attribute("AIMname",AIMName),true ); }
    if( authKey != NULL ) { XML = dyn_strcat(XML,create_xml_attribute("authKey",authKey),true ); }
    XMLC = create_aducid_soap_xml("AIMcloseSession",XML);
    if( XML ){ free(XML); };
    return XMLC;
}
