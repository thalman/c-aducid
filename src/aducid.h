#ifndef __ADUCID_H__
#define __ADUCID_H__

#ifdef __cplusplus
extern "C" {
#endif

/* #include "config.h" */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef ADUCID_PUBLIC_FUNC
  #if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
    /* on windows */
    #ifdef __GNUC__
      #define ADUCID_PUBLIC_FUNC __attribute__ ((dllimport))
    #else
      #define ADUCID_PUBLIC_FUNC __declspec(dllimport)
    #endif
    #define ADUCID_LOCAL_FUNC
  #else
    /* on posix */
    #define ADUCID_PUBLIC_FUNC
    #define ADUCID_LOCAL_FUNC
  #endif
#endif

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
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
typedef void *AducidAttributeList_t;

ADUCID_PUBLIC_FUNC AducidAttributeList_t aducid_attr_list_new();
ADUCID_PUBLIC_FUNC int   aducid_attr_list_count( const AducidAttributeList_t handle );
ADUCID_PUBLIC_FUNC char *aducid_attr_list_get_item_name( const AducidAttributeList_t handle, int idx );
ADUCID_PUBLIC_FUNC char *aducid_attr_list_get_item_value( const AducidAttributeList_t handle, int idx );
ADUCID_PUBLIC_FUNC void  aducid_attr_list_append( AducidAttributeList_t handle, const char *name, const char *value );
ADUCID_PUBLIC_FUNC void  aducid_attr_list_prepend( AducidAttributeList_t handle, const char *name, const char *value );
ADUCID_PUBLIC_FUNC void  aducid_attr_list_insert( AducidAttributeList_t handle, const char *name, const char *value, int idx );
ADUCID_PUBLIC_FUNC char *aducid_attr_list_get_first_by_name( const AducidAttributeList_t handle, const char *name );
ADUCID_PUBLIC_FUNC char *aducid_attr_list_get_next_by_name( const AducidAttributeList_t handle, const char *name );
ADUCID_PUBLIC_FUNC int   aducid_attr_list_get_count_by_name( const AducidAttributeList_t handle, const char *name );
ADUCID_PUBLIC_FUNC bool  aducid_attr_list_delete( AducidAttributeList_t handle, int idx );
ADUCID_PUBLIC_FUNC bool  aducid_attr_list_delete_by_name( AducidAttributeList_t handle, const char *name );
ADUCID_PUBLIC_FUNC void  aducid_attr_list_free( AducidAttributeList_t handle );

/* ADUCID enum constants begin */

typedef enum {
    ADUCID_OPERATION_INVALID = 0,
    ADUCID_OPERATION_OPEN,
    ADUCID_OPERATION_INIT,
    ADUCID_OPERATION_REINIT,
    ADUCID_OPERATION_CHANGE,
    ADUCID_OPERATION_RECHANGE,
    ADUCID_OPERATION_DELETE,
    ADUCID_OPERATION_LINK,
    ADUCID_OPERATION_EXUSE,
    ADUCID_OPERATION_AUTO_CHANGE
} AducidOperation_t;

typedef enum {
    ADUCID_ATTRIBUTE_SET_INVALID = 0,
    ADUCID_ATTRIBUTE_SET_STATUS,
    ADUCID_ATTRIBUTE_SET_BASIC,
    ADUCID_ATTRIBUTE_SET_ALL,
    ADUCID_ATTRIBUTE_SET_VALIDITY,
    ADUCID_ATTRIBUTE_SET_LINK,
    ADUCID_ATTRIBUTE_SET_ERROR,
    ADUCID_ATTRIBUTE_SET_PEIG_RETURN_NAME
} AducidAttributeSet_t;

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
} AducidAIMStatus_t;

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
} AducidMethod_t;

