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
#include "utils.h"

ADUCID_PUBLIC_FUNC const char *
aducid_exuse(AducidHandle_t handle,
             const char *methodName,
             const AducidAttributeList_t methodParameters,
             const AducidAttributeList_t personalObject,
             const char *peigReturnName)
{
    return aducid_request_operation(
        handle,
        ADUCID_OPERATION_EXUSE,
        methodName,
        methodParameters,
        personalObject,
        NULL,
        NULL,
        peigReturnName);
}

/* personal factor operations */

const char *
personal_factor_management_operation(AducidHandle_t handle,
                                  const char *operation,
                                  const char *peigReturnURL)
{
    const char *result;
    AducidAttributeList_t params, personalObject;

    params = aducid_attr_list_new();
    aducid_attr_list_append( params, "UsePersonalFactor", "1" );
    personalObject = aducid_attr_list_new();
    //aducid_attr_list_append( personalObject, "personalObjectName", "" );
    aducid_attr_list_append( personalObject, "personalObjectTypeName", "peigMgmt" );
    aducid_attr_list_append( personalObject, "personalObjectAlgorithmName", aducid_algorithm_str(ADUCID_ALGORITHM_PEIG_MGMT) );
    result = aducid_exuse(
        handle,
        operation,
        params,
        personalObject,
        peigReturnURL
    );
    aducid_attr_list_free( params );
    aducid_attr_list_free( personalObject );
    return result;
}

ADUCID_PUBLIC_FUNC const char *
aducid_init_personal_factor( AducidHandle_t handle, const char * peigReturnURL )
{
    return personal_factor_management_operation(
        handle,
        aducid_method_str( ADUCID_METHOD_INIT ),
        peigReturnURL
    );
}

ADUCID_PUBLIC_FUNC const char *
aducid_change_personal_factor( AducidHandle_t handle, const char * peigReturnURL )
{
    return personal_factor_management_operation(
        handle,
        aducid_method_str( ADUCID_METHOD_CHANGE ),
        peigReturnURL
    );
}

ADUCID_PUBLIC_FUNC const char *
aducid_delete_personal_factor( AducidHandle_t handle, const char * peigReturnURL )
{
    return personal_factor_management_operation(
        handle,
        aducid_method_str( ADUCID_METHOD_DELETE ),
        peigReturnURL
    );
}

ADUCID_PUBLIC_FUNC const char *
aducid_verify_personal_factor( AducidHandle_t handle, const char * peigReturnURL )
{
    return personal_factor_management_operation(
        handle,
        aducid_method_str( ADUCID_METHOD_VERIFY_LF ),
        peigReturnURL
    );
}

/* room operations */

ADUCID_PUBLIC_FUNC const char *
aducid_create_room_by_name( AducidHandle_t handle, const char *roomName, const char * peigReturnURL )
{
    const char *result;
    AducidAttributeList_t params, personalObject;

    params = aducid_attr_list_new();
    aducid_attr_list_append( params, "MeetingRoomName", roomName );
    
    personalObject = aducid_attr_list_new();
    aducid_attr_list_append( personalObject, "personalObjectTypeName", "peigMgmt" );
    aducid_attr_list_append( personalObject, "personalObjectAlgorithmName", aducid_algorithm_str(ADUCID_ALGORITHM_PEIG_MGMT) );

    result = aducid_exuse(
        handle,
        aducid_method_str( ADUCID_METHOD_CREATE_ROOM_BY_NAME ),
        params,
        personalObject,
        peigReturnURL
    );
    
    aducid_attr_list_free( params );
    aducid_attr_list_free( personalObject );
    return result;
}    

ADUCID_PUBLIC_FUNC const char *
aducid_enter_room_by_name( AducidHandle_t handle, const char *roomName, const char * peigReturnURL )
{
    const char *result;
    AducidAttributeList_t params, personalObject;

    params = aducid_attr_list_new();
    aducid_attr_list_append( params, "MeetingRoomName", roomName );
    
    personalObject = aducid_attr_list_new();
    aducid_attr_list_append( personalObject, "personalObjectTypeName", "peigMgmt" );
    aducid_attr_list_append( personalObject, "personalObjectAlgorithmName", aducid_algorithm_str(ADUCID_ALGORITHM_PEIG_MGMT) );

    result = aducid_exuse(
        handle,
        aducid_method_str( ADUCID_METHOD_ENTER_ROOM_BY_NAME ),
        params,
        personalObject,
        peigReturnURL
    );
    
    aducid_attr_list_free( params );
    aducid_attr_list_free( personalObject );
    return result;
}    

