

#include "core/http/RestCookie.h"
#include <functional>
#include <limits.h>
//#include <algorithm>
#include "shared/businessLogic/SharedServiceMgrUtils.h"
#include "core/log/Logger.h"
#include "core/util/StringUtils.h"

namespace BBMobileSDK
{
    RestCookie::RestCookie()
    : Name()
    , Value()
    , Path()
    , Expires(LLONG_MAX)
    {
        
    }
    
    RestCookie::RestCookie(const std::string & name, const std::string & value)
    : Name(name)
    , Value(value)
    , Domain("")
    , Path("/")
    , Expires(LLONG_MAX)
    {
        
    }
    
    RestCookie::RestCookie(const std::string & name, const std::string & value, const std::string & domain, const std::string & path, const long long expires)
    : Name(name)
    , Value(value)
    , Domain(domain)
    , Path(path)
    , Expires(expires)
    {
        
    }
    
    RestCookie::RestCookie(const RestCookie &rhs)
    {
        *this = rhs;
    }
    
    RestCookie& RestCookie::operator = (const RestCookie &rhs)
    {
        if (&rhs != this)
        {
            Name = rhs.Name;
            Value = rhs.Value;
            Domain = rhs.Domain;
            Path = rhs.Path;
            Expires = rhs.Expires;
        }
        
        return *this;
    }
    
    RestCookie::~RestCookie()
    {
        
    }
    
    std::string RestCookie::ToString(bool encode)
    {
        std::stringstream cookieStream;
        cookieStream << Name << "=" << (encode ? StringUtils::UrlEncode(Value) : Value) << ";";
        return cookieStream.str();
    }
    
    long long RestCookie::GetHashKey() const
    {
        std::hash<std::string> strHash;
        return strHash(Name + ";;" + Domain + ";;" + Path);
    }
    
    /**
     *  Reference to netscape format  http://www.cookiecentral.com/faq/#3.5 and
     *  get_netscape_format in https://github.com/curl/curl/blob/master/lib/cookie.c
     */
    RestCookiePtr RestCookie::InstanceFromNetscapeCookie(const std::string cookieString)
    {
        auto restCookie = std::make_shared<RestCookie>();
        std::vector<std::string> cookieFields = StringUtils::Split(cookieString, "\t");
        
        if (cookieFields.size() != 7) {
            Logger::error("lib curl return a non netscape format cookie string");
            return restCookie;
        }
        
        restCookie->Domain  = cookieFields[CookieFieldDomain];
        restCookie->Path    = cookieFields[CookieFieldPath];
        restCookie->Expires = StringUtils::ConvertStringToNumeric<long long>(cookieFields[CookieFieldExpires]);
        restCookie->Name    = cookieFields[CookieFieldName];
        restCookie->Value   = cookieFields[CookieFieldValue];
        
        return restCookie;
    }
}
