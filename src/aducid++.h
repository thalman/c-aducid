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
        AducidClient( const string &AIM );
        AducidClient( const char *AIM );

        string authId() const;
        void authId( const string &authId );
        void authId( const char *authId );

        string authKey() const;
        void authKey( const string &authKey );
        void authKey( const char *authKey );
        
        string bindingId() const;
        void bindingId( const string &authId );
        void bindingId( const char *authId );

        string bindingKey() const;
        void bindingKey( const string &authKey );
        void bindingKey( const char *authKey );
        
        bool open( const char *peigReturnURL );
        bool open( const string &peigReturnURL );
        bool init( const char *peigReturnURL );
        bool init( const string &peigReturnURL );
        bool change( const char *peigReturnURL );
        bool change( const string &peigReturnURL );
        bool rechange( const char *peigReturnURL );
        bool rechange( const string &peigReturnURL );
        bool reinit( const char *peigReturnURL );
        bool reinit( const string &peigReturnURL );
        bool deleteIdentity( const char *peigReturnURL );
        bool deleteIdentity( const string &peigReturnURL );

        bool initPersonalFactor( const char *peigReturnURL );
        bool initPersonalFactor( const string &peigReturnURL );
        bool changePersonalFactor( const char *peigReturnURL );
        bool changePersonalFactor( const string &peigReturnURL );
        bool deletePersonalFactor( const char *peigReturnURL );
        bool deletePersonalFactor( const string &peigReturnURL );
        bool verifyPersonalFactor( const char *peigReturnURL );
        bool verifyPersonalFactor( const string &peigReturnURL );

        bool createRoomByStory( const char *peigReturnURL );
        bool createRoomByStory( const string &peigReturnURL );
        bool enterRoomByStory( const char *peigReturnURL );
        bool enterRoomByStory( const string &peigReturnURL );
        bool createRoomByName( const char *name, const char *peigReturnURL );
        bool createRoomByName( const string &name, const string &peigReturnURL );
        bool enterRoomByName( const char *name, const char *peigReturnURL );
        bool enterRoomByName( const string &name, const string &peigReturnURL );

        bool linkLocal( AducidPeigLocalLink_t linkType, const char *peigReturnURL );
        bool linkLocal( AducidPeigLocalLink_t linkType, const string &peigReturnURL );
        bool initPayment( bool usePersonalFactor, const char *peigReturnURL );
        bool initPayment( bool usePersonalFactor, const string &peigReturnURL );
        bool confirmTextTransaction( const char *textUTF8, bool usePersonalFactor, const char *peigReturnURL );
        bool confirmTextTransaction( const string &textUTF8, bool usePersonalFactor, const string &peigReturnURL );
        bool confirmMoneyTransaction( const char *fromAccount, const char *toAccount, const char *amount, bool usePersonalFactor, const char *peigReturnURL );
        bool confirmMoneyTransaction( const string &fromAccount, const string &toAccount, const string &amount, bool usePersonalFactor, const string &peigReturnURL );
        
        bool close();

        bool verify();
        bool verifyTransaction();
        bool verifyTransaction( map<string,string> &params );
        map<string,string> getPSLAtributes( AducidAttributeSet_t set, bool useCache );
        map<string,string> EPOReadUserAttrSet(const char *attrSetName);
        map<string,string> EPOReadUserAttrSet(const string &attrSetName);

        string getPSLAtribute( const std::string &attr );
        string userDatabaseIndex();
        string AIMProxyURL() const;
        ~AducidClient();
    protected:
        map<string,string> AducidListToMap(const AducidAttributeList_t list) const;
    private:
        AducidHandle_t _handle;
        std::string _AIM;
    };

}
#endif // __ADUCIDPP_H__
