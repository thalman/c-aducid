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

#ifndef __ADUCID_H__
#define __ADUCID_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef ADUCID_PUBLIC_FUNC
  #if defined _WIN32 || defined _WIN64
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

#include <stdbool.h>

/* attribute list functions */

/**
 * \defgroup lists Functions for operations with attribute lists
 * @{
 */

/**
 * \brief Handle for aducid list data structure.
 *
 * The aducid_get_attributes and aducid_set_attributes functions work with a generic list of user
 * data, such as name, surname and email. Each attribute has its name and value. Both name and value
 * are char * type. Items are indexed starting from zero.
 */
typedef void *AducidAttributeList_t;

/**
 * \brief Create new empty list.
 * \see aducid_attr_list_free
 * \return Handle for new empty list.
 *
 * This function creates a new empty attribute list and returns its handle. This list and its contents must be
 * cleared by using aducid_attr_list_free.
 */
ADUCID_PUBLIC_FUNC AducidAttributeList_t
aducid_attr_list_new();

/**
 * \brief Counts items in list.
 * \param handle attribute list handle
 * \return int, number of items in list
 *
 \code{.c}
 if( aducid_attr_list_count(handle) ) {
     printf("list is not empty\n");
 }
 \endcode
 */
ADUCID_PUBLIC_FUNC int
aducid_attr_list_count( const AducidAttributeList_t handle );

/**
 * \brief Moves cursor at the beginning of list.
 * \param handle attribute list handle
 *
 \code{.c}
 aducid_attr_list_first(handle);
 name = aducid_attr_list_get_name(handle);
 value = aducid_attr_list_get_name(handle);
 while(name) {
     printf("%s  %s\n", name, value );
     aducid_attr_list_next(handle);
     name = aducid_attr_list_get_name(handle);
     value = aducid_attr_list_get_name(handle);
 }
 \endcode
 */
ADUCID_PUBLIC_FUNC
void aducid_attr_list_first( AducidAttributeList_t handle );

/**
 * \brief Moves cursor to the next item of list.
 * \param handle attribute list handle
 */
ADUCID_PUBLIC_FUNC
void aducid_attr_list_next( AducidAttributeList_t handle );
    
/**
 * \brief Get list item name.
 * \param handle attribute list handle
 * \return name of current item in the list
 * \see aducid_attr_list_first
 */
ADUCID_PUBLIC_FUNC
const char *aducid_attr_list_get_name( const AducidAttributeList_t handle );

/**
 * \brief Get list item value.
 * \param handle attribute list handle
 * \return value of current item in the list
 * \see aducid_attr_list_first
 */
ADUCID_PUBLIC_FUNC
const char *aducid_attr_list_get_value( const AducidAttributeList_t handle );

/**
 * \brief This function returns the name of the Nth item of the list, or NULL when the given index is invalid.
 * \param handle attribute list handle
 * \param index index of requested item
 * \return char *, name or NULL
 */
ADUCID_PUBLIC_FUNC char *
aducid_attr_list_get_item_name( const AducidAttributeList_t handle, int idx );

/**
 * \brief This function returns the value of the Nth item of the list, or NULL when the given index is invalid.
 * \param handle attribute list handle
 * \param index index of requested item
 * \return char *, value or NULL
 *
 \code{.c}
 int a;
 for(a=0; a<aducid_attr_list_count(handle), a++ ) {
     printf("name[%i] is %s\nvalue[%i] is %s\n",
            a,
            aducid_attr_list_get_item_name(handle,a),
            a,
            aducid_attr_list_get_item_value(handle,a)
     );
 }
 \endcode
 */
ADUCID_PUBLIC_FUNC char *
aducid_attr_list_get_item_value( const AducidAttributeList_t handle, int idx );

/**
 * \brief Append new element to the list.
 * \param handle attribute list handle
 * \param name attribute name
 * \param value atribute value
 *
 * This function adds a new attribute to the end of the list. Both its name and value
 * parameters must not be NULL. The function creates a copy of the transferred values
 * in the memory (strdup).
 */
ADUCID_PUBLIC_FUNC void
aducid_attr_list_append( AducidAttributeList_t handle, const char *name, const char *value );

/**
 * \brief Add new element to the beginning of the list.
 * \param handle attribute list handle
 * \param name attribute name
 * \param value atribute value
 * \see aducid_attr_list_append
 *
 * This function has the same properties as aducid_attr_list_append, but adds
 * the new item to the beginning of the list
 */
ADUCID_PUBLIC_FUNC void
aducid_attr_list_prepend( AducidAttributeList_t handle, const char *name, const char *value );

/**
 * \brief Inserts an attribute to a given position in the list.
 * \param handle attribute list handle
 * \param name attribute name
 * \param value atribute value
 * \param index insert position
 * \see aducid_attr_list_append
 *
 * This function inserts an attribute to a given position in the list.
 * When the index points to beyond the list (even if the position is nonsense),
 * the function behaves as aducid_attr_list_append. When the index
 * is smaller than 1, the function behaves as aducid_attr_list_prepend.
 *
 \code{.c}
 AducidAttributeList handle;
 handle = aducid_attr_list_new();
 aducid_attr_list_append(handle, "item 3","good evening");
 aducid_attr_list_prepend(handle, "item 1","good moorning");
 aducid_attr_list_insert(handle, "item 2","good afternoon",1);
 // the list is now correctly sorted
 aducid_attr_list_free(handle);
 \endcode
 *
 * \see aducid_attr_list_append
 * \see aducid_attr_list_prepend
 */
