

#ifndef VsboardMobile_RestCookie_h
#define VsboardMobile_RestCookie_h

#include <string>

#include "core/util/BaseInclude.h"

namespace BBMobileSDK {
    
    enum CookieField
    {
        CookieFieldDomain = 0,
        CookieFieldTailMatch = 1,
        CookieFieldPath = 2,
        CookieFieldSecure = 3,
        CookieFieldExpires = 4,
        CookieFieldName = 5,
        CookieFieldValue = 6
    };
    
    BB_FORWARD_DECLARE(RestCookie);
    
    class RestCookie
    {
    public:
        RestCookie();
        RestCookie(const std::string & name, const std::string & value);
        RestCookie(const std::string & name, const std::string & value, const std::string & domain, const std::string & path, const long long expires);
        RestCookie(const RestCookie &rhs);
        RestCookie& operator = (const RestCookie &rhs);
        ~RestCookie();
        
        static RestCookiePtr InstanceFromNetscapeCookie(const std::string cookieString);
        
    public:
        std::string Name;
        std::string Value;
        std::string Domain;
        std::string Path;
        long long   Expires;
        
        std::string ToString(bool encode = false);
        long long GetHashKey() const;
    };
}


#endif

