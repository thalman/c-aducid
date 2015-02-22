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
        AducidClient(const string &AIM);
        AducidClient(const char *AIM);

        string authId() const;
        void authId(const string &authId);
        void authId(const char *authId);

        string authKey() const;
        void authKey(const string &authKey);
        void authKey(const char *authKey);
        
        string bindingId() const;
        void bindingId(const string &authId);
        void bindingId(const char *authId);

        string bindingKey() const;
        void bindingKey(const string &authKey);
        void bindingKey(const char *authKey);
        
        bool open(const string peigReturnName);
        bool init(const string peigReturnName);
        bool change(const string peigReturnName);
        bool rechange(const string peigReturnName);
        bool erase(const string peigReturnName);
        bool close();

        bool verify();
        map<string,string> getPSLAtributes( AducidAttributeSet set, bool useCache );
        string getPSLAtribute( const std::string &attr );
        string userDatabaseIndex();
        string AIMProxyURL() const;
        ~AducidClient();
    private:
        AducidHandle handle;
        std::string AIM;
    };

}
#endif // __ADUCIDPP_H__