typedef enum {
    ADUCID_ALGORITHM_INVALID = 0,
    ADUCID_ALGORITHM_USER_ATTR_SET,
    ADUCID_ALGORITHM_PASSWD,
    ADUCID_ALGORITHM_PASSWD_AIM,
    ADUCID_ALGORITHM_BIN_STRING,
    ADUCID_ALGORITHM_OTP_AIM_1,
    ADUCID_ALGORITHM_X509_SIG,
    ADUCID_ALGORITHM_PEIG_MGMT,
    ADUCID_ALGORITHM_PAYMENT
} AducidAlgorithm_t;

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
} AducidAuthStatus_t;


/* ADUCID enum constants end */

typedef enum {
    ADUCID_PEIG_LOCAL_LINK_PRIMARY_REPLICA,
    ADUCID_PEIG_LOCAL_LINK_SECONDARY_REPLICA,
    ADUCID_PEIG_LOCAL_LINK_CONNECTION_USB,
} AducidPeigLocalLink_t;

    
typedef struct {
    char *authId;
    char *bindingId;
    char *bindingKey;
    AducidAIMStatus_t statusAIM;
    AducidAuthStatus_t statusAuth;
} AducidAIMRequestOperationResponse_t;

typedef struct {
    AducidAIMStatus_t statusAIM;
    AducidAuthStatus_t statusAuth;
    char *statusMessage;
    // FIXME explode personalObject
    AducidAttributeList_t personalObject;
} AducidAIMExecutePersonalObjectResponse_t;

typedef struct {
    AducidAIMStatus_t statusAIM;
    AducidAuthStatus_t statusAuth;
    AducidOperation_t operationName;
    char *userDatabaseIndex;
    char *userId;
    char *validityCount;
    char *validityTime;
    char *expirationCountdownUses;
    char *expirationCountdownTime;
    char *securityProfileName;
    char *authenticationProtocolName;
    char *securityLevel;
    char *ILID;
    char *ilTypeName;
    char *ilAlgorithmName;
    char *ilValidityCount;
    char *ilValidityTime;
    char *personalObjectName;
    char *personalObjectTypeName;
    char *personalObjectAlgorithmName;
    AducidAttributeList_t personalObjectAttributes;
    char *authKey2;
    char *sessionKey;
    char *bindingType;
} AducidAIMGetPSLAttributesResponse_t;

typedef struct {
    char *authId;
    char *authKey;
    char *bindingId;
    char *bindingKey;
    char *AIMName;
    char *R3;
    char *R4;
    AducidAIMGetPSLAttributesResponse_t *PSLCache[ADUCID_ATTRIBUTE_SET_ERROR];
} AducidHandleStruct;

typedef AducidHandleStruct *AducidHandle_t;

/**
  * Aducid operations
  */
ADUCID_PUBLIC_FUNC void aducid_free_aim_request_operation_response(AducidAIMRequestOperationResponse_t *response);
ADUCID_PUBLIC_FUNC void aducid_free_aim_get_psl_attributes_response(AducidAIMGetPSLAttributesResponse_t *response);
ADUCID_PUBLIC_FUNC void aducid_free_aim_execute_personal_object_response(AducidAIMExecutePersonalObjectResponse_t *response);

ADUCID_PUBLIC_FUNC AducidAIMRequestOperationResponse_t *aducid_aim_request_operation(
    const char *R4,
    AducidOperation_t operation,
    const char *AIMName,
    const char *authId,
    const char *bindingKey,
    const char *methodName,
    const AducidAttributeList_t methodParameter,
    const AducidAttributeList_t personalObject,
    const char *AAIM2,
    const char *ilData,
    const char *peigReturnName);
    
ADUCID_PUBLIC_FUNC AducidAIMGetPSLAttributesResponse_t *aducid_aim_get_psl_attributes(
    const char *R4,
    const char *authId,
    const char *bindingId,
    const char *AIMName,
    const char *authKey,
    AducidAttributeSet_t attributeSet);