ADUCID_PUBLIC_FUNC const char *
aducid_create_room_by_story( AducidHandle_t handle, const char * peigReturnURL )
{
    const char *result;
    AducidAttributeList_t personalObject;

    personalObject = aducid_attr_list_new();
    aducid_attr_list_append( personalObject, "personalObjectTypeName", "peigMgmt" );
    aducid_attr_list_append( personalObject, "personalObjectAlgorithmName", aducid_algorithm_str(ADUCID_ALGORITHM_PEIG_MGMT) );

    result = aducid_exuse(
        handle,
        aducid_method_str( ADUCID_METHOD_CREATE_ROOM_BY_STORY ),
        NULL,
        personalObject,
        peigReturnURL
    );

    aducid_attr_list_free( personalObject );
    return result;
}    

ADUCID_PUBLIC_FUNC const char *
aducid_enter_room_by_story( AducidHandle_t handle, const char * peigReturnURL )
{
    const char *result;
    AducidAttributeList_t personalObject;

    personalObject = aducid_attr_list_new();
    aducid_attr_list_append( personalObject, "personalObjectTypeName", "peigMgmt" );
    aducid_attr_list_append( personalObject, "personalObjectAlgorithmName", aducid_algorithm_str(ADUCID_ALGORITHM_PEIG_MGMT) );

    result = aducid_exuse(
        handle,
        aducid_method_str( ADUCID_METHOD_ENTER_ROOM_BY_STORY ),
        NULL,
        personalObject,
        peigReturnURL
    );

    aducid_attr_list_free( personalObject );
    return result;
}

/* room operations */

ADUCID_PUBLIC_FUNC const char *
aducid_peig_local_link( AducidHandle_t handle, AducidPeigLocalLink_t linkType, const char * peigReturnURL )
{
    const char *result;
    AducidAttributeList_t params, personalObject;

    params = aducid_attr_list_new();
    switch( linkType ) {
    case ADUCID_PEIG_LOCAL_LINK_PRIMARY_REPLICA:
        aducid_attr_list_append( params, "PrimaryReplica", "1" );
        break;
    case ADUCID_PEIG_LOCAL_LINK_SECONDARY_REPLICA:
        aducid_attr_list_append( params, "SecondaryReplica", "1" );
        break;
    case ADUCID_PEIG_LOCAL_LINK_CONNECTION_USB:
        aducid_attr_list_append( params, "Connection", "Usb" );
        break;
    }
    personalObject = aducid_attr_list_new();
    aducid_attr_list_append( personalObject, "personalObjectTypeName", "peigMgmt" );
    aducid_attr_list_append( personalObject, "personalObjectAlgorithmName", aducid_algorithm_str(ADUCID_ALGORITHM_PEIG_MGMT) );

    result = aducid_exuse(
        handle,
        aducid_method_str( ADUCID_METHOD_PEIG_LOCAL_LINK ),
        params,
        personalObject,
        peigReturnURL
    );
    
    aducid_attr_list_free( params );
    aducid_attr_list_free( personalObject );
    return result;
}

/* payment/transaction operations */

ADUCID_PUBLIC_FUNC const char *
aducid_init_payment(AducidHandle_t handle, bool usePersonalFactor, const char *peigReturnURL)
{
    const char *result;
    AducidAttributeList_t params, personalObject;

    params = aducid_attr_list_new();
    if( usePersonalFactor ) aducid_attr_list_append( params, "UsePersonalFactor", "1" );

    personalObject = aducid_attr_list_new();
    aducid_attr_list_append( personalObject, "personalObjectName", "payment" );
    aducid_attr_list_append( personalObject, "personalObjectTypeName", "payment" );
    aducid_attr_list_append( personalObject, "personalObjectAlgorithmName", aducid_algorithm_str( ADUCID_ALGORITHM_PAYMENT ) );

    result = aducid_exuse(
        handle,
        aducid_method_str( ADUCID_METHOD_INIT ),
        params,
        personalObject,
        peigReturnURL
    );
    
    aducid_attr_list_free( params );
    aducid_attr_list_free( personalObject );
    return result;
}