ADUCID_PUBLIC_FUNC void
aducid_attr_list_insert( AducidAttributeList_t handle, const char *name, const char *value, int idx );

/**
 * \brief Returns first element with given name
 * \param handle attribute list handle
 * \param name attribute name
 * \return attribute value
 *
 * This function finds the given attribute and returns a pointer with its value. The search is not case
 * sensitive. A list may contain several attributes of the same name. This is necessary for operations with
 * multi-value attributes in LDAP, such as email addresses. A user may have several email addresses. In
 * such cases, attribute lists contain several "mail" items with different values.
 *
 * The function also sets the internal pointer and the next aducid_attr_list_get_next_by_name call
 * points to the next value.
 *
 * When the list does not contain an attribute of the given name, the function returns NULL
 */
ADUCID_PUBLIC_FUNC char *
aducid_attr_list_get_first_by_name( const AducidAttributeList_t handle, const char *name );

/**
 * \brief The function searches for the next attribute of the given name.
 * \param handle attribute list handle
 * \param name attribute name
 * \return found value or NULL
 *
 * \code{.c}
 // prints all mails in the list
 char *mail;
 mail = aducid_attr_list_get_first_by_name(handle, "mail");
 while(mail) {
     printf("mail: %s\n", mail);
     mail = aducid_attr_list_get_next_by_name(handle, "mail");
 }
 \endcode
 */
ADUCID_PUBLIC_FUNC char *
aducid_attr_list_get_next_by_name( const AducidAttributeList_t handle, const char *name );

/**
 * \brief The function counts the attributes of the given name and it is not case sensitive.
 * \param handle attribute list handle
 * \param name attribute name
 * \return number of attributes with given name
 *
 * \code{.c}
 AducidAttributeList handle;
 int cnt;
 handle = aducid_attr_list_new();
 aducid_attr_list_append(handle, "item","good evening");
 aducid_attr_list_append(handle, "ITEM","good moorning");
 cnt = aducid_attr_list_get_count_by_name(handle, "iTEm");
 // cnt == 2
 aducid_attr_list_free(handle);
 \endcode
 */
ADUCID_PUBLIC_FUNC int
aducid_attr_list_get_count_by_name( const AducidAttributeList_t handle, const char *name );

/**
 * \brief The function deletes the item at position idx from list.
 * \param handle attribute list handle
 * \param idx index of deleted item
 * \return bool deleted or not
 *
 * This function deletes the item at position idx from the list of attributes. When the operation is successful,
 * the function returns true. When the function returns false, idx points to outside of the list, or handle is
 * NULL.
 */
ADUCID_PUBLIC_FUNC bool
aducid_attr_list_delete( AducidAttributeList_t handle, int idx );

/**
 * \brief The function deletes the all items with given name from list.
 * \param handle attribute list handle
 * \param name attribute name
 * \return true if at least one item deleted
 *
 * This function deletes all attributes of the given name from the list.
 * The search is not case sensitive.
 */
ADUCID_PUBLIC_FUNC bool
aducid_attr_list_delete_by_name( AducidAttributeList_t handle, const char *name );

/**
 * \brief This function clears a list of attributes from the memory.
 * \param handle attribute list handle
 */
ADUCID_PUBLIC_FUNC void
aducid_attr_list_free( AducidAttributeList_t handle );

/**@}*/

/**
 * \defgroup enums ADUCID enums
 * @{
 */

/* Warning, content between ADUCID enum constants begin and end is generated. Do not modify */
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

