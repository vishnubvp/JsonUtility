

#ifndef _BBMobileSDK_SharedCredentials_H
#define _BBMobileSDK_SharedCredentials_H

#include <vector>
#include <string>
#include <memory>

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"
#include "core/external/rapidjson/document.h"
#include "core/external/rapidjson/stringbuffer.h"
#include "core/external/rapidjson/writer.h"



namespace BBMobileSDK
{
    class SharedCredentials;
    GLB_SMART_PTR_DEF(SharedCredentials)
    GLB_SMART_VEC_PTR_DEF(SharedCredentials)
    
    BB_FORWARD_DECLARE(RestCookieCollection)

    class SharedCredentials 
    {
    public:
        SharedCredentials();
        SharedCredentials(const std::string &userName, const std::string &password, const std::string &userId, const std::string &schoolId, const std::string &schoolName, const std::string &cookies, long long lastLoginTime, bool isKeepMeLoggedIn, bool isLoggedIn, bool isProspectiveStudent, const std::string &siteId, const std::string &xsrfToken);
        virtual ~SharedCredentials();
        SharedCredentials(const SharedCredentials &rhs);
        SharedCredentials& operator = (const SharedCredentials &rhs);
        

        void SetUserName(const std::string &userName);
        std::string GetUserName(void);

        void SetPassword(const std::string &password);
        std::string GetPassword(void);

        void SetUserId(const std::string &userId);
        std::string GetUserId(void);

        void SetSchoolId(const std::string &schoolId);
        std::string GetSchoolId(void);

        void SetSchoolName(const std::string &schoolName);
        std::string GetSchoolName(void);

        RestCookieCollectionPtr GetUserCookieCollection(void);
        
        void SetCookies(const std::string &cookies);
        std::string GetCookies(void);
        std::string GetEncodedCookies(void);

        void SetLastLoginTime(long long lastLoginTime);
        long long GetLastLoginTime(void);

        void SetIsKeepMeLoggedIn(bool isKeepMeLoggedIn);
        bool GetIsKeepMeLoggedIn(void);

        void SetIsLoggedIn(bool isLoggedIn);
        bool GetIsLoggedIn(void);
        
        void SetIsProspectiveStudent(bool isProspectiveStudent);
        bool GetIsProspectiveStudent(void);

        void SetSiteId(const std::string &siteId);
        std::string GetSiteId(void);

        void SetXsrfToken(const std::string &xsrfToken);
        std::string GetXsrfToken(void);

        virtual void FromJson(rapidjson::Value &json);
        virtual void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer);
        virtual void ToJsonWithoutObject(rapidjson::Writer<rapidjson::StringBuffer> &writer);
        
        std::string ToJsonString();

        
    private: // public:
        std::string m_UserName; 
        std::string m_Password; 
        std::string m_UserId; 
        std::string m_SchoolId; 
        std::string m_SchoolName; 
        long long m_LastLoginTime;
        bool m_IsKeepMeLoggedIn; 
        bool m_IsLoggedIn;
        bool m_IsProspectiveStudent;
        RestCookieCollectionPtr m_userCookies;
        std::string m_SiteId;
        std::string m_XsrfToken;
    };

}

#endif // _BBMobileSDK_SharedCredentials_H
