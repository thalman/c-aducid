#ifndef __ADUCIDPP_H__
#define __ADUCIDPP_H__

#include <aducid.h>
#include <string>
#include <map>

namespace aducid
{

    using namespace std;
    
    class AducidClient {
    public:
		ADUCID_PUBLIC_FUNC AducidClient(const string &AIM);
		ADUCID_PUBLIC_FUNC AducidClient(const char *AIM);

		ADUCID_PUBLIC_FUNC string authId() const;
		ADUCID_PUBLIC_FUNC void authId(const string &authId);
		ADUCID_PUBLIC_FUNC void authId(const char *authId);

		ADUCID_PUBLIC_FUNC string authKey() const;
		ADUCID_PUBLIC_FUNC void authKey(const string &authKey);
		ADUCID_PUBLIC_FUNC void authKey(const char *authKey);
        
		ADUCID_PUBLIC_FUNC string bindingId() const;
		ADUCID_PUBLIC_FUNC void bindingId(const string &authId);
		ADUCID_PUBLIC_FUNC void bindingId(const char *authId);

		ADUCID_PUBLIC_FUNC string bindingKey() const;
		ADUCID_PUBLIC_FUNC void bindingKey(const string &authKey);
		ADUCID_PUBLIC_FUNC void bindingKey(const char *authKey);
        
		ADUCID_PUBLIC_FUNC bool open(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool open(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool init(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool init(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool change(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool change(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool rechange(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool rechange(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool reinit(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool reinit(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool deleteIdentity(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool deleteIdentity(const string &peigReturnURL);

		ADUCID_PUBLIC_FUNC bool initPersonalFactor(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool initPersonalFactor(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool changePersonalFactor(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool changePersonalFactor(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool deletePersonalFactor(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool deletePersonalFactor(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool verifyPersonalFactor(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool verifyPersonalFactor(const string &peigReturnURL);

		ADUCID_PUBLIC_FUNC bool createRoomByStory(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool createRoomByStory(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool enterRoomByStory(const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool enterRoomByStory(const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool createRoomByName(const char *name, const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool createRoomByName(const string &name, const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool enterRoomByName(const char *name, const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool enterRoomByName(const string &name, const string &peigReturnURL);

		ADUCID_PUBLIC_FUNC bool linkLocal(AducidPeigLocalLink_t linkType, const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool linkLocal(AducidPeigLocalLink_t linkType, const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool initPayment(bool usePersonalFactor, const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool initPayment(bool usePersonalFactor, const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool confirmTextTransaction(const char *textUTF8, bool usePersonalFactor, const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool confirmTextTransaction(const string &textUTF8, bool usePersonalFactor, const string &peigReturnURL);
		ADUCID_PUBLIC_FUNC bool confirmMoneyTransaction(const char *fromAccount, const char *toAccount, const char *amount, bool usePersonalFactor, const char *peigReturnURL);
		ADUCID_PUBLIC_FUNC bool confirmMoneyTransaction(const string &fromAccount, const string &toAccount, const string &amount, bool usePersonalFactor, const string &peigReturnURL);
        
		ADUCID_PUBLIC_FUNC bool close();

        bool verifyTransaction();
        bool verifyTransaction( map<string,string> &params );
        map<string,string> getPSLAtributes( AducidAttributeSet_t set, bool useCache );
        map<string,string> EPOReadUserAttrSet(const char *attrSetName);
        map<string,string> EPOReadUserAttrSet(const string &attrSetName);

        void EPOWriteUserAttrSet(const string &attrSetName, map<string,string>attributes);

        string getPSLAtribute( const std::string &attr );
        string userDatabaseIndex();
        string AIMProxyURL() const;
        ~AducidClient();
    protected:
        map<string,string> AducidListToMap(const AducidAttributeList_t list) const;
        AducidAttributeList_t MapToAducidList(const map<string,string> &attrs) const;
    private:
        AducidHandle_t _handle;
        std::string _AIM;
    };

}
#endif // __ADUCIDPP_H__
