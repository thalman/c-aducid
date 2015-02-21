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
    char *id =  aducid_get_authid(this->handle);
    if(id) result = id;
    return result;
}

void AducidClient::authId(const string &authId) {
    this->authId(authId.c_str());
}

void AducidClient::authId(const char *authId) {
    if( this->handle ) aducid_set_authid(this->handle,authId);
}

string AducidClient::authKey() const {
    string result;
    char *id =  aducid_get_authkey(this->handle);
    if(id) result = id;
    return result;
}    

void AducidClient::authKey(const string &authKey){
    this->authKey(authKey.c_str());
}

void AducidClient::authKey(const char *authKey) {
    aducid_set_authkey(this->handle,authKey);
}
        
string  AducidClient::bindingId() const {
    string result;
    char *id =  aducid_get_bindingid(this->handle);
    if(id) result = id;
    return result;
}
        
void  AducidClient::bindingId(const string &bindingId) {
    this->bindingId(bindingId.c_str());
}

void  AducidClient::bindingId(const char *bindingId) {
    aducid_set_bindingid(this->handle,bindingId);
}

string AducidClient::bindingKey() const {
    string result;
    char *id =  aducid_get_bindingkey(this->handle);
    if(id) result = id;
    return result;
}

void AducidClient::bindingKey(const string &bindingKey) {
    this->bindingKey(bindingKey.c_str());
}

void AducidClient::bindingKey(const char *bindingKey) {
    aducid_set_bindingkey(this->handle,bindingKey);
}

bool AducidClient::open(const string peigReturnName) {
    char *id = aducid_open(this->handle, peigReturnName.c_str());
    return id != NULL;
}

bool AducidClient::init(const string peigReturnName) {
    char *id = aducid_init(this->handle, peigReturnName.c_str());
    return id != NULL;
}

bool AducidClient::change(const string peigReturnName) {
    char *id = aducid_change(this->handle, peigReturnName.c_str());
    return id != NULL;
}

bool AducidClient::rechange(const string peigReturnName) {
    char *id = aducid_rechange(this->handle, peigReturnName.c_str());
    return id != NULL;
}

bool AducidClient::erase(const string peigReturnName) {
    char *id = aducid_delete(this->handle, peigReturnName.c_str());
    return id != NULL;
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
