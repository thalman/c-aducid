#ifndef __ADUCID_H__
#define __ADUCID_H__

#ifdef __cplusplus
extern "C" {
#endif

/* #include "config.h" */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  #ifdef BUILDING_ADUCID_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) /* Note: actually gcc seems to also supports this syntax. */
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) /* Note: actually gcc seems to also supports this syntax. */
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif

#if defined _WIN32 || defined _WIN64
#ifndef bool
#define bool int
#define false 0
#define true 1
#endif
#else
#include<stdbool.h>
#endif
/**
 * attribute list functions
 */
typedef void *AducidAttributeList;

DLL_PUBLIC AducidAttributeList aducid_attr_list_new();
DLL_PUBLIC int   aducid_attr_list_count( const AducidAttributeList handle );
DLL_PUBLIC char *aducid_attr_list_get_item_name( const AducidAttributeList handle, int idx );
DLL_PUBLIC char *aducid_attr_list_get_item_value( const AducidAttributeList handle, int idx );
DLL_PUBLIC void  aducid_attr_list_append( AducidAttributeList handle,char *name,char *value );
DLL_PUBLIC void  aducid_attr_list_prepend( AducidAttributeList handle,char *name,char *value );
DLL_PUBLIC void  aducid_attr_list_insert( AducidAttributeList handle,char *name,char *value,int idx );
DLL_PUBLIC char *aducid_attr_list_get_first_by_name( const AducidAttributeList handle, const char *name );
DLL_PUBLIC char *aducid_attr_list_get_next_by_name( const AducidAttributeList handle, const char *name );
DLL_PUBLIC int   aducid_attr_list_get_count_by_name( const AducidAttributeList handle, const char *name );
DLL_PUBLIC bool  aducid_attr_list_delete( AducidAttributeList handle, int idx );
DLL_PUBLIC bool  aducid_attr_list_delete_by_name( AducidAttributeList handle,char *name );
DLL_PUBLIC void  aducid_attr_list_free( AducidAttributeList handle );

/* ADUCID enum constants begin */

typedef enum {
    ADUCID_OPERATION_INVALID = 0,
    ADUCID_OPERATION_OPEN,
    ADUCID_OPERATION_INIT,
    ADUCID_OPERATION_REINIT,
    ADUCID_OPERATION_CHANGE,
    ADUCID_OPERATION_RECHANGE,
    ADUCID_OPERATION_DELETE,
    ADUCID_OPERATION_REPLICA,
    ADUCID_OPERATION_LINK,
    ADUCID_OPERATION_EXUSE,
    ADUCID_OPERATION_AUTO_CHANGE
} AducidOperation;

typedef enum {
    ADUCID_ATTRIBUTE_SET_INVALID = 0,
    ADUCID_ATTRIBUTE_SET_STATUS,
    ADUCID_ATTRIBUTE_SET_BASIC,
    ADUCID_ATTRIBUTE_SET_ALL,
    ADUCID_ATTRIBUTE_SET_VALIDITY,
    ADUCID_ATTRIBUTE_SET_LINK,
    ADUCID_ATTRIBUTE_SET_ERROR,
    ADUCID_ATTRIBUTE_SET_PEIG_RETURN_NAME
} AducidAttributeSet;

typedef enum {
    ADUCID_AIM_STATUS_INVALID = 0,
    ADUCID_AIM_STATUS_NONE,
    ADUCID_AIM_STATUS_ERROR,
    ADUCID_AIM_STATUS_WORKING,
    ADUCID_AIM_STATUS_CLIENT_BINDING,
    ADUCID_AIM_STATUS_START,
    ADUCID_AIM_STATUS_FINISHED,
    ADUCID_AIM_STATUS_ACTIVE,
    ADUCID_AIM_STATUS_INTERNAL_ERROR,
    ADUCID_AIM_STATUS_START_TIMEOUT,
    ADUCID_AIM_STATUS_PROCESS_TIMEOUT,
    ADUCID_AIM_STATUS_BINDING_TIMEOUT,
    ADUCID_AIM_STATUS_END,
    ADUCID_AIM_STATUS_PASSIVE,
    ADUCID_AIM_STATUS_AUTH_ERROR
} AducidAIMStatus;

