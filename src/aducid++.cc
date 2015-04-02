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

#include "aducid++.h"
#include "attrlist.h"

namespace aducid
{

AducidClient::AducidClient( const std::string &AIM ) {
    _handle = aducid_new(AIM.c_str(),NULL,NULL,NULL,NULL);
    _AIM = AIM;
}

AducidClient::AducidClient( const char* AIM ) {
    _handle = aducid_new( AIM, NULL, NULL, NULL, NULL );
    _AIM = AIM;
}

string AducidClient::authId() const {
    string result;
    const char *id =  aducid_get_authid( _handle );
    if(id) result = id;
    return result;
}

void AducidClient::authId( const string &authId ) {
    if( authId.empty() ) { this->authId(NULL); }
    else { this->authId(authId.c_str()); }
}

void AducidClient::authId( const char *authId ) {
    if( authId && strlen( authId ) ) { aducid_set_authid( _handle, authId ); }
    else { aducid_set_authid( _handle, NULL ); }
}

string AducidClient::authKey() const {
    string result;
    const char *id =  aducid_get_authkey( _handle );
    if(id) result = id;
    return result;
}    

void AducidClient::authKey( const string &authKey ){
    if( authKey.empty() ) { this->authKey(NULL); }
    else { this->authKey(authKey.c_str()); };
}

void AducidClient::authKey( const char *authKey ) {
    if( authKey && strlen( authKey ) ) { aducid_set_authkey( _handle, authKey ); }
    else { aducid_set_authkey( _handle, NULL ); }
}
        
string  AducidClient::bindingId() const {
    string result;
    const char *id =  aducid_get_bindingid( _handle );
    if(id) result = id;
    return result;
}
        
void  AducidClient::bindingId(const string &bindingId) {
    if( bindingId.empty() ) { this->bindingId(NULL); }
    else { this->bindingId(bindingId.c_str()); }
}

void  AducidClient::bindingId(const char *bindingId) {
    if( bindingId && strlen( bindingId ) ) { aducid_set_bindingid( _handle, bindingId ); }
    else { aducid_set_bindingid( _handle, bindingId ); }
}

string AducidClient::bindingKey() const {
    string result;
    const char *id =  aducid_get_bindingkey( _handle );
    if(id) result = id;
    return result;
}

void AducidClient::bindingKey(const string &bindingKey) {
    if( bindingKey.empty() ) { this->bindingKey(NULL); }
    else { this->bindingKey(bindingKey.c_str()); }
}
void AducidClient::bindingKey(const char *bindingKey) {
    if( bindingKey && strlen( bindingKey ) ) { aducid_set_bindingkey( _handle, bindingKey ); }
    else { aducid_set_bindingkey( _handle, NULL ); }
}

bool AducidClient::open( const char *peigReturnURL ) {
    return aducid_open( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::open( const string &peigReturnURL ) {
    return open( peigReturnURL.c_str() );
}

bool AducidClient::init( const char *peigReturnURL ) {
    return aducid_init( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::init( const string &peigReturnURL ) {
    return init( peigReturnURL.c_str() );
}

bool AducidClient::change( const char *peigReturnURL ) {
    return aducid_change( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::change( const string &peigReturnURL ) {
    return change( peigReturnURL.c_str() );
}

bool AducidClient::rechange( const char *peigReturnURL ) {
    return aducid_rechange( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::rechange( const string &peigReturnURL ) {
    return rechange( peigReturnURL.c_str() );
}

bool AducidClient::reinit( const char *peigReturnURL ) {
    return aducid_reinit( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::reinit( const string &peigReturnURL ) {
    return reinit( peigReturnURL.c_str() );
}

bool AducidClient::deleteIdentity( const char *peigReturnURL ) {
    return aducid_delete( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::deleteIdentity( const string &peigReturnURL ) {
    return deleteIdentity( peigReturnURL.c_str() );
}

bool AducidClient::initPersonalFactor( const char *peigReturnURL )
{
    return aducid_init_personal_factor( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::initPersonalFactor( const string &peigReturnURL )
{
    return initPersonalFactor( peigReturnURL.c_str() );
}

bool AducidClient::changePersonalFactor( const char *peigReturnURL )
{
    return aducid_change_personal_factor( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::changePersonalFactor( const string &peigReturnURL )
{
    return changePersonalFactor( peigReturnURL.c_str() );
}

bool AducidClient::deletePersonalFactor( const char *peigReturnURL )
{
    return aducid_delete_personal_factor( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::deletePersonalFactor( const string &peigReturnURL )
{
    return deletePersonalFactor( peigReturnURL.c_str() );
}

bool AducidClient::verifyPersonalFactor( const char *peigReturnURL )
{
    return aducid_verify_personal_factor( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::verifyPersonalFactor( const string &peigReturnURL )
{
    return verifyPersonalFactor( peigReturnURL.c_str() );
}

bool AducidClient::createRoomByStory( const char *peigReturnURL )
{
    return aducid_create_room_by_story( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::createRoomByStory( const string &peigReturnURL )
{
    return createRoomByStory( peigReturnURL.c_str() );
}

bool AducidClient::enterRoomByStory( const char *peigReturnURL )
{
    return aducid_enter_room_by_story( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::enterRoomByStory( const string &peigReturnURL )
{
    return enterRoomByStory( peigReturnURL.c_str() );
}

bool AducidClient::createRoomByName( const char *name, const char *peigReturnURL )
{
    return aducid_create_room_by_name( _handle, name, peigReturnURL ) != NULL;
}
bool AducidClient::createRoomByName( const string &name, const string &peigReturnURL )
{
    return createRoomByName( name.c_str(), peigReturnURL.c_str() );
}

bool AducidClient::enterRoomByName( const char *name, const char *peigReturnURL )
{
    return ( aducid_enter_room_by_name( _handle, name, peigReturnURL ) != NULL );
}
bool AducidClient::enterRoomByName( const string &name, const string &peigReturnURL )
{
    return enterRoomByName( name.c_str(), peigReturnURL.c_str() );
}

bool AducidClient::linkLocal( AducidPeigLocalLink_t linkType, const char *peigReturnURL )
{
    return ( aducid_peig_local_link( _handle, linkType, peigReturnURL ) != NULL );
}
bool AducidClient::linkLocal( AducidPeigLocalLink_t linkType, const string &peigReturnURL )
{
    return linkLocal( linkType, peigReturnURL.c_str() );
}

bool AducidClient::initPayment( bool usePersonalFactor, const char *peigReturnURL )
{
    return ( aducid_init_payment( _handle, usePersonalFactor, peigReturnURL ) != NULL );
}
bool AducidClient::initPayment( bool usePersonalFactor, const string &peigReturnURL ) {
    return initPayment( usePersonalFactor, peigReturnURL.c_str() );
}

bool AducidClient::confirmTextTransaction( const char *textUTF8, bool usePersonalFactor, const char *peigReturnURL )
{
    return aducid_confirm_text_transaction( _handle, textUTF8, usePersonalFactor, peigReturnURL ) != NULL;
}
bool AducidClient::confirmTextTransaction( const string &textUTF8, bool usePersonalFactor, const string &peigReturnURL )
{
    return confirmTextTransaction( textUTF8.c_str(), usePersonalFactor, peigReturnURL.c_str() );
}

bool AducidClient::confirmMoneyTransaction( const char *fromAccount,
                                            const char *toAccount,
                                            const char *amount,
                                            bool usePersonalFactor,
                                            const char *peigReturnURL )
{
    return aducid_confirm_money_transaction(
        _handle,
        fromAccount,
        toAccount,
        amount,
        usePersonalFactor,
        peigReturnURL ) != NULL ;
}
bool AducidClient::confirmMoneyTransaction( const string &fromAccount,
                                            const string &toAccount,
                                            const string &amount,
                                            bool usePersonalFactor,
                                            const string &peigReturnURL )
{
    return confirmMoneyTransaction(
        fromAccount.c_str(),
        toAccount.c_str(),
        amount.c_str(),
        usePersonalFactor,
        peigReturnURL.c_str() );
}

bool AducidClient::close() {
    return aducid_close( _handle );
}

bool AducidClient::verify() {
    return aducid_verify( _handle );
}

bool AducidClient::verifyTransaction() {
    return aducid_verify_transaction( _handle, NULL );
}

bool AducidClient::verifyTransaction( map<string,string> &transactionOtput ) {
    AducidAttributeList_t list = NULL;
    bool result = aducid_verify_transaction( _handle, &list );
    if( list == NULL ) return result;
    AducidAttributeListItem_t *attr = ((AducidAttributeListStruct_t *)list)->firstItem;
    while( attr ) {
        transactionOtput[attr->name] = attr->value;
        attr = attr->next;
    }
    aducid_attr_list_free( list );
    return result;
}

string AducidClient::userDatabaseIndex() {
    string result;
    const char *udi = aducid_get_user_database_index( _handle );
    if(udi) result = udi;
    return result;
}

map<string,string>
AducidClient::getPSLAttributes( AducidAttributeSet_t set, bool useCache ) {
    map<string,string> result;
    const AducidAIMGetPSLAttributesResponse_t *response =
        aducid_get_psl_attributes( _handle, set, useCache );
    if(response->statusAIM) result["statusAIM"] = aducid_aim_status_str(response->statusAIM);
    if(response->statusAuth) result["statusAuth"] = aducid_auth_status_str(response->statusAuth);
    if(response->operationName) result["operationName"] = aducid_operation_str(response->operationName);

    if( response->userDatabaseIndex ) result["operationName"] = response->userDatabaseIndex;
    if( response->userId )            result["userId"] = response->userId;
    if( response->validityCount )     result["validityCount"] = response->validityCount;
    if( response->validityTime )      result["validityTime"] = response->validityTime;
    if( response->expirationCountdownUses ) result["expirationCountdownUses"] = response->expirationCountdownUses;
    if( response->expirationCountdownTime ) result["orangeTime"] = response->expirationCountdownTime;
    if( response->securityProfileName ) result["securityProfileName"] = response->securityProfileName;
    if( response->authenticationProtocolName ) result["authenticationProtocolName"] = response->authenticationProtocolName;
    if( response->securityLevel )     result["securityLevel"] = response->securityLevel;
    if( response->ILID )              result["ILID"] = response->ILID;
    if( response->ilTypeName )        result["ilTypeName"] = response->ilTypeName;
    if( response->ilAlgorithmName )   result["ilAlgorithmName"] = response->ilAlgorithmName;
    if( response->ilValidityCount )   result["ilValidityCount"] = response->ilValidityCount;
    if( response->ilValidityTime )    result["ilValidityTime"] = response->ilValidityTime;
    if( response->authKey2 )          result["authKey2"] = response->authKey2;
    if( response->sessionKey )        result["sessionKey"] = response->sessionKey;
    if( response->bindingType )       result["bindingType"] = response->bindingType;
    return result;
}

string AducidClient::getPSLAttribute( const std::string &attr ) {
    map<string,string> attrs = getPSLAttributes(ADUCID_ATTRIBUTE_SET_ALL,true);
    map<string,string>::iterator search = attrs.find(attr);
    if( search != attrs.end() ) {
        return search->second;
    }
    return "";
}

map<string,string>
AducidClient::EPOReadUserAttrSet( const char *attrSetName ) {
    AducidAttributeList_t list;
    map<string,string> result;

    list = aducid_epo_read_user_attr_set( _handle, attrSetName );
    result = AducidListToMap( list );
    aducid_attr_list_free( list );
    return result;
}

map<string,string>
AducidClient::EPOReadUserAttrSet( const string &attrSetName ) {
    return EPOReadUserAttrSet( attrSetName.c_str() );
}

void
AducidClient::EPOWriteUserAttrSet(const string &attrSetName, map<string,string>attributes)
{
    AducidAttributeList_t list = MapToAducidList(attributes);
    aducid_epo_write_user_attr_set( _handle, attrSetName.c_str(), list);
    aducid_attr_list_free(list);
}


string AducidClient::AIMProxyURL() const {
    string result;
    char *url = aducid_get_aimproxy_url( _handle );
    if(url) {
        result = url;
        free(url);
    }
    return result;
}

map<string,string> AducidClient::AducidListToMap(const AducidAttributeList_t list) const {
    map<string,string> result;
    if( list == NULL ) return result;
    AducidAttributeListItem_t *attr = ((AducidAttributeListStruct_t *)list)->firstItem;
    while( attr ) {
        result[attr->name] = attr->value;
        attr = attr->next;
    }
    return result;
}

AducidAttributeList_t AducidClient::MapToAducidList(const map<string,string> &attrs) const {
    AducidAttributeList_t result = aducid_attr_list_new();
    for( map<string,string>::const_iterator i = attrs.begin() ; i != attrs.end(); ++i ) {
        aducid_attr_list_append( result, i->first.c_str(), i->second.c_str() );
    }
    return result;
}

AducidClient::~AducidClient() {
    aducid_free(_handle);
}

}
