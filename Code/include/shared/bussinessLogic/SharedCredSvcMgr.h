
#ifndef SDKShared_SharedCredSvcMgr_h
#define SDKShared_SharedCredSvcMgr_h

#include "shared/callbacks/SharedCredSvcCallback.h"
#include "core/util/BaseInclude.h"

namespace BBMobileSDK
{
    
    BB_FORWARD_DECLARE(SharedBaseResponse);
   
    BB_FORWARD_DECLARE(SharedCredentials);
    BB_FORWARD_DECLARE(RestResponse);
    BB_FORWARD_DECLARE(RestManager);

    class SharedCredSvcMgr
    {
    public:
        
        SharedCredSvcMgr();
        ~SharedCredSvcMgr();
        
        
        // bool SetMySchool(const SharedInstitutionPtr & institution);
        
        // SharedInstitutionPtr GetMySchool();
        
        // SharedInstitutionPtr GetMySchoolForNotification();
        
       // SharedLoginResponsePtr Login(const std::string & userName, const std::string & password, bool isKeepMeLoggedIn, bool isRenewSession = false, bool isProspective = false);
        
        // SharedLoginResponsePtr FTWLogin(const std::string & userId, const std::string & cookies, bool needCheckUserLicense, bool isKeepMeLoggedIn);
        
        // SharedLicenseRespPtr CheckUserLicense(const std::string & userId);
        
        // SharedLicenseRespPtr CheckUserRole(const std::string & userId, const std::string & cookies);
        
        // SharedLoginResponsePtr SaveUserId(const std::string & userId);
        // bool SaveCookies(const std::string & cookies);
        
        // SharedLoginResponsePtr SaveUserIdAndCookies(const std::string & userId, const std::string & cookies);

        SharedCredentialsPtr GetMyCredentials();

        std::string GetUniqueSchoolIDWithUId();
        
        std::string GetCookies();
        std::string GetEncodedCookiesForServerbaas();
        bool RefreshCookies();
        
        void Logout(bool clearServerSession = true);
        
        bool CleanUserSessionInfo();
        
        void RegisterRequestAuthorizationFailedCallback(sf_callback_RequestAuthorizationFailed callback);
        void UnRegisterRequestAuthorizationFailedCallback();
        
        void RegisterCookieUpdateCallback(UserCookieRefreshedCallback callback);
        void UnRegisterCookieUpdateCallback();
        bool SaveMyCredentials(const SharedCredentialsPtr & credentials);
        std::string GetMySchoolDomain();
        static void GetValuesFromCookie(std::string &sessionId, std::string &expires, std::string &timeout);
    private:
        // SharedKvDAOMgrPtr m_KvDAOMgr;
        // SharedCredRestMgrPtr m_RestMgr;
        //UtilityServiceManagerPtr m_utilityMgr;
        static std::shared_ptr<UserCookieRefreshedCallback> s_userCookieRefreshCallback;
        
        static int MapLoginMinorCodeToResponseCode(int originalResponseCode, int httpStatusCode, int minorCode);
        // SharedLoginResponsePtr SendLoginRequest(const SharedInstitutionPtr &institution,
        //                                         const std::string & userName,
        //                                         const std::string & password,
        //                                         bool isProspective);
        // void BuildLoginResp(SharedLoginResponsePtr & resp,
        //                     const RestResponsePtr & restResp,
        //                     const SharedInstitutionPtr &institution,
        //                     const std::string & userName,
        //                     const std::string & password);
        SharedBaseResponsePtr UpdateUserInfo(const std::string &userId, std::string &userName);
        SharedBaseResponsePtr PostLogin(const std::string & userId, const std::string & cookies);
        
        void HandleUserChange();
    };
    
    GLB_SMART_PTR_DEF(SharedCredSvcMgr)
}

#endif