typedef enum {
    ADUCID_METHOD_INVALID = 0,
    ADUCID_METHOD_INIT,
    ADUCID_METHOD_CREATE,
    ADUCID_METHOD_CHANGE,
    ADUCID_METHOD_READ,
    ADUCID_METHOD_DELETE,
    ADUCID_METHOD_WRITE,
    ADUCID_METHOD_LEGACY_LOGIN,
    ADUCID_METHOD_SET,
    ADUCID_METHOD_GEN_KEY_PAIR,
    ADUCID_METHOD_WRITE_CERT,
    ADUCID_METHOD_LEGACY_SIGN,
    ADUCID_METHOD_OTP_VERIFICATION,
    ADUCID_METHOD_IDENTITY_LINK_READ,
    ADUCID_METHOD_PASSWORD_DECRYPT,
    ADUCID_METHOD_SET_EXECUTE_RIGHT,
    ADUCID_METHOD_CLEAR_EXECUTE_RIGHT,
    ADUCID_METHOD_UPLOAD_CERT,
    ADUCID_METHOD_TEMP_ENABLE_CAPI,
    ADUCID_METHOD_TEMP_DISABLE_CAPI,
    ADUCID_METHOD_PERM_ENABLE_CAPI,
    ADUCID_METHOD_PERM_DISABLE_CAPI,
    ADUCID_METHOD_PPO_RESULT,
    ADUCID_METHOD_AIM_READ,
    ADUCID_METHOD_READ_PEIG_COUNT,
    ADUCID_METHOD_ACTIVATE_OTHER_PEIGS,
    ADUCID_METHOD_DEACTIVATE_OTHER_PEIGS,
    ADUCID_METHOD_ACTIVATE_THE_PEIG,
    ADUCID_METHOD_DEACTIVATE_THE_PEIG,
    ADUCID_METHOD_READ_PEIG_ID,
    ADUCID_METHOD_READ_OTHER_PEIGS_ID,
    ADUCID_METHOD_CREATE_ROOM_BY_NAME,
    ADUCID_METHOD_CREATE_ROOM_BY_STORY,
    ADUCID_METHOD_ENTER_ROOM_BY_NAME,
    ADUCID_METHOD_ENTER_ROOM_BY_STORY,
    ADUCID_METHOD_CONFIRM_TRANSACTION,
    ADUCID_METHOD_VERIFY_LF,
    ADUCID_METHOD_PEIG_LOCAL_LINK
} AducidMethod;

typedef enum {
    ADUCID_ALGORITHM_INVALID = 0,
    ADUCID_ALGORITHM_USER_ATTR_SET,
    ADUCID_ALGORITHM_PASSWD,
    ADUCID_ALGORITHM_PASSWD_AIM,
    ADUCID_ALGORITHM_BIN_STRING,
    ADUCID_ALGORITHM_OTP_AIM_1,
    ADUCID_ALGORITHM_X509_SIG,
    ADUCID_ALGORITHM_PAYMENT
} AducidAlgorithm;

typedef enum {
    ADUCID_AUTHSTATUS_INVALID = 0,
    ADUCID_AUTHSTATUS_OK,
    ADUCID_AUTHSTATUS_ERR,
    ADUCID_AUTHSTATUS_UV,
    ADUCID_AUTHSTATUS_USP,
    ADUCID_AUTHSTATUS_DI,
    ADUCID_AUTHSTATUS_UPR,
    ADUCID_AUTHSTATUS_CR,
    ADUCID_AUTHSTATUS_UI,
    ADUCID_AUTHSTATUS_MI,
    ADUCID_AUTHSTATUS_VI,
    ADUCID_AUTHSTATUS_UIP,
    ADUCID_AUTHSTATUS_USSP,
    ADUCID_AUTHSTATUS_NEO,
    ADUCID_AUTHSTATUS_UOP,
    ADUCID_AUTHSTATUS_NER,
    ADUCID_AUTHSTATUS_IE,
    ADUCID_AUTHSTATUS_NAU,
    ADUCID_AUTHSTATUS_NU,
    ADUCID_AUTHSTATUS_NTD,
    ADUCID_AUTHSTATUS_DR,
    ADUCID_AUTHSTATUS_SPE,
    ADUCID_AUTHSTATUS_NAP,
    ADUCID_AUTHSTATUS_UU,
    ADUCID_AUTHSTATUS_UUS,
    ADUCID_AUTHSTATUS_UTL,
    ADUCID_AUTHSTATUS_UCC,
    ADUCID_AUTHSTATUS_NOP,
    ADUCID_AUTHSTATUS_UIL,
    ADUCID_AUTHSTATUS_ILM,
    ADUCID_AUTHSTATUS_ISE,
    ADUCID_AUTHSTATUS_NSA,
    ADUCID_AUTHSTATUS_KO,
    ADUCID_AUTHSTATUS_PPNP,
    ADUCID_AUTHSTATUS_NS,
    ADUCID_AUTHSTATUS_CTO,
    ADUCID_AUTHSTATUS_LI,
    ADUCID_AUTHSTATUS_DMR,
    ADUCID_AUTHSTATUS_UMR,
    ADUCID_AUTHSTATUS_CMR,
    ADUCID_AUTHSTATUS_MET,
    ADUCID_AUTHSTATUS_BIM,
    ADUCID_AUTHSTATUS_DLN,
    ADUCID_AUTHSTATUS_MCT,
    ADUCID_AUTHSTATUS_BEE,
    ADUCID_AUTHSTATUS_UBM,
    ADUCID_AUTHSTATUS_PCD
} AducidAuthStatus;