ADUCID_PUBLIC_FUNC AducidAIMExecutePersonalObjectResponse_t *aducid_aim_execute_personal_object(
    const char *R4,
    const char *authId,
    const char *AIMName,
    const char *authKey,
    AducidMethod_t methodName,
    const char *personalObjectName,
    AducidAlgorithm_t personalObjectAlgorithm,
    AducidAttributeList_t personalObjectData,
    const char *ILID,
    const char *AAIM2,
    const char *ilData);

ADUCID_PUBLIC_FUNC bool aducid_aim_close_session(
    const char *R4,
    const char *authId,
    const char *AIMName,
    const char *authKey);

/*
const char *    aducid_operation_str(AducidOperation operation);
AducidOperation aducid_operation_enum(char *operation);
*/
ADUCID_PUBLIC_FUNC const char *aducid_operation_str(AducidOperation_t operation);
ADUCID_PUBLIC_FUNC AducidOperation_t aducid_operation_enum(const char *operation);

ADUCID_PUBLIC_FUNC const char *       aducid_attribute_set_str(AducidAttributeSet_t set);
ADUCID_PUBLIC_FUNC AducidAttributeSet_t aducid_attribute_set_enum(const char *set);

ADUCID_PUBLIC_FUNC const char *    aducid_aim_status_str(AducidAIMStatus_t status);
ADUCID_PUBLIC_FUNC AducidAIMStatus_t aducid_aim_status_enum(const char *status);

ADUCID_PUBLIC_FUNC const char * aducid_method_str(AducidMethod_t method);
ADUCID_PUBLIC_FUNC AducidMethod_t aducid_method_enum(const char *method);

ADUCID_PUBLIC_FUNC const char *    aducid_algorithm_str(AducidAlgorithm_t alg);
ADUCID_PUBLIC_FUNC AducidAlgorithm_t aducid_algorithm_enum(const char *alg);

ADUCID_PUBLIC_FUNC const char *     aducid_auth_status_str(AducidAuthStatus_t status);
ADUCID_PUBLIC_FUNC AducidAuthStatus_t aducid_auth_status_enum(const char *status);

/* c interface */
ADUCID_PUBLIC_FUNC AducidHandle_t aducid_new(const char *AIM, const char *authId, const char *authKey, const char *bindingId, const char *bindingKey);

ADUCID_PUBLIC_FUNC const char *aducid_open( AducidHandle_t handle, const char *peigReturnName);
ADUCID_PUBLIC_FUNC const char *aducid_init( AducidHandle_t handle, const char *peigReturnName);
ADUCID_PUBLIC_FUNC const char *aducid_reinit( AducidHandle_t handle, const char *peigReturnName);
ADUCID_PUBLIC_FUNC const char *aducid_change( AducidHandle_t handle, const char *peigReturnName);
ADUCID_PUBLIC_FUNC const char *aducid_rechange( AducidHandle_t handle, const char *peigReturnName);
ADUCID_PUBLIC_FUNC const char *aducid_delete( AducidHandle_t handle, const char *peigReturnName);

ADUCID_PUBLIC_FUNC const char *
aducid_exuse( AducidHandle_t handle,
              const char *methodName,
              const AducidAttributeList_t methodParameters,
              const AducidAttributeList_t personalObject,
              const char *peigReturnName );

ADUCID_PUBLIC_FUNC bool aducid_close(AducidHandle_t handle);

ADUCID_PUBLIC_FUNC AducidAIMGetPSLAttributesResponse_t *
aducid_get_psl_attributes( AducidHandle_t handle, AducidAttributeSet_t attributeSet, bool useCache );

ADUCID_PUBLIC_FUNC bool
aducid_wait_for_operation( AducidHandle_t handle );

ADUCID_PUBLIC_FUNC bool
aducid_verify( AducidHandle_t handle );

ADUCID_PUBLIC_FUNC bool
aducid_verify_transaction( AducidHandle_t handle, AducidAttributeList_t *transaction );

