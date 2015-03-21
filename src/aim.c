#include "aim.h"

ADUCID_PUBLIC_FUNC
void aducid_free_aim_request_operation_response(AducidAIMRequestOperationResponse_t *response) {
    if( response == NULL ) { return; }
    safe_free(response->authId);
    safe_free(response->bindingId);
    safe_free(response->bindingKey);
    free(response);
}

ADUCID_PUBLIC_FUNC
void aducid_free_aim_get_psl_attributes_response(AducidAIMGetPSLAttributesResponse_t *response) {
    if( response == NULL ) { return; }
    safe_free(response->userDatabaseIndex);
    safe_free(response->userId);
    safe_free(response->validityCount);
    safe_free(response->validityTime);
    safe_free(response->expirationCountdownUses);
    safe_free(response->expirationCountdownTime);
    safe_free(response->securityProfileName);
    safe_free(response->authenticationProtocolName);
    safe_free(response->securityLevel);
    safe_free(response->ILID);
    safe_free(response->ilTypeName);
    safe_free(response->ilAlgorithmName);
    safe_free(response->ilValidityCount);
    safe_free(response->ilValidityTime);
    safe_free(response->authKey2);
    safe_free(response->sessionKey);
    safe_free(response->bindingType);
    free(response);
}

ADUCID_PUBLIC_FUNC void
aducid_free_aim_execute_personal_object_response(AducidAIMExecutePersonalObjectResponse_t *response)
{
    if( response == NULL ) { return; }
    safe_free(response->statusMessage);
    aducid_attr_list_free(response->personalObject);
    free(response);
}


ADUCID_PUBLIC_FUNC AducidAIMRequestOperationResponse_t *
aducid_aim_request_operation( const char *R4,
                              AducidOperation_t operation,
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
    char *XML;
    char *dom,*p;
    AducidAIMRequestOperationResponse_t *result;
    
    XML = create_aim_request_operation_xml(
                                           aducid_operation_str(operation),
                                           AIMName,authId,bindingKey, methodName, methodParameters,
                                           personalObject,AAIM2,ilData,
                                           peigReturnName
                                           );
    dom = soap_request(R4,"AIMrequestOperation",XML);

    /* dom = xmlParseDoc(BAD_CAST response); */
    result = NULL;
    if(dom != NULL) {
        result = (AducidAIMRequestOperationResponse_t *)malloc( sizeof(AducidAIMRequestOperationResponse_t) );
        result->authId = xml_get_single_node_text(dom, "//authId");
        result->bindingId = xml_get_single_node_text(dom, "//bindingId");
        result->bindingKey = xml_get_single_node_text(dom, "//bindingKey");
        p = xml_get_single_node_text(dom, "//statusAIM");
        result->statusAIM = aducid_aim_status_enum( p );
        safe_free(p);
        p = xml_get_single_node_text(dom, "//statusAuth");
        result->statusAuth = aducid_auth_status_enum( p );
        safe_free(p);
    }
    safe_free(XML);
    safe_free(dom);
    
    return result;
}

ADUCID_PUBLIC_FUNC AducidAIMGetPSLAttributesResponse_t *
aducid_aim_get_psl_attributes( const char *R4,
                               const char *authId,
                               const char *bindingId,
                               const char *AIMName,
                               const char *authKey,
                               AducidAttributeSet_t attributeSet)
{
    char *XML;
    char *dom, *p;
    AducidAIMGetPSLAttributesResponse_t *result;
    
    /**
       #<xs:element name="authId" type="authidType" minOccurs="0" maxOccurs="1"/>
       #<xs:element name="AIMname" type="nameType" minOccurs="0" maxOccurs="1"/>
       #<xs:element name="authKey" type="authkeyType" minOccurs="0" maxOccurs="1"/>
       #<xs:element name="attributeSetName" type="nameType" minOccurs="0" maxOccurs="1"/>
    */
    XML = create_aim_get_psl_attributes_xml(authId, bindingId, AIMName, authKey, aducid_attribute_set_str( attributeSet ) );
    dom = soap_request(R4,"AIMgetPSLAttributes",XML);
    /* dom = xmlParseDoc(response); */
    result = NULL;
    if( dom ) {
        result = (AducidAIMGetPSLAttributesResponse_t *)malloc( sizeof(AducidAIMGetPSLAttributesResponse_t) );
        memset(result,0,sizeof(AducidAIMGetPSLAttributesResponse_t));

        p = xml_get_single_node_text(dom,"//statusAIM");
        result->statusAIM = aducid_aim_status_enum( p );
        safe_free(p);
        
        p =  xml_get_single_node_text(dom,"//statusAuth");
        result->statusAuth = aducid_auth_status_enum( p );
        safe_free(p);

        p = xml_get_single_node_text(dom,"//operationName");
        result->operationName = aducid_operation_enum( p );
        safe_free(p);
        
        result->userDatabaseIndex = xml_get_single_node_text(dom, "//userDatabaseIndex");
        result->userId = xml_get_single_node_text(dom,"//userId");
        
        result->validityCount = xml_get_single_node_text(dom,"//validityCount");
        result->validityTime = xml_get_single_node_text(dom,"//validityTime");
        result->expirationCountdownUses = xml_get_single_node_text(dom,"//expirationCountdownUses");
        result->expirationCountdownTime = xml_get_single_node_text(dom,"//expirationCountdownTime");
        
        result->securityProfileName = xml_get_single_node_text(dom,"//securityProfileName");
        result->authenticationProtocolName = xml_get_single_node_text(dom,"//authenticationProtocolName");
        result->securityLevel = xml_get_single_node_text(dom,"//securityLevel");
        
        result->ILID = xml_get_single_node_text(dom,"//ilid");
        result->ilTypeName = xml_get_single_node_text(dom,"//ilTypeName");
        result->ilAlgorithmName = xml_get_single_node_text(dom,"//ilAlgorithmName");
        result->ilValidityTime = xml_get_single_node_text(dom,"//ilValidityTime");
        result->ilValidityCount = xml_get_single_node_text(dom,"//ilValidityCount");
        
        result->authKey2 = xml_get_single_node_text(dom,"//authKey2");
        result->sessionKey = xml_get_single_node_text(dom,"//sessionKey");
        
        result->bindingType = xml_get_single_node_text(dom,"//bindingType");
    }
    safe_free(XML);
    safe_free(dom);

    return result;
}