/* ADUCID enum constants end */

typedef struct {
    char *authId;
    char *bindingId;
    char *bindingKey;
    AducidAIMStatus statusAIM;
    AducidAuthStatus statusAuth;
} AducidAIMRequestOperationResponse;

typedef struct {
    AducidAIMStatus statusAIM;
    AducidAuthStatus statusAuth;
    char *statusMessage;
    AducidAttributeList personalObject;
} AducidAIMExecutePersonalObjectResponse;

typedef struct {
    AducidAIMStatus statusAIM;
    AducidAuthStatus statusAuth;
    AducidOperation operationName;
    char *userDatabaseIndex;
    char *userId;
    char *validityCount;
    char *validityTime;
    char *orangeCount;
    char *orangeTime;
    char *securityProfileName;
    char *authenticationProtocolName;
    char *securityLevel;
    char *ILID;
    char *ilTypeName;
    char *ilAlgorithmName;
    char *ilValidityCount;
    char *ilValidityTime;
    /**
       FIXME
       personalObjectName
       personalObject
    */
    char *authKey2;
    char *sessionKey;
    char *bindingType;
} AducidAIMGetPSLAttributesResponse;

typedef struct {
    char *authId;
    char *authKey;
    char *bindingId;
    char *bindingKey;
    char *AIMName;
    char *R3;
    char *R4;
    AducidAIMGetPSLAttributesResponse *PSLCache[ADUCID_ATTRIBUTE_SET_ERROR];
} AducidHandleStruct;

typedef AducidHandleStruct *AducidHandle;

/**
  * Aducid operations
  */
DLL_PUBLIC void aducid_free_aim_request_operation_response(AducidAIMRequestOperationResponse *response);
DLL_PUBLIC void aducid_free_aim_get_psl_attributes_response(AducidAIMGetPSLAttributesResponse *response);
DLL_PUBLIC void aducid_free_aim_execute_personal_object_response(AducidAIMExecutePersonalObjectResponse *response);

DLL_PUBLIC AducidAIMRequestOperationResponse *aducid_aim_request_operation(
    const char *R4,
    AducidOperation operation,
    const char *AIMName,
    const char *authId,
    const char *bindingKey,
    const char *methodName,
    const AducidAttributeList methodParameter,
    const AducidAttributeList personalObject,
    const char *AAIM2,
    const char *ilData,
    const char *peigReturnName);
    
DLL_PUBLIC AducidAIMGetPSLAttributesResponse *aducid_aim_get_psl_attributes(
    const char *R4,
    const char *authId,
    const char *bindingId,
    const char *AIMName,
    const char *authKey,
    AducidAttributeSet attributeSet);

DLL_PUBLIC AducidAIMExecutePersonalObjectResponse *aducid_aim_execute_personal_object(
    const char *R4,
    const char *authId,
    const char *AIMName,
    const char *authKey,
    AducidMethod methodName,
    const char *personalObjectName,
    AducidAlgorithm personalObjectAlgorithm,
    AducidAttributeList *personalObjectData,
    const char *ILID,
    const char *AAIM2,
    const char *ilData);

DLL_PUBLIC bool aducid_aim_close_session(
    const char *R4,
    const char *authId,
    const char *AIMName,
    const char *authKey);

/*
const char *    aducid_operation_str(AducidOperation operation);
AducidOperation aducid_operation_enum(char *operation);
*/
DLL_PUBLIC const char *aducid_operation_str(AducidOperation operation);
DLL_PUBLIC AducidOperation aducid_operation_enum(char *operation);

DLL_PUBLIC const char *       aducid_attribute_set_str(AducidAttributeSet set);
DLL_PUBLIC AducidAttributeSet aducid_attribute_set_enum(char *set);

