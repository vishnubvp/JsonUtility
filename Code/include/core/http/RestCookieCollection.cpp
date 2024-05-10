
#include "core/http/RestCookieCollection.h"

#include "core/http/CookieUtils.h"
#include "core/http/RestCookie.h"

namespace BBMobileSDK
{
    
    RestCookieCollection::RestCookieCollection()
    : m_mtx()
    , m_cookies()
    {
    }
    
    RestCookieCollection::RestCookieCollection(const RestCookieCollection &rhs)
    {
        *this = rhs;
    }
    
    RestCookieCollection& RestCookieCollection::operator=(const BBMobileSDK::RestCookieCollection &rhs)
    {
        if (&rhs != this)
        {
            BBScopeLock lock(m_mtx);
            m_cookies = rhs.m_cookies;
        }
        return *this;
    }
    
    RestCookieCollection::~RestCookieCollection()
    {
    }
    
    void RestCookieCollection::SetOrUpdateCookie(const RestCookiePtr &cookie)
    {
        RestCookieVPtr cookies {cookie};
        SetOrUpdateCookies(cookies);
    }
    
    void RestCookieCollection::SetOrUpdateCookies(const RestCookieVPtr &cookies)
    {
        BBScopeLock lock(m_mtx);
        
        for (auto newCookie : cookies)
        {
            if (newCookie == nullptr) continue;
            
            auto it = std::find_if(m_cookies.begin(), m_cookies.end(), [&newCookie](const RestCookiePtr &cookie)
            {
                if (cookie == nullptr)  return false;
                
                return cookie->Name == newCookie->Name &&
                       cookie->Domain == newCookie->Domain &&
                       cookie->Path == newCookie->Path;
            });
            
            if (it == m_cookies.end())
            {
                m_cookies.push_back(newCookie);
            }
            else if (*it != nullptr)
            {
                (*it)->Expires = newCookie->Expires;
                (*it)->Value = newCookie->Value;
            }
        }
    }
    
    void RestCookieCollection::SetOrUpdateCookies(const std::string &cookieString)
    {
        //Don't lock here
        auto cookies = CookieUtils::CookiesFromString(cookieString);
        SetOrUpdateCookies(cookies);
    }
    
    void RestCookieCollection::Union(const RestCookieCollectionPtr &restCookieCollection)
    {
        auto cookies = restCookieCollection->GetCookies();
        SetOrUpdateCookies(cookies);
    }
    
    void RestCookieCollection::CleanCookies()
    {
        BBScopeLock lock(m_mtx);
        m_cookies.clear();
    }
    
    bool RestCookieCollection::IsEmpty()
    {
        BBScopeLock lock(m_mtx);
        return m_cookies.empty();
    }
    
    const RestCookieVPtr RestCookieCollection::GetCookies()
    {
        BBScopeLock lock(m_mtx);
        RestCookieVPtr copyCookies;
        for (auto cookie : m_cookies)
        {
            if (cookie == nullptr) continue;
            copyCookies.push_back(std::make_shared<RestCookie>(*cookie));
        }
        
        return copyCookies;
    }
    
    const std::string RestCookieCollection::GetCookiesString(bool encode)
    {
        BBScopeLock lock(m_mtx);
        std::string cookieString = CookieUtils::StringFromCookies(m_cookies);
        
        if (encode)
            return CookieUtils::EncodeCookieValue(cookieString);
        else
            return cookieString;
    }
    
    RestCookieCollectionPtr RestCookieCollection::Clone()
    {
        RestCookieCollectionPtr newCollection(new RestCookieCollection);
        newCollection->CleanCookies();
        newCollection->SetOrUpdateCookies(this->GetCookies());
        return newCollection;
    }
}
