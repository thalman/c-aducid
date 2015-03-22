#include "definitions.h"
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

bool AducidClient::initLocalFactor( const char *peigReturnURL )
{
    return aducid_init_local_factor( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::initLocalFactor( const string &peigReturnURL )
{
    return initLocalFactor( peigReturnURL.c_str() );
}

bool AducidClient::changeLocalFactor( const char *peigReturnURL )
{
    return aducid_change_local_factor( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::changeLocalFactor( const string &peigReturnURL )
{
    return changeLocalFactor( peigReturnURL.c_str() );
}

bool AducidClient::deleteLocalFactor( const char *peigReturnURL )
{
    return aducid_delete_local_factor( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::deleteLocalFactor( const string &peigReturnURL )
{
    return deleteLocalFactor( peigReturnURL.c_str() );
}

bool AducidClient::verifyLocalFactor( const char *peigReturnURL )
{
    return aducid_verify_local_factor( _handle, peigReturnURL ) != NULL;
}
bool AducidClient::verifyLocalFactor( const string &peigReturnURL )
{
    return verifyLocalFactor( peigReturnURL.c_str() );
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

bool AducidClient::initPayment( bool useLocalFactor, const char *peigReturnURL )
{
    return ( aducid_init_payment( _handle, useLocalFactor, peigReturnURL ) != NULL );
}
bool AducidClient::initPayment( bool useLocalFactor, const string &peigReturnURL ) {
    return initPayment( useLocalFactor, peigReturnURL.c_str() );
}

bool AducidClient::confirmTextTransaction( const char *textUTF8, bool useLocalFactor, const char *peigReturnURL )
{
    return aducid_confirm_text_transaction( _handle, textUTF8, useLocalFactor, peigReturnURL ) != NULL;
}
bool AducidClient::confirmTextTransaction( const string &textUTF8, bool useLocalFactor, const string &peigReturnURL )
{
    return confirmTextTransaction( textUTF8.c_str(), useLocalFactor, peigReturnURL.c_str() );
}

bool AducidClient::confirmMoneyTransaction( const char *fromAccount,
                                            const char *toAccount,
                                            const char *amount,
                                            bool useLocalFactor,
                                            const char *peigReturnURL )
{
    return aducid_confirm_money_transaction(
        _handle,
        fromAccount,
        toAccount,
        amount,
        useLocalFactor,
        peigReturnURL ) != NULL ;
}
bool AducidClient::confirmMoneyTransaction( const string &fromAccount,
                                            const string &toAccount,
                                            const string &amount,
                                            bool useLocalFactor,
                                            const string &peigReturnURL )
{
    return confirmMoneyTransaction(
        fromAccount.c_str(),
        toAccount.c_str(),
        amount.c_str(),
        useLocalFactor,
        peigReturnURL.c_str() );
}

bool AducidClient::close() {
    return
        aducid_aim_close_session(
            _handle->R4,
            _handle->authId,
            _handle->AIMName,
            _handle->authKey
        );
}

bool AducidClient::verify() {
    return aducid_verify( _handle );
}

bool AducidClient::verifyTransaction() {
    return aducid_verify_transaction( _handle, NULL );
}

bool AducidClient::verifyTransaction( map<string,string> &params ) {
    AducidAttributeList_t list = NULL;
    bool result = aducid_verify_transaction( _handle, &list );
    if( list == NULL ) return result;
    AducidAttributeListItem_t *attr = ((AducidAttributeListStruct_t *)list)->firstItem;
    while( attr ) {
        params[attr->name] = attr->value;
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
AducidClient::getPSLAtributes( AducidAttributeSet_t set, bool useCache ) {
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

string AducidClient::getPSLAtribute( const std::string &attr ) {
    map<string,string> attrs = getPSLAtributes(ADUCID_ATTRIBUTE_SET_ALL,true);
    map<string,string>::iterator search = attrs.find(attr);
    if( search != attrs.end() ) {
        return search->second;
    }
    return "";
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

map<string,string> AducidClient::AducidListToMap(const AducidAttributeList_t *list) const {
    map<string,string> result;
    if( list == NULL ) return result;
    AducidAttributeListItem_t *attr = ((AducidAttributeListStruct_t *)list)->firstItem;
    while( attr ) {
        result[attr->name] = attr->value;
        attr = attr->next;
    }
    return result;
}

AducidClient::~AducidClient() {
    aducid_free(_handle);
}

}
