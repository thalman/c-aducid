#ifndef __ADUCIDSOAP_H__
#define __ADUCIDSOAP_H__

#include "attrlist.h"
#include "myxml.h"


char *create_aducid_soap_xml(const char *operation, const char *xml);
char *create_aim_request_operation_xml(const char *operationName,
				       char *AIMName,
				       char *authId,
				       char *bindingKey,
				       char *methodName,
				       char *methodParameter,
				       char *personalObject,
				       char *AAIM2,
				       char *ilData,
				       char *peigReturnName);
char *create_aim_get_psl_attributes_xml(const char *authId,
					const char *bindingId,
					const char *AIMName,
					const char *authKey,
					const char *attributeSetName);
char *create_aim_execute_personal_object_xml(const char *authId,
					     const char *AIMName,
					     const char *authKey,
					     const char *methodName,
					     const char *personalObjectName,
					     const char *personalObjectAlgorithm,
					     AducidAttributeList *personalObjectData,
					     const char *ILID,
					     const char *AAIM2,
					     const char *ilData);
AducidAttributeList *parse_personal_object(xmlDocPtr doc);
char *create_aim_close_session_xml(char *authId, char *AIMName, char *authKey);

#endif
