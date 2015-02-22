#include "aducid.h"
#include "soap.h"
#include "aducidsoap.h"
#include "utils.h"
#include "attrlist.h"
#include "myxml.h"

#if defined _WIN32 || defined _WIN64
/* nothing special for windows */
#else
/* on linux we need */
#include <curl/curl.h>
#include <unistd.h>
#endif

#include "definitions.h"

DLL_PUBLIC
void aducid_free_aim_request_operation_response(AducidAIMRequestOperationResponse *response) {
    if( response == NULL ) { return; }
    safe_free(response->authId);
    safe_free(response->bindingId);
    safe_free(response->bindingKey);
    free(response);
}

DLL_PUBLIC
void aducid_free_aim_get_psl_attributes_response(AducidAIMGetPSLAttributesResponse *response) {
    if( response == NULL ) { return; }
    safe_free(response->userDatabaseIndex);
    safe_free(response->userId);
    safe_free(response->validityCount);
    safe_free(response->validityTime);
    safe_free(response->orangeCount);
    safe_free(response->orangeTime);
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

DLL_PUBLIC
void aducid_free_aim_execute_personal_object_response(AducidAIMExecutePersonalObjectResponse *response) {
    if( response == NULL ) { return; }
    safe_free(response->statusMessage);
    aducid_attr_list_free(response->personalObject);
    free(response);
}

/* ADUCID text constants begin */

const static char *aducidOperations[] = {
    "open",
    "init",
    "reinit",
    "change",
    "rechange",
    "delete",
    "replica",
    "link",
    "exuse",
    "autoChange",
    NULL
};

const static char *aducidAttributeSets[] = {
    "Status",
    "Basic",
    "All",
    "Validity",
    "Link",
    "Error",
    "PeigReturnName",
    NULL
};

const static char *aducidAIMStatuses[] = {
    "none",
    "error",
    "working",
    "Client-binding",
    "start",
    "finished",
    "active",
    "internal-error",
    "startTimeout",
    "processTimeout",
    "bindingTimeout",
    "end",
    "passive",
    "Auth-error",
    NULL
};

const static char *aducidMethods[] = {
    "Init",
    "Create",
    "Change",
    "Read",
    "Delete",
    "Write",
    "LegacyLogin",
    "Set",
    "GenKeyPair",
    "WriteCert",
    "LegacySign",
    "OTPverification",
    "ILread",
    "PasswdDecrypt",
    "SetExecuteRight",
    "ClearExecuteRight",
    "UploadCert",
    "TempEnableCAPI",
    "TempDisableCAPI",
    "PermEnableCAPI",
    "PermDisableCAPI",
    "PPOresult",
    "AIMread",
    "ReadPeigCount",
    "ActivateOtherPeigs",
    "DeactivateOtherPeigs",
    "ActivateThePeig",
    "DeactivateThePeig",
    "ReadPeigId",
    "ReadOtherPeigsId",
    "CreateRoomByName",
    "CreateRoomByStory",
    "EnterRoomByName",
    "EnterRoomByStory",
    "ConfirmTransaction",
    "VerifyLF",
    "PeigLocalLink",
    NULL
};

const static char *aducidAlgorithms[] = {
    "USER_ATTRIBUTE_SET",
    "PASSWD",
    "PASSWD-AIM",
    "BIN_STRING",
    "OTP-AIM_1",
    "X509-SIG",
    "PAYMENT",
    NULL
};

const static char *aducidAuthStatuses[] = {
    "OK",
    "ERR",
    "UV",
    "USP",
    "DI",
    "UPR",
    "CR",
    "UI",
    "MI",
    "VI",
    "UIP",
    "USSP",
    "NEO",
    "UOP",
    "NER",
    "IE",
    "NAU",
    "NU",
    "NTD",
    "DR",
    "SPE",
    "NAP",
    "UU",
    "UUS",
    "UTL",
    "UCC",
    "NOP",
    "UIL",
    "ILM",
    "ISE",
    "NSA",
    "KO",
    "PPNP",
    "NS",
    "CTO",
    "LI",
    "DMR",
    "UMR",
    "CMR",
    "MET",
    "BIM",
    "DLN",
    "MCT",
    "BEE",
    "UBM",
    "PCD",
    NULL
};


/* ADUCID text constants end */

const char *aducid_enum_to_str(const int aenum,const char *array[]) {
    int cnt=0;

    while( array[cnt] != NULL ) { cnt++; }
    if( aenum < 1 || aenum > cnt ) { return NULL; }
    return array[aenum - 1];
}

int aducid_str_to_enum(const char *aenum,const char *array[]) {
    int i;

    if(! aenum ) { return 0; }
    for(i=0 ; array[i] != NULL; i++) {
        if( strcasecmp(array[i],aenum) == 0 ) {
            return i+1;
        }
    }
    return 0;
}

DLL_PUBLIC
const char *aducid_operation_str(AducidOperation operation) {
    return aducid_enum_to_str(operation,aducidOperations);
}

DLL_PUBLIC
AducidOperation aducid_operation_enum(char *operation) {
    return (AducidOperation)aducid_str_to_enum(operation,aducidOperations);
}

DLL_PUBLIC
const char *aducid_attribute_set_str(AducidAttributeSet set) {
    return aducid_enum_to_str(set,aducidAttributeSets);
}

DLL_PUBLIC
AducidAttributeSet aducid_attribute_set_enum(char *set) {
    return (AducidAttributeSet)aducid_str_to_enum(set,aducidAttributeSets);
}

DLL_PUBLIC
const char *aducid_aim_status_str(AducidAIMStatus status) {
    return aducid_enum_to_str(status,aducidAIMStatuses);
}

DLL_PUBLIC
AducidAIMStatus aducid_aim_status_enum(char *status) {
    return (AducidAIMStatus)aducid_str_to_enum(status,aducidAIMStatuses);
}

DLL_PUBLIC
const char *aducid_method_str(AducidMethod method) {
    return aducid_enum_to_str(method,aducidMethods);
}

DLL_PUBLIC
AducidMethod aducid_method_enum(char *method) {
    return (AducidMethod)aducid_str_to_enum(method,aducidMethods);
}

DLL_PUBLIC
const char *aducid_algorithm_str(AducidAlgorithm alg) {
    return aducid_enum_to_str(alg,aducidAlgorithms);
}

DLL_PUBLIC
AducidAlgorithm aducid_algorithm_enum(char *alg) {
    return (AducidAlgorithm)aducid_str_to_enum(alg,aducidAlgorithms);
}

DLL_PUBLIC
const char *aducid_auth_status_str(AducidAuthStatus status) {
    return aducid_enum_to_str(status,aducidAuthStatuses);
}

DLL_PUBLIC
AducidAuthStatus aducid_auth_status_enum(char *status) {
    return (AducidAuthStatus)aducid_str_to_enum(status,aducidAuthStatuses);
}

DLL_PUBLIC
AducidAIMRequestOperationResponse *aducid_aim_request_operation(const char *R4,
                                                                AducidOperation operation,
                                                                const char *AIMName,
                                                                const char *authId,
                                                                const char *bindingKey,
                                                                const char *methodName,
                                                                const char *methodParameter,
                                                                const char *personalObject,
                                                                const char *AAIM2,
                                                                const char *ilData,
                                                                const char *peigReturnName)
{
    char *XML;
    char *dom,*p;
    AducidAIMRequestOperationResponse *result;
    
    XML = create_aim_request_operation_xml(
                                           aducid_operation_str(operation),
                                           AIMName,authId,bindingKey, methodName, methodParameter,
                                           personalObject,AAIM2,ilData,
                                           peigReturnName
                                           );
    dom = soap_request(R4,"AIMrequestOperation",XML);

    /* dom = xmlParseDoc(BAD_CAST response); */
    result = NULL;
    if(dom != NULL) {
        result = (AducidAIMRequestOperationResponse *)malloc( sizeof(AducidAIMRequestOperationResponse) );
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

DLL_PUBLIC
AducidAIMGetPSLAttributesResponse *aducid_aim_get_psl_attributes(const char *R4,
                                                                 const char *authId,
                                                                 const char *bindingId,
                                                                 const char *AIMName,
                                                                 const char *authKey,
                                                                 AducidAttributeSet attributeSet) {
    char *XML;
    char *dom, *p;
    AducidAIMGetPSLAttributesResponse *result;
    
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
        result = (AducidAIMGetPSLAttributesResponse *)malloc( sizeof(AducidAIMGetPSLAttributesResponse) );
        memset(result,0,sizeof(AducidAIMGetPSLAttributesResponse));

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
        result->orangeCount = xml_get_single_node_text(dom,"//orangeCount");
	result->orangeTime = xml_get_single_node_text(dom,"//orangeTime");

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


DLL_PUBLIC
AducidAIMExecutePersonalObjectResponse *aducid_aim_execute_personal_object(
    const char *R4,
    const char *authId,
    const char *AIMName,
    const char *authKey,
    AducidMethod methodName,
    const char *personalObjectName,
    AducidAlgorithm personalObjectAlgorithm,
    AducidAttributeList *personalObjectData,
    const char *ILID, const char *AAIM2, const char *ilData
                                                                           ) {
    char *XML;
    char *dom;
    char *p;
    AducidAIMExecutePersonalObjectResponse *result;
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
    result = (AducidAIMExecutePersonalObjectResponse *)malloc( sizeof(AducidAIMExecutePersonalObjectResponse) );
    memset(result,0,sizeof(AducidAIMExecutePersonalObjectResponse) );

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

DLL_PUBLIC
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
    AducidAIMStatus AIMStatus;
    AducidAuthStatus AuthStatus;
    
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


DLL_PUBLIC
AducidHandle aducid_new(const char *AIM, const char *authId, const char *authKey, const char *bindingId, const char *bindingKey) {
    AducidHandle handle;
    char *r3 = NULL;
    char *r4 = NULL;
    
    if( AIM == NULL ) { return NULL; }
    handle = (AducidHandleStruct *)malloc( sizeof(AducidHandleStruct) );
    if(!handle) { return NULL; }
    memset(handle,0,sizeof(AducidHandleStruct) );
    /* AIM can be aim.example.com 10.0.0.1 http[s]://aim.example.com:8080 */
    if( (strncasecmp(AIM,"http://",7) != 0 ) && (strncasecmp(AIM,"https://",8) != 0) ) {
        /* protocol missing */
        r3 = dyn_strcat(r3,"http://",false);
    }
    r3 = dyn_strcat(r3,strdup(AIM),true);
    if( (strlen(r3) > 0) && (r3[strlen(r3)-1] != '/' ) ) {
        /* add trailing slash */
        r3 = dyn_strcat(r3,"/",false);
    }
    r4 = strdup(r3);
    handle->R3 = dyn_strcat(r3,"AIM/services/R3",false);
    handle->R4 = dyn_strcat(r4,"AIM/services/R4",false);
    if(authId) {
        handle->authId = strdup(authId);
        if(authKey) { handle->authKey = strdup(authKey); }
        if(bindingId) { handle->bindingId = strdup(bindingId); }
        if(bindingKey) { handle->bindingKey = strdup(bindingKey); }
    }
    return handle;
}

DLL_PUBLIC
void aducid_set_authid(AducidHandle handle, const char *authId) {
    if(!handle) return;
    
    safe_free(handle->authId);
    if(authId) {
        handle->authId = strdup(authId);
    } else {
        handle->authId = NULL;
    }
}

DLL_PUBLIC
const char *aducid_get_authid(AducidHandle handle) {
    if(!handle) return NULL;
    return handle->authId;
}

DLL_PUBLIC
void aducid_set_authkey(AducidHandle handle, const char *authKey) {
    if(!handle) return;
    
    safe_free(handle->authKey);
    if(authKey) {
        handle->authKey = strdup(authKey);
    } else {
        handle->authKey = NULL;
    }
}

DLL_PUBLIC
const char *aducid_get_authkey(AducidHandle handle) {
    if(!handle) return NULL;
    return handle->authKey;
}

DLL_PUBLIC
void aducid_set_bindingkey(AducidHandle handle, const char *bindingKey) {
    if(!handle) return;
    
    safe_free(handle->bindingKey);
    if(bindingKey) {
        handle->bindingKey = strdup(bindingKey);
    } else {
        handle->bindingKey = NULL;
    }
}

DLL_PUBLIC
const char *aducid_get_bindingkey(AducidHandle handle) {
    if(!handle) return NULL;
    return handle->bindingKey;
}

DLL_PUBLIC
void aducid_set_bindingid(AducidHandle handle, const char *bindingId) {
    if(!handle) return;
    
    safe_free(handle->bindingId);
    if(bindingId) {
        handle->bindingId = strdup(bindingId);
    } else {
        handle->bindingId = NULL;
    }
}

DLL_PUBLIC
const char *aducid_get_bindingid(AducidHandle handle) {
    if(!handle) return NULL;
    return handle->bindingId;
}

DLL_PUBLIC
const char *aducid_request_operation(AducidHandle handle,
                               AducidOperation operation,
                               const char* methodName,
                               const char* methodParameter,
                               const char *personalObject,
                               const char *AAIM2,
                               const char *ilData,
                               const char *peigReturnName) {
    AducidAIMRequestOperationResponse *response;

    if(!handle)return NULL;
    if( handle->authId == NULL ) {
        safe_free(handle->authKey);
        safe_free(handle->bindingId);
        safe_free(handle->bindingKey);
        handle->authKey = NULL;
        handle->bindingKey = NULL;
        handle->bindingId = NULL;
    }
    response = aducid_aim_request_operation(handle->R4,
                                            operation,
                                            handle->AIMName,
                                            handle->authId,
                                            handle->bindingKey,
                                            methodName, methodParameter,
                                            personalObject,AAIM2,ilData,
                                            peigReturnName);
    if( response && (response->authId) ) {
        if( handle->authId == NULL ) {
            handle->authId = response->authId;
            response->authId = NULL;
        }
        handle->bindingId = response->bindingId;
        handle->bindingKey = response->bindingKey;
        response->bindingId = NULL;
        response->bindingKey = NULL;
    }
    aducid_free_aim_request_operation_response(response);
    return handle->authId;
}

DLL_PUBLIC
const char *aducid_open(AducidHandle handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_OPEN,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

DLL_PUBLIC
const char *aducid_init(AducidHandle handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_INIT,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

DLL_PUBLIC
const char *aducid_reinit(AducidHandle handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_REINIT,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

DLL_PUBLIC
const char *aducid_change(AducidHandle handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_CHANGE,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

DLL_PUBLIC
const char *aducid_rechange(AducidHandle handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_RECHANGE,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

DLL_PUBLIC
const char *aducid_delete(AducidHandle handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_DELETE,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

DLL_PUBLIC
bool aducid_close(AducidHandle handle) {
    return aducid_aim_close_session(handle->R4,handle->authId,handle->AIMName,handle->authKey);
}

DLL_PUBLIC
AducidAIMGetPSLAttributesResponse *aducid_get_psl_attributes(AducidHandle handle,AducidAttributeSet attributeSet, bool useCache){
    if(!handle || !handle->authId) return false;
    if(attributeSet <= ADUCID_ATTRIBUTE_SET_INVALID || attributeSet > ADUCID_ATTRIBUTE_SET_ERROR ) return false;
    if( ! useCache && handle->PSLCache[attributeSet-1] ) {
        aducid_free_aim_get_psl_attributes_response(handle->PSLCache[attributeSet-1]);
        handle->PSLCache[attributeSet-1] = NULL;
    }
    if( handle->PSLCache[attributeSet-1] != NULL ) {
        return handle->PSLCache[attributeSet-1];
    }
    handle->PSLCache[attributeSet-1] = aducid_aim_get_psl_attributes(handle->R4,handle->authId,handle->bindingId,NULL,handle->authKey,attributeSet);
    if( handle->PSLCache[attributeSet-1] && handle->PSLCache[attributeSet-1]->authKey2) {
        aducid_set_authkey(handle,handle->PSLCache[attributeSet-1]->authKey2);
    }
    return handle->PSLCache[attributeSet-1];    
}

DLL_PUBLIC
bool aducid_wait_for_operation(AducidHandle handle) {
    AducidAIMGetPSLAttributesResponse *status;
    
    if(!handle) return false;
    if(!handle->authId) return false;
    
    while(true) {
        status = aducid_get_psl_attributes(handle,ADUCID_ATTRIBUTE_SET_STATUS,false);
        if( (status == NULL) || (status->statusAIM == ADUCID_AIM_STATUS_INVALID) ) {
            /* unexpected error */
            return false;
        }
        if( (status->statusAIM == ADUCID_AIM_STATUS_START) || (status->statusAIM == ADUCID_AIM_STATUS_WORKING) ) {
            sleep(1);
        } else {
            return true;
        }
    }
}

DLL_PUBLIC
bool aducid_verify(AducidHandle handle) {
    AducidAIMGetPSLAttributesResponse *status;
    if(!handle) return false;
    
    status = aducid_get_psl_attributes(handle,ADUCID_ATTRIBUTE_SET_ALL,true);
    if(!status) return false;
    return (status->statusAuth == ADUCID_AUTHSTATUS_OK) && (status->statusAIM == ADUCID_AIM_STATUS_ACTIVE);
}

DLL_PUBLIC
AducidAttributeList *aducid_get_attributes(AducidHandle handle,char *attrSetName) {
    AducidAttributeList *list = NULL;
    AducidAIMExecutePersonalObjectResponse *dpo;
    
    if(!handle || !handle->authId || !handle->authKey ) return NULL;
    if( attrSetName == NULL ) { attrSetName = "default"; }
    dpo = aducid_aim_execute_personal_object(handle->R4,
                                             handle->authId,
                                             NULL,
                                             handle->authKey,
                                             ADUCID_METHOD_READ,
                                             attrSetName,
                                             ADUCID_ALGORITHM_USER_ATTR_SET,
                                             NULL,NULL,NULL,NULL);
    if(dpo && dpo->personalObject ) {
        list = dpo->personalObject;
        dpo->personalObject = NULL;
    }
    aducid_free_aim_execute_personal_object_response(dpo);
    return list;
}

DLL_PUBLIC
bool aducid_set_attributes(AducidHandle handle, char *attrSetName, AducidAttributeList *attrs) {
    AducidAIMExecutePersonalObjectResponse *dpo;
    
    if(!handle || !handle->authId || !handle->authKey ) return false;
    if( attrSetName == NULL ) { attrSetName = "default"; }
    dpo = aducid_aim_execute_personal_object(handle->R4,
                                             handle->authId,
                                             NULL,
                                             handle->authKey,
                                             ADUCID_METHOD_WRITE,
                                             attrSetName,
                                             ADUCID_ALGORITHM_USER_ATTR_SET,
                                             attrs,NULL,NULL,NULL);
    /* FIXME: check statusAIM/statusAuth */
    aducid_free_aim_execute_personal_object_response(dpo);
    return true;
}

DLL_PUBLIC
char *aducid_get_user_database_index(AducidHandle handle) {
    AducidAIMGetPSLAttributesResponse *response;
    
    if( !handle || !handle->authId || !handle->authKey ) return NULL;
    response = aducid_get_psl_attributes(handle,ADUCID_ATTRIBUTE_SET_ALL,true);
    return response->userDatabaseIndex;
}

DLL_PUBLIC
void aducid_clear_psl_cache(AducidHandle handle) {
    if(handle) {
        int i;

        for( i=0; i < ADUCID_ATTRIBUTE_SET_ERROR; i++) {
            aducid_free_aim_get_psl_attributes_response(handle->PSLCache[i]);
        }
    }
}

DLL_PUBLIC
void aducid_free(AducidHandle handle) {
    if(handle) {
        safe_free(handle->authId);
        safe_free(handle->authKey);
        safe_free(handle->AIMName);
        safe_free(handle->R3);
        safe_free(handle->R4);
        aducid_clear_psl_cache(handle);
    }
    safe_free(handle);
}

/*
  DLL_PUBLIC AducidClient::AducidClient(char *aim) {
  handle = aducid_new(aim);
  }
  DLL_PUBLIC AducidClient::~AducidClient() {
  aducid_free(handle);
  }
  DLL_PUBLIC char *AducidClient::open() {
  return aducid_open(handle);
  }
  DLL_PUBLIC char *AducidClient::init() {
  return aducid_init(handle);
  }
  DLL_PUBLIC char *AducidClient::reinit() {
  return aducid_reinit(handle);
  }
  DLL_PUBLIC char *AducidClient::change() {
  return aducid_change(handle);
  }
  DLL_PUBLIC char *AducidClient::rechange() {
  return aducid_rechange(handle);
  }
  DLL_PUBLIC bool AducidClient::close() {
  return aducid_close(handle);
  }
  DLL_PUBLIC AIMGetPSLAttributesResponse *AducidClient::getPslAttributes(AducidAttributeSet attributeSet, bool useCache) {
  return aducid_get_psl_attributes(handle,attributeSet,useCache);
  }
*/

DLL_PUBLIC
int aducid_library_init() {
#if defined(_WIN32) || defined(_W64)
    return 0;
#else
    return curl_global_init(CURL_GLOBAL_ALL);
#endif
}

DLL_PUBLIC
int aducid_library_free() {
#if defined(_WIN32) || defined(_W64)
    return 0;
#else
    curl_global_cleanup();
    return 0;
#endif
}