ADUCID_PUBLIC_FUNC const char *
aducid_confirm_text_transaction(AducidHandle_t handle, const char *textUTF8, bool usePersonalFactor, const char *peigReturnURL)
{
    const char *result;
    char *textEscaped;
    AducidAttributeList_t params, personalObject;

    if( ! textUTF8 ) return NULL;

    textEscaped = xml_encode(textUTF8);
    params = aducid_attr_list_new();
    aducid_attr_list_append( params, "PaymentMessage", textEscaped );
    if( usePersonalFactor ) aducid_attr_list_append( params, "UsePersonalFactor", "1" );

    personalObject = aducid_attr_list_new();
    aducid_attr_list_append( personalObject, "personalObjectName", "payment" );
    aducid_attr_list_append( personalObject, "personalObjectTypeName", "payment" );
    aducid_attr_list_append( personalObject, "personalObjectAlgorithmName", aducid_algorithm_str( ADUCID_ALGORITHM_PAYMENT ) );

    result = aducid_exuse(
        handle,
        aducid_method_str( ADUCID_METHOD_CONFIRM_TRANSACTION ),
        params,
        personalObject,
        peigReturnURL
    );
    
    aducid_attr_list_free( params );
    aducid_attr_list_free( personalObject );
    safe_free( textEscaped );
    return result;
}

ADUCID_PUBLIC_FUNC const char *
aducid_confirm_money_transaction(AducidHandle_t handle, const char *fromAccount, const char *toAccount, const char *amount, bool usePersonalFactor, const char *peigReturnURL)
{
    const char *result;
    AducidAttributeList_t params, personalObject;

    if( ! fromAccount || ! toAccount || ! amount ) return NULL;

    params = aducid_attr_list_new();
    aducid_attr_list_append( params, "PaymentAmount", amount );
    aducid_attr_list_append( params, "PaymentFromAccount", fromAccount );
    aducid_attr_list_append( params, "PaymentToAccount", toAccount );
    if( usePersonalFactor ) aducid_attr_list_append( params, "UsePersonalFactor", "1" );

    personalObject = aducid_attr_list_new();
    aducid_attr_list_append( personalObject, "personalObjectName", "payment" );
    aducid_attr_list_append( personalObject, "personalObjectTypeName", "payment" );
    aducid_attr_list_append( personalObject, "personalObjectAlgorithmName", aducid_algorithm_str( ADUCID_ALGORITHM_PAYMENT ) );

    result = aducid_exuse(
        handle,
        aducid_method_str( ADUCID_METHOD_CONFIRM_TRANSACTION ),
        params,
        personalObject,
        peigReturnURL
    );
    
    aducid_attr_list_free( params );
    aducid_attr_list_free( personalObject );
    return result;
}

// This function returns true if parameter should be filtered
// from transaction result in case of failure.
bool _filter_attribute(const char *name) {
    static const char *attributesToFilter[] = {
        "PaymentSignature",
        NULL
    };
    int i = 0;
    while(attributesToFilter[i] != NULL ) {
        if( strcmp( name, attributesToFilter[i] ) == 0 ) return true;
        ++i;
    }
    return false;
}

ADUCID_PUBLIC_FUNC bool
aducid_verify_transaction( AducidHandle_t handle, AducidAttributeList_t *transaction )
{
    bool result = false;
    int a;
    char *p;
    
    if( ! aducid_verify( handle ) ) { *transaction = NULL; return false; }
    if( transaction ) *transaction = aducid_attr_list_new();
    AducidAIMGetPSLAttributesResponse_t *
        all = aducid_get_psl_attributes( handle, ADUCID_ATTRIBUTE_SET_ALL, true );
    result = true;
    // personal factor
    p = aducid_attr_list_get_first_by_name( all->personalObjectAttributes, "UsePersonalFactor" );
    if( p && ( strcmp( p, "OK" ) != 0 ) ) { result = false; }
    p = aducid_attr_list_get_first_by_name( all->personalObjectAttributes, "Return_Status" );
    if( p && ( strcmp( p, "ConfirmedByUser" ) != 0 ) ) { result = false; }
    
    if( transaction ) {
        a = 0;
        aducid_attr_list_first( all->personalObjectAttributes );
        const char *name, *value;

        name = aducid_attr_list_get_name( all->personalObjectAttributes );
        value = aducid_attr_list_get_value( all->personalObjectAttributes );
        while( name ) {
            printf("1%s\t%s\n",name,value);
            if( result || ! _filter_attribute(name) ) {
                printf("2%s\t%s\n",name,value);
                char *decoded = xml_decode(value);
                if( decoded ) {
                    printf("3%s\t%s\n",name,value);
                    aducid_attr_list_append( *transaction, name, decoded);
                    free(decoded);
                }
            }
            aducid_attr_list_next( all->personalObjectAttributes );
            name = aducid_attr_list_get_name( all->personalObjectAttributes);
            value = aducid_attr_list_get_value( all->personalObjectAttributes);
        }
    }
    return result;
}