/**@}*/

    
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
 * \defgroup lowlevel Low-level ADUCID functions
 * @{
 */

/**
 * \brief Free memory structure returned by aducid_aim_request_operation.
 * \param response response to free
 * \see aducid_aim_request_operation
 *
 * Function clears memory structures obtained with aducid_aim_request_operation.
 * if response is NULL, function does nothing.
 */
ADUCID_PUBLIC_FUNC void
aducid_free_aim_request_operation_response(AducidAIMRequestOperationResponse_t *response);

/**
 * \brief Free memory structure returned by aducid_aim_get_psl_attributes.
 * \param response response to free
 * \see aducid_aim_get_psl_attributes
 *
 * Functions clears memory structures obtained with aducid_aim_get_psl_attributes.
 * if response is NULL, function does nothing.
 */
ADUCID_PUBLIC_FUNC void
aducid_free_aim_get_psl_attributes_response(AducidAIMGetPSLAttributesResponse_t *response);

/**
 * \brief Free memory structure returned by aducid_aim_execute_personal_object.
 * \param response response to free
 * \see aducid_aim_execute_personal_object
 *
 * Functions clears memory structures obtained with aducid_aim_execute_personal_object.
 * if response is NULL, function does nothing.
 */
ADUCID_PUBLIC_FUNC void
aducid_free_aim_execute_personal_object_response(AducidAIMExecutePersonalObjectResponse_t *response);

/**
 * \brief This function initiates an operation on the AIM server.
 * \param R4 address of the SOAP R4 AIM interface (for example, "http://aim.example.com/AIM/services/R4")
 * \param operation requested operation
 * \param authId ADUCID session identifier (when the value is NULL, it is assigned to AIM)
 * \param methodName name of requested method
 * \param methodParametr parameters for methodName method.
 * \param personalObject ADUCID personal object
 * \param AAIM2 secondary AIM address for identity link
 * \param ilData data for identity link
 * \param peigReturnURL URL for application return address
 * \return pointer AducidAIMRequestOperationResponse data structure.
 *
 * The returned response must be cleared by using aducid_free_aim_request_operation_response().
 */
ADUCID_PUBLIC_FUNC AducidAIMRequestOperationResponse_t *
aducid_aim_request_operation(
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
    const char *peigReturnURL);
    
/**
 * \brief Returns ADUCID PSL set of attributes
 * \param R4 address of the SOAP R4 AIM interface (for example, "http://aim.example.com/AIM/services/R4")
 * \param authId ADUCID session identifier.
 * \param bindingId ADUCID binding identifier.
 * \param AIMName name of virtual AIM
 * \param authKey ADUCID session key.
 * \param attributeSet requested set of attributes.
 * \return pointer AducidAIMGetPSLAttributesResponse_t data structure.
 *
 * The function returns a pointer to the AducidAIMGetPSLAttributesResponse, or NULL when
 * unsuccessful.
 *
 * The return structure has various items completed, depending on the queried attributeSet. Its typical
 * use is a query for a set of attributes ADUCID_ATTRIBUTE_SET_STATUS. This set returns the authentication
 * process status (initiated, in progress, completed, etc.) and does not need authKey (authKey = NULL).
 *
 * After authentication is completed, other sets may be queried. For normal applications, the
 * ADUCID_ATTRIBUTE_SET_ALL set may be used. It contains all necessary information, such as
 * authentication status and user database index.
 *
 * The structure must be cleared by using aducid_free_aim_get_psl_attributes_response().
 */
ADUCID_PUBLIC_FUNC AducidAIMGetPSLAttributesResponse_t *
aducid_aim_get_psl_attributes(
    const char *R4,
    const char *authId,
    const char *bindingId,
    const char *AIMName,
    const char *authKey,
    AducidAttributeSet_t attributeSet);

/**
 * \brief Function requests aim for operation with personal object
 * \param R4 address of the SOAP R4 AIM interface (e.g. "http://aim.example.com/AIM/services/R4")
 * \param authId ADUCID session identifier
 * \param AIMName name of virual AIM
 * \param authKey ADUCID authentication key
 * \param methodName name of the method called (for example, ADUCID_METHOD_WRITE)
 * \param personalObjectName object name (for example, name of set being written)
 * \param personalObjectAlgorithm algorithm used (for example, ADUCID_ALGORITHM_USER_ATTR_SET)
 * \param personalObjectData list of attributes and their values (for example, name of set being written)
 * \param ILID information for identity link
 * \param AAIM2 secondary AIM for identity link
 * \param ilData data for identity link
 * \return pointer to AducidAIMExecutePersonalObjectResponse, or NULL when unsuccessful.
 *
 * The returned structure must be cleared by using aducid_free_aim_execute_personal_object_response().
 */
ADUCID_PUBLIC_FUNC AducidAIMExecutePersonalObjectResponse_t *
aducid_aim_execute_personal_object(
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

/**
 * \brief function closes ADUCID session on AIM
 * \param R4 address of the SOAP R4 AIM interface (e.g. "http://aim.example.com/AIM/services/R4")
 * \param authId ADUCID session identifier
 * \param AIMName name of virual AIM
 * \param authKey ADUCID authentication key
 *
 * This function closes the authentication session on the AIM server. For security reasons, this function
 * should be called when the authentication session is not needed. If the session is not closed explicitly, it
 * closes itself after a time limit elapses (the limit is configured on the AIM server).
 *
 * The function returns true when the call is successful.
 */
ADUCID_PUBLIC_FUNC bool
aducid_aim_close_session(
    const char *R4,
    const char *authId,
    const char *AIMName,
    const char *authKey);

/**@}*/

/**
 * \defgroup conversions Functions enabling conversion of enumeration types to strings and vice versa
 * @{
 */

/**
 * \brief Function converts AducidOperation_t into string.
 * \param operation operation enum
 * \return const char * operation name
 *
 * When invalid value is converted to text (for example (AducidOperation_t)-1), the function returns NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_operation_str( AducidOperation_t operation );

/**
 * \brief Function converts string representing AducidOperation into enum.
 * \param operation name
 * \return AducidOperation_t operation
 *
 * When invalid name is provided (for example "some random text"), the function returns 0 (ADUCID_OPERATION_INVALID).
 */
ADUCID_PUBLIC_FUNC AducidOperation_t
aducid_operation_enum( const char *operation );

/**
 * \brief Function converts AducidAttributeList_t into string.
 * \param set AducidAttributeSet
 * \return const char * set name
 *
 * When invalid value is converted to text (for example (AducidAttributeSet_t)-1), the function returns NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_attribute_set_str(AducidAttributeSet_t set);

/**
 * \brief Function converts string representing AducidAttributeSet into enum.
 * \param name set name
 * \return AducidAttributeSet_t set
 *
 * When invalid name is provided (for example "some random text"), the function returns 0 (ADUCID_ATTRIBUTE_SET_INVALID).
 */
ADUCID_PUBLIC_FUNC AducidAttributeSet_t
aducid_attribute_set_enum(const char *set);

/**
 * \brief Function converts AducidAIMStatus_t into string.
 * \param status ADUCID AIM status
 * \return const char * status name
 *
 * When invalid value is converted to text (for example (AducidAIMStatus_t)-1), the function returns NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_aim_status_str(AducidAIMStatus_t status);

/**
 * \brief Function converts string representing AducidAttributeSet into enum.
 * \param status status name
 * \return AducidAttributeSet_t set
 *
 * When invalid name is provided (for example "some random text"), the function returns 0 (ADUCID_AIM_STATUS_INVALID).
 */
ADUCID_PUBLIC_FUNC AducidAIMStatus_t
aducid_aim_status_enum(const char *status);

/**
 * \brief Function converts AducidMethod_t into string.
 * \param method ADUCID method enum 
 * \return const char * method name
 *
 * When invalid value is converted to text (for example (AducidMethod_t)-1), the function returns NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_method_str(AducidMethod_t method);

/**
 * \brief Function converts string representing AducidMethod into enum.
 * \param method method name
 * \return AducidMethod_t method enum
 *
 * When invalid name is provided (for example "some random text"), the function returns 0 (ADUCID_METHOD_INVALID).
 */
ADUCID_PUBLIC_FUNC AducidMethod_t
aducid_method_enum(const char *method);

/**
 * \brief Function converts AducidAlgorithm_t into string.
 * \param alg ADUCID algorithm enum
 * \return const char * algorithm name
 *
 * When invalid value is converted to text (for example (AducidAlgorithm_t)-1), the function returns NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_algorithm_str(AducidAlgorithm_t alg);

/**
 * \brief Function converts string representing AducidAlgorithm into enum.
 * \param alg algorithm name
 * \return AducidAlgorithm_t algorithm
 *
 * When invalid name is provided (for example "some random text"), the function returns 0 (ADUCID_ALGORITHM_INVALID).
 */
ADUCID_PUBLIC_FUNC AducidAlgorithm_t
aducid_algorithm_enum(const char *alg);

/**
 * \brief Function converts AducidAuthStatus_t into string.
 * \param status ADUCID auth status enum
 * \return const char * status name
 *
 * When invalid value is converted to text (for example (AducidAuthStatus_t)-1), the function returns NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_auth_status_str(AducidAuthStatus_t status);

/**
 * \brief Function converts string representing AducidAuthStatus into enum.
 * \param status status name
 * \return AducidAuthStatus_t status
 *
 * When invalid name is provided (for example "some random text"), the function returns 0 (ADUCID_AUTHSTATUS_INVALID).
 */
ADUCID_PUBLIC_FUNC AducidAuthStatus_t
aducid_auth_status_enum(const char *status);

/**@}*/

/**
 * \defgroup aducid ADUCID authentication functions
 * @{
 */

/**
 * \brief Function creates new ADUCID handle
 * \param AIM AIM server address/URL
 * \param authId ADUCID session id
 * \param authKey ADUCID session key
 * \param bindingId ADUCID binding id
 * \param bindingKey ADUCID binding key
 * \see aducid_free
 *
 * The first input parameter is the AIM interface address. It may be provided as DNS name, IP address or
 * URL. Examples of valid parameters:
 *
 *     aim.example.com
 *     1.2.3.4
 *     aim.example.com:80
 *     http://aim.example.com
 *     https://aim.example.com:4443/
 *     http://1.2.3.4
 *
 * Additional parameters include authId, authKey, bindingId and bindingKey. The created object saves
 * these parameters and may be used for direct AIM server queries. For unknown parameters, use NULL.
 * When the authId value is specified as NULL, all other parameters are ignored!
 *
 * The authId parameter is the ADUCID operation identifier. The authKey parameter is the secret created
 * during some authentication scenarios.
 *
 * The other two parameters are bindingId and bindingKey. In ADUCID authentication terminology,
 * binding is a method of transferring authentication information between an application communication
 * channel (for example, browser or web server) and an ADUCID communication channel (for example,
 * PEIG or AIM). From the SDK viewpoint, binding is represented by two parameters: bindingID and
 * bindingKey.
 *
 * These parameters are created during different types of ADUCID use, in different phases of authentication
 * (depending on the scenario used, PEIG on PC, PEIG on phone; also depending on AIM settings).
 *
 * For application programmers, the important thing to remember is that as soon as one of these parameters
 * is created, its value must be remembered in the application and the parameter must be used in
 * subsequent calls (binding parameters are used in calls such as getResult or invokePeig).
 *
 * The function creates an object in the ADUCID memory and initiates necessary data structures.
 *
 * The function returns the handle (pointer to a data structure), or NULL when unsuccessful (insufficient
 * memory).
 *
 * Use aducid_free() to terminate and free the memory.
 *
 * Example of use:
 *     #include <aducid.h>;
 *     int main(int argc,char *argv[]) {
 *         AducidHandle handle;
 *         handle = aducid_new("aim.example.com",NULL,NULL,NULL,NULL);
 *         // use aducid here
 *         aducid_free(handle);
 *     }
 */
ADUCID_PUBLIC_FUNC AducidHandle_t
aducid_new( const char *AIM, const char *authId, const char *authKey, const char *bindingId, const char *bindingKey );

/**
 * \brief Starts open operation
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 *
 * This function initiates the open operation on the AIM server. The open call is used to use an identity for
 * authentication. The result is the authId identifier. The authId value is saved in the internal structure and
 * may be referenced later by using aducid_get_authid.
 *
 * The peigReturnURL parameter is used in web application development. This parameter contains the
 * URL to which the browser is to be redirected after the operation is completed.
 *
 * The function returns a pointer to authId, or, when unsuccessful, NULL (for example, when the AIM
 * server is unavailable).
 *
 * Example:
 * \code{.c}
 #include <aducid.h>;
 int main(int argc,char *argv[]) {
     AducidHandle handle;
     handle = aducid_new("aim.example.com",NULL,NULL,NULL,NULL);
     if( aducid_open(handle, NULL) ) {
         // operation has been started
     }
     aducid_free(handle);
 }
 \endcode
 */
ADUCID_PUBLIC_FUNC const char *
aducid_open( AducidHandle_t handle, const char *peigReturnURL );

/**
 * \brief Starts init operation
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 *
 * This function initiates the init operation on the AIM server. The init operation is used to create an
 * identity. After authId is handed over at PEIG, PEIG starts to communicate with the AIM server and after
 * the user confirms, an identity is created (both at AIM and PEIG).
 *
 * The function returns a pointer to authId, or, when unsuccessful, NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_init( AducidHandle_t handle, const char *peigReturnURL );


/**
 * \brief Starts reinit operation
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 *
 * This function initiates the reinit operation on the AIM server. The reinit operation is used to renew an
 * identity and recover from an error condition when an identity exists in PEIG, but not on the AIM server (for
 * example, after deletion by the AIM server administrator).
 *
 * The function returns a pointer to authId, or, when unsuccessful, NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_reinit( AducidHandle_t handle, const char *peigReturnURL );

/**
 * \brief Starts change operation
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 *
 * This function initiates the change operation on the AIM server. The change operation is used to change
 * an identity (create new pseudo random identifiers) during its validity. If the identity's validity has expired,
 * use rechange. With standard AIM settings, identities are changed automatically before they expire.
 *
 * The function returns a pointer to authId, or, when unsuccessful, NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_change( AducidHandle_t handle, const char *peigReturnURL );

/**
 * \brief Starts change operation
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 *
 * This function initiates the rechange operation on the AIM server. The rechange operation is used to
 * change an identity (create new pseudo random identifiers) after its validity has expired. An identity's
 * validity depends both on the number of its uses and on its validity period. The rechange operation may
 * be necessary when a user has not logged in to a given service for a long time.
 *
 * The function returns a pointer to authId, or, when unsuccessful, NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_rechange( AducidHandle_t handle, const char *peigReturnURL );

/**
 * \brief Starts delete operation
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 *
 * This function initiates the delete operation on the AIM server. The delete operation is used to remove
 * an identity both from AIM and PEIG.
 *
 * The function returns a pointer to authId, or, when unsuccessful, NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_delete( AducidHandle_t handle, const char *peigReturnURL );

/**
 * \brief Starts exuse operation
 * \param handle aducid handle
 * \param methodName requested method
 * \param methodParametr parameters for methodName method.
 * \param personalObject ADUCID personal object
 * \param peigReturnURL URL for application return address
 *
 * This function initiates the exuse operation on the AIM server. This function
 * allows use advanced ADUCID features like transaction. Because direct usage of
 * this method is complicated, SDK offers other high-level functions, which encapsulate
 * this one.
 *
 * The function returns a pointer to authId, or, when unsuccessful, NULL.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_exuse(
    AducidHandle_t handle,
    const char *methodName,
    const AducidAttributeList_t methodParameters,
    const AducidAttributeList_t personalObject,
    const char *peigReturnURL );

/**
 * \brief Function closes ADUCID session on AIM
 * \param handle aducid handle
 * \return true if closed successfuly
 *
 * This function closes the ADUCID session on the AIM server. This function should be called when the
 * application obtains all necessary information (authentication result, user information) and will not need
 * ADUCID any more. When the function is not called, the session is automatically closed on the server after
 * a time limit expires. The time limit depends on the AIM server configuration.
 *
 * The function returns true when the call is successful.
 */
ADUCID_PUBLIC_FUNC bool
aducid_close( AducidHandle_t handle );

/**
 * \brief Get PSL attributes
 * \param handle aducid handle
 * \param attributeSet PSL attribute set
 * \param useCache allows reading requested data from cache
 * \return PSL response response
 *
 * ADUCID offers several attributes directly related to ADUCID identification of the user and their PEIG. This
 * is called Permanent Secure Link (PSL), in the ADUCID terminology. PSL contains selected information
 * about identities and the status of the authentication process.
 *
 * The most important PSL sets are ADUCID_ATTRIBUTE_SET_ALL and ADUCID_ATTRIBUTE_SET_ERROR.
 *
 * Set ADUCID_ATTRIBUTE_SET_ERROR allows the developer detect what went wrong when autentication failed.
 *
 * Set ADUCID_ATTRIBUTE_SET_ALL provides all PSL information when authentication was successful.
 *
 * Function returns pointer into internal structure. This is maintained in PSL cache and is disposed automatically.
 * Do not free this manually!
 */
ADUCID_PUBLIC_FUNC AducidAIMGetPSLAttributesResponse_t *
aducid_get_psl_attributes( AducidHandle_t handle, AducidAttributeSet_t attributeSet, bool useCache );

/**
 * \brief Waits until pending operation is finished
 * \param handle aducid handle
 * \return true if opertion is finished
 *
 * This function waits for an operation to close. The function returns true when the operation is closed;
 * however, that does not necessarily mean that the operation was successful. When the function returns
 * false, it indicates that the operation's condition could not be determined. That may happen during a
 * network failure, for instance.
 *
 * Internally, the function repeatedly calls aducid_get_psl_attributes to determine the authentication
 * status.
 *
 *     aducid_get_psl_attributes( handle, ADUCID_ATTRIBUTE_SET_STATUS, false );
 *
 * This call is repeated as long as the return value statusAIM is ADUCID_AIM_STATUS_START or
 * ADUCID_AIM_STATUS_WORKING.
 */
ADUCID_PUBLIC_FUNC bool
aducid_wait_for_operation( AducidHandle_t handle );

/**
 * \brief Verify current ADUCID operation.
 * \param handle aducid handle
 * \return overall status of the operation.
 *
 * This function determines whether the operation was successful and the user was authenticated. At the
 * time of calling this function, the other parameters should be known (depend of the binding type).
 *
 * \code{.c}
 h = aducid_new( "aim.example.com", authId, authKey, bindingId, bindingKey );
 if( aducid_verify(h) ) {
     // ok
 } else {
     // failed
 }
 aducid_free(h);
 \endcode
 */
ADUCID_PUBLIC_FUNC bool
aducid_verify( AducidHandle_t handle );

/**
 * \brief Verify current ADUCID operation including personal factor usage.
 * \param[in] handle, aducid handle
 * \param[out] transaction, list for storing transaction information
 * \return bool overall status of the operation.
 *
 * This function determines whether the operation was successful and the user was authenticated,
 * usage of personal factor included.
 *
 * If the transaction parameter is given, all relevant transaction information are stored in that list (Like
 * usage of personal factor or digital signature).
 *
 * \code{.c}
 h = aducid_new( "aim.example.com", authId, authKey, bindingId, bindingKey );
 AducidAttributeList_t transaction = aducid_attr_list_new();
 if( aducid_verify_transaction( h, &transaction ) ) {
     printf("ok: %s\n", aducid_attr_list_get_first_by_name( transaction, "PaymentSignature" ) );
 } else {
     printf("failed: %s\n", aducid_attr_list_get_first_by_name( transaction, "Return_Status" ) );
 }
 aducid_attr_list_free(transaction);
 aducid_free(h);
 \endcode
 */
ADUCID_PUBLIC_FUNC bool
aducid_verify_transaction( AducidHandle_t handle, AducidAttributeList_t *transaction );

/**
 * \brief Does an operation with personal object.
 *
 * After successful authentication You can use ADUCID handle for manipulating
 * objects stored in AIM. This concept is generic and for particular operation
 * there are other high-level functions, simplifying usage of this concept.
 *
 * For example we can have some user attributes stored in AIM and ve can read them.
 * - method is ADUCID_METHOD_READ,
 * - personalObjectName is in this case name of attribute set we want read
 *   for example "default" or "UIM"
 * - algorithm is ADUCID_ALGORITHM_USER_ATTR_SET - manipulating with user attribute set.
 * - the rest of attributes is NULL in this case.
 */
ADUCID_PUBLIC_FUNC AducidAttributeList_t
aducid_execute_personal_object(
    AducidHandle_t handle,
    AducidMethod_t method,
    const char *personalObjectName,
    AducidAlgorithm_t personalObjectAlgorithm,
    const AducidAttributeList_t personalObjectData,
    const char *ILID,
    const char *AAIM2,
    const char *ilData);

/**
 * \brief Read user attributes from AIM.
 * \param handle aducid handle
 * \param attrSetName attribute set name
 * \return list of attributes
 * \see aducid_execute_personal_object
 *
 * Method reads set of user attributes in attrSetName. Free the result with aducid_attr_list_free().
 *
 * Example:
 * \code{.c}
 h = aducid_new( "aim.example.com", authId, authKey, bindingId, bindingKey );
 if( aducid_verify( h ) ) {
     AducidAttributeList_t list = aducid_epo_read_user_attr_set( h, "default" );
     const char *mail = aducid_attr_list_get_first_by_name( list, "mail" );
     printf( "user mail is %s\n", ( mail ? mail : "not set" ) );
     aducid_attr_list_free(list);
 }
 aducid_free( h );
 \endcode
 */
ADUCID_PUBLIC_FUNC AducidAttributeList_t
aducid_epo_read_user_attr_set( AducidHandle_t handle, const char *attrSetName );

/**
 * \brief Read user attributes from AIM.
 * \param handle aducid handle
 * \param attrSetName attribute set name
 * \param attrs attributes to store
 * \return true
 * \see aducid_execute_personal_object
 * \see aducid_epo_read_user_attr_set
 *
 * Method writes set of user attributes in attrSetName
 */
ADUCID_PUBLIC_FUNC bool
aducid_epo_write_user_attr_set( AducidHandle_t handle, const char *attrSetName, const AducidAttributeList_t attrs );

/**
 * \brief Method returns userDatabaseIndex.
 * \param handle aducid handle
 * \return user identifier
 */
ADUCID_PUBLIC_FUNC const char *
aducid_get_user_database_index( AducidHandle_t handle );

/**
 * \brief Clear PSL cache
 * \param handle aducid handle
 *
 * Function clears internal cache of PSL responses.
 */
ADUCID_PUBLIC_FUNC void
aducid_clear_psl_cache( AducidHandle_t handle );

/**
 * \brief Returns current authId.
 * \param handle aducid handle
 *
 * Function returns authId from ADUCID handle.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_get_authid( AducidHandle_t handle );

/**
 * \brief Sets authId.
 * \param handle aducid handle
 * \param authId authId value
 *
 * Function sets authId in ADUCID handle.
 */
ADUCID_PUBLIC_FUNC void
aducid_set_authid( AducidHandle_t handle, const char *authId );

/**
 * \brief Returns current authKey.
 * \param handle aducid handle
 *
 * Function returns authKey from ADUCID handle.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_get_authkey( AducidHandle_t handle );

/**
 * \brief Sets authKey.
 * \param handle aducid handle
 * \param authKey authKey value
 *
 * Function sets authKey in ADUCID handle.
 */
ADUCID_PUBLIC_FUNC void
aducid_set_authkey( AducidHandle_t handle, const char *authKey );

/**
 * \brief Returns current bindingKey.
 * \param handle aducid handle
 *
 * Function returns bindingKey from ADUCID handle.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_get_bindingkey( AducidHandle_t handle );

/**
 * \brief Sets bindingKey.
 * \param handle aducid handle
 * \param bindingKey new bindingKey value
 *
 * Function sets bindingKey in ADUCID handle.
 */
ADUCID_PUBLIC_FUNC void
aducid_set_bindingkey( AducidHandle_t handle, const char *bindingKey );

/**
 * \brief Returns current bindingId.
 * \param handle aducid handle
 *
 * Function returns bindingId from ADUCID handle.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_get_bindingid( AducidHandle_t handle );

/**
 * \brief Sets bindingId.
 * \param handle aducid handle
 * \param bindingId new bindingId value
 *
 * Function sets bindingId in ADUCID handle.
 */
ADUCID_PUBLIC_FUNC void
aducid_set_bindingid( AducidHandle_t handle, const char *bindingId );

/**
 * \brief Starts exuse operation for personal factor initialization.
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 */
ADUCID_PUBLIC_FUNC const char *
aducid_init_personal_factor( AducidHandle_t handle, const char * peigReturnURL );

/**
 * \brief Starts exuse operation for personal factor change.
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 */
ADUCID_PUBLIC_FUNC const char *
aducid_change_personal_factor( AducidHandle_t handle, const char * peigReturnURL );

/**
 * \brief Starts exuse operation for personal factor deleting.
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 */
ADUCID_PUBLIC_FUNC const char *
aducid_delete_personal_factor( AducidHandle_t handle, const char * peigReturnURL );

/**
 * \brief Starts exuse operation for personal factor verification.
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 */
ADUCID_PUBLIC_FUNC const char *
aducid_verify_personal_factor( AducidHandle_t handle, const char * peigReturnURL );

/**
 * \brief Starts exuse operation for creating room.
 * \param handle aducid handle
 * \param roomName room name
 * \param peigReturnURL URL for application return address
 *
 * Room opertions is way, how to pair two PEIGs together,
 * that they belong to the same person. After creating room
 * with one PEIG, You simply enter into that room with the
 * other one.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_create_room_by_name( AducidHandle_t handle, const char *roomName, const char * peigReturnURL );

/**
 * \brief Starts exuse operation for entering room.
 * \param handle aducid handle
 * \param roomName room name
 * \param peigReturnURL URL for application return address
 * \see aducid_create_room_by_name
 */
ADUCID_PUBLIC_FUNC const char *
aducid_enter_room_by_name( AducidHandle_t handle, const char *roomName, const char * peigReturnURL );

/**
 * \brief Starts exuse operation for creating room.
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 * \see aducid_create_room_by_name
 *
 * Instead specifying room name, user creates the room as a sequence of pictograms.
 */
ADUCID_PUBLIC_FUNC const char *
aducid_create_room_by_story( AducidHandle_t handle, const char * peigReturnURL );

/**
 * \brief Starts exuse operation for entering room.
 * \param handle aducid handle
 * \param peigReturnURL URL for application return address
 * \see aducid_create_room_by_name
 * \see aducid_create_room_by_story
 */
ADUCID_PUBLIC_FUNC const char *
aducid_enter_room_by_story( AducidHandle_t handle, const char * peigReturnURL );

ADUCID_PUBLIC_FUNC const char *
aducid_peig_local_link( AducidHandle_t handle, AducidPeigLocalLink_t linkType, const char * peigReturnURL );

/**
 * \brief Starts exuse operation for payment initialization.
 * \param handle aducid handle
 * \param usePersonalFactor use personal factor for confirmation
 * \param peigReturnURL URL for application return address
 */
ADUCID_PUBLIC_FUNC const char *
aducid_init_payment( AducidHandle_t handle, bool usePersonalFactor, const char *peigReturnURL );

/**
 * \brief Starts the text transaction.
 * \param handle aducid handle
 * \param textUTF8 text in UTF8 for confirmation
 * \param usePersonalFactor use personal factor for confirmation
 * \param peigReturnURL URL for application return address
 * \see aducid_verify_transaction
 */
ADUCID_PUBLIC_FUNC const char *
aducid_confirm_text_transaction(
    AducidHandle_t handle,
    const char *textUTF8,
    bool usePersonalFactor,
    const char *peigReturnURL );

/**
 * \brief Starts the money transfer transaction.
 * \param handle aducid handle
 * \param fromAccount transfer money from this account 
 * \param toAccount transfer money to this account 
 * \param amount transfer this amount
 * \param usePersonalFactor use personal factor for confirmation
 * \param peigReturnURL URL for application return address
 * \see aducid_verify_transaction
 */
ADUCID_PUBLIC_FUNC const char *
aducid_confirm_money_transaction(
    AducidHandle_t handle,
    const char *fromAccount,
    const char *toAccount,
    const char *amount,
    bool usePersonalFactor,
    const char *peigReturnURL );


/**
 * \brief This function frees the allocated memory and finishes work with the ADUCID object.
 * \see aducid_new
 */
ADUCID_PUBLIC_FUNC void
aducid_free( AducidHandle_t handle );

/**@}*/



/**
 * \defgroup peig operation with local PEIG
 * @{
 */

/**
 * \brief This function starts the local PEIG activity.
 *
 * This function may be used when creating a thick client in a client-server architecture. Its use with web
 * applications is not beneficial. The function communicates with a PEIG-proxy through a redirect adapter
 * (http connection to localhost).
 *
 * Calling the function transfers parameters for initialisation of the corresponding ADUCID operation to the
 * PEIG/PEIG-proxy.
 *
 * The function returns true when the information transfer is successful.
 *
 * \code{.c}
 AducidHandle h;
 h = aducid_new("aim.example.com",authId,NULL,bindingId,bindingKey);
 aducid_peig_invoke(h);
 aducid_free(h);
 \endcode
 */
ADUCID_PUBLIC_FUNC bool
aducid_peig_invoke( AducidHandle_t handle );

/**
 * \brief Obtain authKey from local PEIG (PEIG proxy).
 *
 * This function is also intended for use with a thick client and is supplementary to aducid_peig_invoke. It
 * is used to obtain the authKey—the resulting secret that the client may use to authenticate themselves.
 *
 * \code{.c}
 AducidHandle handle;
 char *URL;
 // we received authId, bindingId, bindingKey from server
 handle = aducid_new( TESTINGAIM, authId, NULL, bindingId, bindingKey );
 // let the peig know
 if( aducid_peig_invoke(handle) ) {
     // peig started (or maybe QR code has been displayed)
     if( aducid_wait_for_operation(handle) ) {
         // operation finished
         aducid_peig_get_authkey(handle);
         if( aducid_verify(handle) ) {
             // user authenicated
             printf("ok\n");
         } else {
             printf("verification failed\n");
         }
     } else {
         printf("wait failed (network issue?)\n");
     }
 }
 if( ! aducid_close(handle) ) {
     printf("close ADUCID failed\n");
 };
 aducid_free(handle);
 \endcode
 */
ADUCID_PUBLIC_FUNC const char *
aducid_peig_get_authkey( AducidHandle_t handle );

/**
 * \brief Returns URL for redirecting into AIMProxy.
 * \param handle aducid handle
 *
 * This function generates a URL which may be used to redirect the user to the AIM-proxy. The resulting
 * string must be cleared by using free().
 *
 * Example of URLs generated in this way:
 *     http://aim.example.com/AIM-proxy/process?authId=w3P31ufKiug%3D&bindingId=5xW6xo%2F25jw%3D&bindingKey=nOjglEfyewc%3D
 */
ADUCID_PUBLIC_FUNC char *
aducid_get_aimproxy_url( AducidHandle_t handle );

/**
 * \brief Returns URL for URI schema aducid
 * \param handle aducid handle
 *
 * This function generates a URL for an ADUCID URI schema. This URL may be used to generate a QR code
 * for use in mobile PEIG authentication. The resulting string must be cleared by using free().
 *
 * Example of URLs generated in this way:
 *     aducid://callback?authId=w3P31ufKiug%3D&r3Url=http%3A%2F%2Faim.example.com%2FAIM%2Fservices%2FR3& \
 *     bindingId=5xW6xo%2F25jw%3D&bindingKey=nOjglEfyewc%3D
 */
ADUCID_PUBLIC_FUNC char *
aducid_get_aducid_url( AducidHandle_t handle );

/**
 * \defgroup library aducid library initialization
 * @{
 */

/**
 * \brief Initialize aducid library.
 *
 * The library contains the aducid_library_init() function, which initialises the libraries used (on Linux
 * cURL) and the aducid_library_free() which clears them. The aducid_library_init() function should be
 * called immediately after the program launches. If the function is not called, the library may not function
 * correctly in multi-thread applications.
 *
 * The function returns 0 when the call is successful and an error code when it is not (on Linux this is the
 * cURL initialisation error code).
 */
ADUCID_PUBLIC_FUNC int aducid_library_init();

/**
 * \brief Deinitialize aducid library.
 * \see aducid_library_init
 */
ADUCID_PUBLIC_FUNC int aducid_library_free();

/**@}*/


#ifdef __cplusplus
}
#endif

#endif
