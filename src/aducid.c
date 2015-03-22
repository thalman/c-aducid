#include "definitions.h"
#include "textconstants.h"
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


ADUCID_PUBLIC_FUNC
AducidHandle_t aducid_new(const char *AIM, const char *authId, const char *authKey, const char *bindingId, const char *bindingKey) {
    AducidHandle_t handle;
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

ADUCID_PUBLIC_FUNC
void aducid_set_authid(AducidHandle_t handle, const char *authId) {
    if(!handle) return;
    
    safe_free(handle->authId);
    if(authId) {
        handle->authId = strdup(authId);
    } else {
        handle->authId = NULL;
    }
}

ADUCID_PUBLIC_FUNC
const char *aducid_get_authid(AducidHandle_t handle) {
    if(!handle) return NULL;
    return handle->authId;
}

ADUCID_PUBLIC_FUNC
void aducid_set_authkey(AducidHandle_t handle, const char *authKey) {
    if(!handle) return;
    
    safe_free(handle->authKey);
    if(authKey) {
        handle->authKey = strdup(authKey);
    } else {
        handle->authKey = NULL;
    }
}

ADUCID_PUBLIC_FUNC
const char *aducid_get_authkey(AducidHandle_t handle) {
    if(!handle) return NULL;
    return handle->authKey;
}

ADUCID_PUBLIC_FUNC
void aducid_set_bindingkey(AducidHandle_t handle, const char *bindingKey) {
    if(!handle) return;
    
    safe_free(handle->bindingKey);
    if(bindingKey) {
        handle->bindingKey = strdup(bindingKey);
    } else {
        handle->bindingKey = NULL;
    }
}

ADUCID_PUBLIC_FUNC
const char *aducid_get_bindingkey(AducidHandle_t handle) {
    if(!handle) return NULL;
    return handle->bindingKey;
}

ADUCID_PUBLIC_FUNC
void aducid_set_bindingid(AducidHandle_t handle, const char *bindingId) {
    if(!handle) return;
    
    safe_free(handle->bindingId);
    if(bindingId) {
        handle->bindingId = strdup(bindingId);
    } else {
        handle->bindingId = NULL;
    }
}

ADUCID_PUBLIC_FUNC
const char *aducid_get_bindingid(AducidHandle_t handle) {
    if(!handle) return NULL;
    return handle->bindingId;
}

const char *
aducid_request_operation(AducidHandle_t handle,
                         AducidOperation_t operation,
                         const char* methodName,
                         const AducidAttributeList_t methodParameters,
                         const AducidAttributeList_t personalObject,
                         const char *AAIM2,
                         const char *ilData,
                         const char *peigReturnName) {
    AducidAIMRequestOperationResponse_t *response;
    
    if(!handle)return NULL;
    /*
    if( handle->authId == NULL ) {
        safe_free(handle->authKey);
        safe_free(handle->bindingId);
        safe_free(handle->bindingKey);
        handle->authKey = NULL;
        handle->bindingKey = NULL;
        handle->bindingId = NULL;
    }
    */
    safe_free(handle->authId);
    safe_free(handle->authKey);
    safe_free(handle->bindingId);
    safe_free(handle->bindingKey);
    handle->authId = NULL;
    handle->authKey = NULL;
    handle->bindingId = NULL;
    handle->bindingKey = NULL;
    aducid_clear_psl_cache( handle );
    response = aducid_aim_request_operation(handle->R4,
                                            operation,
                                            handle->AIMName,
                                            handle->authId,
                                            handle->bindingKey,
                                            methodName, methodParameters,
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

ADUCID_PUBLIC_FUNC
const char *aducid_open(AducidHandle_t handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_OPEN,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

ADUCID_PUBLIC_FUNC
const char *aducid_init(AducidHandle_t handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_INIT,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

ADUCID_PUBLIC_FUNC
const char *aducid_reinit(AducidHandle_t handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_REINIT,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

ADUCID_PUBLIC_FUNC
const char *aducid_change(AducidHandle_t handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_CHANGE,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

ADUCID_PUBLIC_FUNC
const char *aducid_rechange(AducidHandle_t handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_RECHANGE,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

ADUCID_PUBLIC_FUNC
const char *aducid_delete(AducidHandle_t handle, const char *peigReturnName) {
    return aducid_request_operation(handle,ADUCID_OPERATION_DELETE,NULL,NULL,NULL,NULL,NULL,peigReturnName);
}

ADUCID_PUBLIC_FUNC bool
aducid_close(AducidHandle_t handle) {
    return aducid_aim_close_session(handle->R4,handle->authId,handle->AIMName,handle->authKey);
}


ADUCID_PUBLIC_FUNC AducidAIMGetPSLAttributesResponse_t *
aducid_get_psl_attributes( AducidHandle_t handle, AducidAttributeSet_t attributeSet, bool useCache){
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

ADUCID_PUBLIC_FUNC bool
aducid_wait_for_operation( AducidHandle_t handle ) {
    AducidAIMGetPSLAttributesResponse_t *status;
    
    if(!handle) return false;
    if(!handle->authId) return false;
    
    while(true) {
        status = aducid_get_psl_attributes( handle, ADUCID_ATTRIBUTE_SET_STATUS, false );
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

ADUCID_PUBLIC_FUNC
bool aducid_verify(AducidHandle_t handle) {
    AducidAIMGetPSLAttributesResponse_t *status;
    if(!handle) return false;
    
    status = aducid_get_psl_attributes(handle,ADUCID_ATTRIBUTE_SET_ALL,true);
    if(!status) return false;
    return (status->statusAuth == ADUCID_AUTHSTATUS_OK) && (status->statusAIM == ADUCID_AIM_STATUS_ACTIVE);
}

ADUCID_PUBLIC_FUNC AducidAttributeList_t *
aducid_get_attributes(AducidHandle_t handle, char *attrSetName) {
    AducidAttributeList_t *list = NULL;
    AducidAIMExecutePersonalObjectResponse_t *dpo;
    
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

ADUCID_PUBLIC_FUNC bool
aducid_set_attributes(AducidHandle_t handle, char *attrSetName, AducidAttributeList_t *attrs) {
    AducidAIMExecutePersonalObjectResponse_t *dpo;
    
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

ADUCID_PUBLIC_FUNC
const char *aducid_get_user_database_index(AducidHandle_t handle) {
    AducidAIMGetPSLAttributesResponse_t *response;
    
    if( !handle || !handle->authId || !handle->authKey ) return NULL;
    response = aducid_get_psl_attributes(handle,ADUCID_ATTRIBUTE_SET_ALL,true);
    return response->userDatabaseIndex;
}

ADUCID_PUBLIC_FUNC
void aducid_clear_psl_cache( AducidHandle_t handle ) {
    if(handle) {
        int i;
        for( i=0; i < ADUCID_ATTRIBUTE_SET_ERROR; i++) {
            aducid_free_aim_get_psl_attributes_response(handle->PSLCache[i]);
            handle->PSLCache[i] = NULL;
        }
    }
}

ADUCID_PUBLIC_FUNC
void aducid_free(AducidHandle_t handle) {
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
  ADUCID_PUBLIC_FUNC AducidClient::AducidClient(char *aim) {
  handle = aducid_new(aim);
  }
  ADUCID_PUBLIC_FUNC AducidClient::~AducidClient() {
  aducid_free(handle);
  }
  ADUCID_PUBLIC_FUNC char *AducidClient::open() {
  return aducid_open(handle);
  }
  ADUCID_PUBLIC_FUNC char *AducidClient::init() {
  return aducid_init(handle);
  }
  ADUCID_PUBLIC_FUNC char *AducidClient::reinit() {
  return aducid_reinit(handle);
  }
  ADUCID_PUBLIC_FUNC char *AducidClient::change() {
  return aducid_change(handle);
  }
  ADUCID_PUBLIC_FUNC char *AducidClient::rechange() {
  return aducid_rechange(handle);
  }
  ADUCID_PUBLIC_FUNC bool AducidClient::close() {
  return aducid_close(handle);
  }
  ADUCID_PUBLIC_FUNC AIMGetPSLAttributesResponse *AducidClient::getPslAttributes(AducidAttributeSet attributeSet, bool useCache) {
  return aducid_get_psl_attributes(handle,attributeSet,useCache);
  }
*/

ADUCID_PUBLIC_FUNC
int aducid_library_init() {
#if defined(_WIN32) || defined(_W64)
    return 0;
#else
    return curl_global_init(CURL_GLOBAL_ALL);
#endif
}

ADUCID_PUBLIC_FUNC
int aducid_library_free() {
#if defined(_WIN32) || defined(_W64)
    return 0;
#else
    curl_global_cleanup();
    return 0;
#endif
}