ADUCID_PUBLIC_FUNC AducidAttributeList_t *
aducid_get_attributes( AducidHandle_t handle, char *attrSetName );

ADUCID_PUBLIC_FUNC bool
aducid_set_attributes( AducidHandle_t handle, char *attrSetName, AducidAttributeList_t *attrs );

ADUCID_PUBLIC_FUNC const char *
aducid_get_user_database_index( AducidHandle_t handle );

ADUCID_PUBLIC_FUNC void
aducid_clear_psl_cache( AducidHandle_t handle );

ADUCID_PUBLIC_FUNC const char *
aducid_get_authid( AducidHandle_t handle );

ADUCID_PUBLIC_FUNC void
aducid_set_authid( AducidHandle_t handle, const char *authId );

ADUCID_PUBLIC_FUNC const char *
aducid_get_authkey( AducidHandle_t handle );

ADUCID_PUBLIC_FUNC void
aducid_set_authkey( AducidHandle_t handle, const char *authKey );

ADUCID_PUBLIC_FUNC const char *
aducid_get_bindingkey( AducidHandle_t handle );

ADUCID_PUBLIC_FUNC void
aducid_set_bindingkey( AducidHandle_t handle, const char *bindingKey );

ADUCID_PUBLIC_FUNC const char *
aducid_get_bindingid( AducidHandle_t handle );

ADUCID_PUBLIC_FUNC void
aducid_set_bindingid( AducidHandle_t handle, const char *bindingId );

ADUCID_PUBLIC_FUNC const char *
aducid_exuse( AducidHandle_t handle,
              const char *methodName,
              const AducidAttributeList_t methodParameters,
              const AducidAttributeList_t personalObject,
              const char *peigReturnName );

ADUCID_PUBLIC_FUNC const char *
aducid_init_personal_factor( AducidHandle_t handle, const char * peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_change_personal_factor( AducidHandle_t handle, const char * peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_delete_personal_factor( AducidHandle_t handle, const char * peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_verify_personal_factor( AducidHandle_t handle, const char * peigReturnURL );

/*
 *   Room operations
 */

ADUCID_PUBLIC_FUNC const char *
aducid_create_room_by_name( AducidHandle_t handle, const char *roomName, const char * peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_enter_room_by_name( AducidHandle_t handle, const char *roomName, const char * peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_create_room_by_story( AducidHandle_t handle, const char * peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_enter_room_by_story( AducidHandle_t handle, const char * peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_peig_local_link( AducidHandle_t handle, AducidPeigLocalLink_t linkType, const char * peigReturnURL );

/*
 * Payment operations
 */
ADUCID_PUBLIC_FUNC const char *
aducid_init_payment( AducidHandle_t handle, bool usePersonalFactor, const char *peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_confirm_text_transaction(
    AducidHandle_t handle,
    const char *textUTF8,
    bool usePersonalFactor,
    const char *peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_confirm_money_transaction(
    AducidHandle_t handle,
    const char *fromAccount,
    const char *toAccount,
    const char *amount,
    bool usePersonalFactor,
    const char *peigReturnURL );


ADUCID_PUBLIC_FUNC void
aducid_free( AducidHandle_t handle );


/**
 * PEIG
 */

ADUCID_PUBLIC_FUNC bool aducid_peig_invoke( AducidHandle_t handle );
ADUCID_PUBLIC_FUNC const char *aducid_peig_get_authkey( AducidHandle_t handle );
ADUCID_PUBLIC_FUNC char *aducid_get_aimproxy_url( AducidHandle_t handle );
ADUCID_PUBLIC_FUNC char *aducid_get_aducid_url( AducidHandle_t handle );

/**
 * library inicialization
 */
ADUCID_PUBLIC_FUNC int aducid_library_init();
ADUCID_PUBLIC_FUNC int aducid_library_free();

#ifdef __cplusplus
}
#endif

#endif
