//
//  RestCookieCollection.h
//  
//
//  Created 
//  Copyright © 2024
//

#ifndef RestCookieCollection_h
#define RestCookieCollection_h

#include "core/util/TypeDefs.h"

namespace BBMobileSDK {
    
    BB_FORWARD_DECLARE(RestCookie);
    BB_FORWARD_DECLARE(RestCookieCollection);
    
    class RestCookieCollection
    {
    public:
        RestCookieCollection();
        RestCookieCollection(const RestCookieCollection &rhs);
        RestCookieCollection& operator = (const RestCookieCollection &rhs);
        ~RestCookieCollection();
        
        void SetOrUpdateCookie(const RestCookiePtr &cookie);
        void SetOrUpdateCookies(const RestCookieVPtr &cookies);
        void SetOrUpdateCookies(const std::string &cookieString);
        void CleanCookies();
        bool IsEmpty();
        
        const RestCookieVPtr GetCookies();
        const std::string GetCookiesString(bool encode = false);

        RestCookieCollectionPtr Clone();
        void Union(const RestCookieCollectionPtr &restCookieCollection);
        
    private:
        std::mutex m_mtx;
        RestCookieVPtr m_cookies;
    };
}

#endif /* RestCookieCollection_h */
