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

        bool initLocalFactor( const char *peigReturnURL );
        bool initLocalFactor( const string &peigReturnURL );
        bool changeLocalFactor( const char *peigReturnURL );
        bool changeLocalFactor( const string &peigReturnURL );
        bool deleteLocalFactor( const char *peigReturnURL );
        bool deleteLocalFactor( const string &peigReturnURL );
        bool verifyLocalFactor( const char *peigReturnURL );
        bool verifyLocalFactor( const string &peigReturnURL );

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
        bool initPayment( bool useLocalFactor, const char *peigReturnURL );
        bool initPayment( bool useLocalFactor, const string &peigReturnURL );
        bool confirmTextTransaction( const char *textUTF8, bool useLocalFactor, const char *peigReturnURL );
        bool confirmTextTransaction( const string &textUTF8, bool useLocalFactor, const string &peigReturnURL );
        bool confirmMoneyTransaction( const char *fromAccount, const char *toAccount, const char *amount, bool useLocalFactor, const char *peigReturnURL );
        bool confirmMoneyTransaction( const string &fromAccount, const string &toAccount, const string &amount, bool useLocalFactor, const string &peigReturnURL );
        
        bool close();

        bool verify();
        bool verifyTransaction();
        bool verifyTransaction( map<string,string> &params );
        map<string,string> getPSLAtributes( AducidAttributeSet_t set, bool useCache );
        string getPSLAtribute( const std::string &attr );
        string userDatabaseIndex();
        string AIMProxyURL() const;
        ~AducidClient();
    protected:
        map<string,string> AducidListToMap(const AducidAttributeList_t *list) const;
    private:
        AducidHandle_t _handle;
        std::string _AIM;
    };

}
#endif // __ADUCIDPP_H__