ADUCID_PUBLIC_FUNC AducidAIMExecutePersonalObjectResponse_t *
aducid_aim_execute_personal_object( const char *R4,
                                    const char *authId,
                                    const char *AIMName,
                                    const char *authKey,
                                    AducidMethod_t methodName,
                                    const char *personalObjectName,
                                    AducidAlgorithm_t personalObjectAlgorithm,
                                    AducidAttributeList_t *personalObjectData,
                                    const char *ILID,
                                    const char *AAIM2,
                                    const char *ilData )
{
    char *XML;
    char *dom;
    char *p;
    AducidAIMExecutePersonalObjectResponse_t *result;
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
    XML = create_aim_execute_personal_object_xml(authId, AIMName, authKey,
                                                 aducid_method_str( methodName ),
                                                 personalObjectName,
                                                 aducid_algorithm_str(personalObjectAlgorithm),
                                                 personalObjectData,ILID,AAIM2,ilData);
    dom = soap_request(R4,"AIMexecutePersonalObject",XML);
    result = (AducidAIMExecutePersonalObjectResponse_t *)malloc( sizeof(AducidAIMExecutePersonalObjectResponse_t) );
    memset(result,0,sizeof(AducidAIMExecutePersonalObjectResponse_t) );

    p = xml_get_single_node_text(dom,"//statusAIM");
    result->statusAIM = aducid_aim_status_enum( p );
    safe_free(p);
    
    p = xml_get_single_node_text(dom,"//statusAuth");
    result->statusAuth = aducid_auth_status_enum( p );
    safe_free(p);
    
    result->personalObject = parse_personal_object(dom);
    free(XML);
    free(dom);
    return result;
}

ADUCID_PUBLIC_FUNC
bool aducid_aim_close_session(const char *R4, const char *authId, const char *AIMName, const char *authKey) {
    /**
       function callCloseSession($R4URL,$request) {
       $soap = new SoapClient(NULL,
       array ( "location" => $R4URL,
       "uri"      => "http://iface.aducid.anect.com",
       "style"    => SOAP_RPC,
       "use"      => SOAP_ENCODED
       ));
       $soapParams = array();
       if( isset($request["authId"])  && ( $request["authId"] != NULL )  ) { array_push($soapParams, new SoapParam($request["authId"],"authId") ); }
       if( isset($request["AIMName"]) && ( $request["AIMName"] != NULL ) ) { array_push($soapParams, new SoapParam($request["AIMName"],"AIMName") ); }
       if( isset($request["authKey"]) && ( $request["authKey"] != NULL ) ) { array_push($soapParams, new SoapParam($request["authKey"],"authKey") ); }
       $result = $soap->__call(
       "AIMcloseSession",
       $soapParams
       );
       return $result;
       }
    */
    char *XML;
    char *dom;
    char *status;
    AducidAIMStatus_t AIMStatus;
    AducidAuthStatus_t AuthStatus;
    
    XML = create_aim_close_session_xml(authId, AIMName, authKey);
    dom = soap_request(R4,"AIMcloseSession",XML);

    status = xml_get_single_node_text(dom,"//statusAIM");
    AIMStatus = aducid_aim_status_enum( status );
    safe_free(status);

    status = xml_get_single_node_text(dom,"//statusAuth");
    AuthStatus = aducid_auth_status_enum( status );
    safe_free(status);

    /**
       <?xml version='1.0' encoding='UTF-8'?><soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\"><soapenv:Body><ns1:AIMcloseSessionResponse xmlns:ns1=\"http://iface.aducid.anect.com\"><statusAIM>end</statusAIM><statusAuth>OK</statusAuth></ns1:AIMcloseSessionResponse></soapenv:Body></soapenv:Envelope>"
    */
    free(XML);
    free(dom);
    return (AuthStatus == ADUCID_AUTHSTATUS_OK) && ( AIMStatus == ADUCID_AIM_STATUS_END );
}