DLL_PUBLIC const char *    aducid_aim_status_str(AducidAIMStatus status);
DLL_PUBLIC AducidAIMStatus aducid_aim_status_enum(char *status);

DLL_PUBLIC const char * aducid_method_str(AducidMethod method);
DLL_PUBLIC AducidMethod aducid_method_enum(char *method);

DLL_PUBLIC const char *    aducid_algorithm_str(AducidAlgorithm alg);
DLL_PUBLIC AducidAlgorithm aducid_algorithm_enum(char *alg);

DLL_PUBLIC const char *     aducid_auth_status_str(AducidAuthStatus status);
DLL_PUBLIC AducidAuthStatus aducid_auth_status_enum(char *status);

/* c interface */
DLL_PUBLIC AducidHandle aducid_new(const char *AIM, const char *authId, const char *authKey, const char *bindingId, const char *bindingKey);

DLL_PUBLIC const char *aducid_open(AducidHandle handle, const char *peigReturnName);
DLL_PUBLIC const char *aducid_init(AducidHandle handle, const char *peigReturnName);
DLL_PUBLIC const char *aducid_reinit(AducidHandle handle, const char *peigReturnName);
DLL_PUBLIC const char *aducid_change(AducidHandle handle, const char *peigReturnName);
DLL_PUBLIC const char *aducid_rechange(AducidHandle handle, const char *peigReturnName);
DLL_PUBLIC const char *aducid_delete(AducidHandle handle, const char *peigReturnName);

DLL_PUBLIC const char *aducid_exuse(AducidHandle handle,
                                    const char *methodName,
                                    const AducidAttributeList methodParameters,
                                    const AducidAttributeList personalObject,
                                    const char *peigReturnName);

DLL_PUBLIC bool aducid_close(AducidHandle handle);

DLL_PUBLIC AducidAIMGetPSLAttributesResponse *aducid_get_psl_attributes(AducidHandle handle,AducidAttributeSet attributeSet, bool useCache);
DLL_PUBLIC bool  aducid_wait_for_operation(AducidHandle handle);
DLL_PUBLIC bool  aducid_verify(AducidHandle handle);

DLL_PUBLIC AducidAttributeList *aducid_get_attributes(AducidHandle handle,char *attrSetName);
DLL_PUBLIC bool  aducid_set_attributes(AducidHandle handle, char *attrSetName, AducidAttributeList *attrs);
DLL_PUBLIC const char *aducid_get_user_database_index(AducidHandle handle);
DLL_PUBLIC void  aducid_clear_psl_cache(AducidHandle handle);

DLL_PUBLIC const char *aducid_get_authid(AducidHandle handle);
DLL_PUBLIC void  aducid_set_authid(AducidHandle handle, const char *authId);
DLL_PUBLIC const char *aducid_get_authkey(AducidHandle handle);
DLL_PUBLIC void  aducid_set_authkey(AducidHandle handle, const char *authKey);
DLL_PUBLIC const char *aducid_get_bindingkey(AducidHandle handle);
DLL_PUBLIC void  aducid_set_bindingkey(AducidHandle handle, const char *bindingKey);
DLL_PUBLIC const char *aducid_get_bindingid(AducidHandle handle);
DLL_PUBLIC void  aducid_set_bindingid(AducidHandle handle, const char *bindingId);

DLL_PUBLIC void  aducid_free(AducidHandle handle);

/* cpp interface
class DLL_PUBLIC AducidClient
{
 private:
    AducidHandle handle;
 public:
    DLL_PUBLIC AducidClient(char *aim);
    DLL_PUBLIC ~AducidClient();
    DLL_PUBLIC char *open();
    DLL_PUBLIC char *init();
    DLL_PUBLIC char *reinit();
    DLL_PUBLIC char *change();
    DLL_PUBLIC char *rechange();
    DLL_PUBLIC bool close();
    DLL_PUBLIC AIMGetPSLAttributesResponse *getPslAttributes(AducidAttributeSet attributeSet, bool useCache);
};
*/

/**
 * PEIG
 */

DLL_PUBLIC bool aducid_peig_invoke(AducidHandle handle);
DLL_PUBLIC const char *aducid_peig_get_authkey(AducidHandle handle);
DLL_PUBLIC char *aducid_get_aimproxy_url(AducidHandle handle);
DLL_PUBLIC char *aducid_get_aducid_url(AducidHandle handle);

/**
 * library inicialization
 */
DLL_PUBLIC int aducid_library_init();
DLL_PUBLIC int aducid_library_free();

#ifdef __cplusplus
}
#endif

#endif
