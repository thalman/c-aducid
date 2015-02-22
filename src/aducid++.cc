#include "aducid++.h"

namespace aducid
{

AducidClient::AducidClient(const std::string &AIM) {
    this->handle = aducid_new(AIM.c_str(),NULL,NULL,NULL,NULL);
    this->AIM = AIM;
}

AducidClient::AducidClient(const char* AIM) {
    this->handle = aducid_new(AIM,NULL,NULL,NULL,NULL);
    this->AIM = AIM;
}

string AducidClient::authId() const {
    string result;
    const char *id =  aducid_get_authid(this->handle);
    if(id) result = id;
    return result;
}

void AducidClient::authId(const string &authId) {
    if( authId.empty() ) { this->authId(NULL); }
    else { this->authId(authId.c_str()); }
}

void AducidClient::authId(const char *authId) {
    if( this->handle ) aducid_set_authid(this->handle,authId);
}

string AducidClient::authKey() const {
    string result;
    const char *id =  aducid_get_authkey(this->handle);
    if(id) result = id;
    return result;
}    

void AducidClient::authKey(const string &authKey){
    if( authKey.empty() ) { this->authKey(NULL); }
    else { this->authKey(authKey.c_str()); };
}

void AducidClient::authKey(const char *authKey) {
    aducid_set_authkey(this->handle,authKey);
}
        
string  AducidClient::bindingId() const {
    string result;
    const char *id =  aducid_get_bindingid(this->handle);
    if(id) result = id;
    return result;
}
        
void  AducidClient::bindingId(const string &bindingId) {
    if( bindingId.empty() ) { this->bindingId(NULL); }
    else { this->bindingId(bindingId.c_str()); }
}

void  AducidClient::bindingId(const char *bindingId) {
    aducid_set_bindingid(this->handle,bindingId);
}

string AducidClient::bindingKey() const {
    string result;
    const char *id =  aducid_get_bindingkey(this->handle);
    if(id) result = id;
    return result;
}

void AducidClient::bindingKey(const string &bindingKey) {
    if( bindingKey.empty() ) { this->bindingKey(NULL); }
    else { this->bindingKey(bindingKey.c_str()); }
}

void AducidClient::bindingKey(const char *bindingKey) {
    aducid_set_bindingkey(this->handle,bindingKey);
}

bool AducidClient::open(const string peigReturnName) {
    return ( aducid_open(this->handle, peigReturnName.c_str()) != NULL );
}

bool AducidClient::init(const string peigReturnName) {
    return ( aducid_init(this->handle, peigReturnName.c_str()) != NULL );
}

bool AducidClient::change(const string peigReturnName) {
    return ( aducid_change(this->handle, peigReturnName.c_str()) != NULL );
}

bool AducidClient::rechange(const string peigReturnName) {
    return ( aducid_rechange(this->handle, peigReturnName.c_str()) != NULL );
}

bool AducidClient::erase(const string peigReturnName) {
    return( aducid_delete(this->handle, peigReturnName.c_str()) != NULL );
}

bool AducidClient::close() {
    return
        aducid_aim_close_session(
            this->handle->R4,
            this->handle->authId,
            this->handle->AIMName,
            this->handle->authKey
        );
}

bool AducidClient::verify() {
    return aducid_verify(this->handle);
}

string AducidClient::userDatabaseIndex() {
    string result;
    const char *udi = aducid_get_user_database_index(this->handle);
    if(udi) result = udi;
    return result;
}

map<string,string>
AducidClient::getPSLAtributes( AducidAttributeSet set, bool useCache ) {
    map<string,string> result;
    const AducidAIMGetPSLAttributesResponse *response =
        aducid_get_psl_attributes(this->handle,set,useCache);
    if(response->statusAIM) result["statusAIM"] = aducid_aim_status_str(response->statusAIM);
    if(response->statusAuth) result["statusAuth"] = aducid_auth_status_str(response->statusAuth);
    if(response->operationName) result["operationName"] = aducid_operation_str(response->operationName);

    if( response->userDatabaseIndex ) result["operationName"] = response->userDatabaseIndex;
    if( response->userId )            result["userId"] = response->userId;
    if( response->validityCount )     result["validityCount"] = response->validityCount;
    if( response->validityTime )      result["validityTime"] = response->validityTime;
    if( response->orangeCount )       result["orangeCount"] = response->orangeCount;
    if( response->orangeTime )        result["orangeTime"] = response->orangeTime;
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
    char *url = aducid_get_aimproxy_url(this->handle);
    if(url) {
        result = url;
        free(url);
    }
    return result;
}

AducidClient::~AducidClient() {
    aducid_free(this->handle);
}

}
