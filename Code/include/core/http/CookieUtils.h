

#ifndef CookieUtils_hpp
#define CookieUtils_hpp

#include "core/util/BaseInclude.h"

namespace BBMobileSDK {
    BB_FORWARD_DECLARE(RestCookie);
    
    class CookieUtils
    {
    public:
        static const std::string StringFromCookies(const RestCookieVPtr &cookies);
        static const RestCookieVPtr CookiesFromString(const std::string &cookiesString);
        
        static void EncodeCookieValue(RestCookieVPtr &cookies);
        static void DecodeCookieValue(RestCookieVPtr &cookies);
        
        static void ParseCookies(const std::string & cookies, std::vector<KVPair> & kvPairs);
        static std::string EncodeCookieValue(const std::string & cookies);
        static std::string DecodeCookieValue(const std::string & cookies);
        
    private:
        static void URLEncodeCookie(RestCookieVPtr & cookies, bool encode);
        static std::string URLEncodeCookie(const std::string & cookies, bool encode);
    };
}

#endif /* CookieUtils_hpp */
