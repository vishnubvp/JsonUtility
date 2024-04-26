

#include "shared/rest/RestHelper.h"

#include "core/http/RestCookieCollection.h"
#include "core/util/Helpers.h"
#include "core/util/InternalConstData.h"
#include "core/log/Logger.h"
#include "shared/businessLogic/SharedCredSvcMgr.h"
#include "shared/businessLogic/UserSessionManager.h"
#include "shared/businessLogic/UtilityServiceManager.h"
#include "shared/const/SharedConst.h"
#include "shared/daoManager/SqliteResponse.h"
#include "shared/model/credential/SharedCredentials.h"
#include "shared/model/credential/SharedInstitution.h"
#include "shared/model/credential/SharedLoginResponse.h"
#include "shared/model/SharedBaseResponse.h"

namespace VSTestSDK
{
    SessionRenewer::SessionRenewer()
    : renewingSession_(new semaphore_)
    , sessionNeedRenew_(false)
    , renewSessionFailed_(false)
    {}
    
    SessionRenewer& SessionRenewer::GetInstance()
    {
        static SessionRenewer * s_sessionRenewer = new SessionRenewer();
        return *s_sessionRenewer; 
    }
    
    unsigned long long SessionRenewer::GetRenewSessionTimeout()
    {
        using namespace ServerDrivenKey::HTTPOption;
        
        const unsigned long long kMsPerSecond = 1000;
        unsigned long long timeout = SDK_LOGIN_BLOCKING_TIMEOUT_IN_SECOND_DEFAULT * kMsPerSecond;
        
        UtilityServiceManager sdpMgr;
        std::string timeoutStr = sdpMgr.GetServerDrivenDataByKey(SDK_LOGIN_BLOCKING_TIMEOUT_IN_SECOND);
        if (!timeoutStr.empty()) {
            int sdpTimeoutSecond = 0;
            sdpTimeoutSecond = StringUtils::ConvertStringToNumeric<int>(timeoutStr);
            if (sdpTimeoutSecond > 0) {
                timeout = sdpTimeoutSecond * kMsPerSecond;
            }
        }
        return timeout;
    }
    
    bool SessionRenewer::SyncRenewSession()
    {
        Logger::debug("enter sync renew session");
        // TODO do info not always renew session
        Logger::info("before wait: " + StringUtils::strfval(renewingSession_->available_res_count()));
        int errRenewTimeout = renewingSession_->wait(GetRenewSessionTimeout());
        Logger::info("after wait: " + StringUtils::strfval(renewingSession_->available_res_count()));
        
        if (errRenewTimeout) {
            Logger::info("something wrong when renewing session, do not renew again");
            renewingSession_->signal();
            return false;
        }
        
        SharedBaseResponsePtr renewResp(new SharedBaseResponse);
        
        Logger::info("session need renew: " + StringUtils::strfval(sessionNeedRenew_.load()));
        
        if (sessionNeedRenew_.load()) {
            sessionNeedRenew_.store(false);
            renewResp = RenewSession();
            
            renewSessionFailed_.store(renewResp->GetErrorCode() != ResponseCodeOk);
        } else {
            renewResp->SetErrorCode(ResponseCodeOk);
        }
        
        Logger::info("before signal: " + StringUtils::strfval(renewingSession_->available_res_count()));
        renewingSession_->signal();
        Logger::info("after signal: " + StringUtils::strfval(renewingSession_->available_res_count()));

        // retry if successfully renewed session
        if (!renewSessionFailed_.load() && renewResp->GetErrorCode() == ResponseCodeOk)
            return true;
        return false;
    }

	SharedBaseResponsePtr SessionRenewer::RenewSession()
	{
		SharedBaseResponsePtr resp(new SharedBaseResponse());

		SharedCredSvcMgr credentialsServiceMgr;
        
        SharedInstitutionPtr institution = credentialsServiceMgr.GetMySchool();
        
        RestCookieCollectionPtr cookies = UserSessionManager::GetInstance().GetCookies();
        // ForceToWeb, return 401 directly
        if (!institution || institution->GetIsForceWebLogin()) {
            if (!institution)
                Logger::debug("renew failed because empty institution");
            else
                Logger::debug("renew failed because it is force to web school");
            
            resp->SetErrorCode(ResponseCodeNeedAuthorization);
            
            UtilityServiceManager::SendDataToNewRelic(resp,NewRelicTransactionType::NR_SESSION_EXPIRY_LOGOUT);
            if (nullptr != cookies &&
                !cookies->IsEmpty())
            {
                credentialsServiceMgr.Logout();
            }
            
            return resp;
        }

        SharedCredentialsPtr credentials = credentialsServiceMgr.GetMyCredentials();

		if (!credentials || credentials->GetUserName().empty() || credentials->GetPassword().empty()) {
            Logger::debug("renew failed because user name or password is empty");
			resp->SetErrorCode(ResponseCodeNeedAuthorization);
            
            if (nullptr != cookies &&
                !cookies->IsEmpty())
            {
                credentialsServiceMgr.Logout();
            }
            
			return resp;
		}
        
        SharedLoginResponsePtr loginResp = credentialsServiceMgr.Login(credentials->GetUserName(), credentials->GetPassword(), credentials->GetIsKeepMeLoggedIn());
        
        cookies = UserSessionManager::GetInstance().GetCookies();
        if (loginResp->GetErrorCode() != ResponseCodeOk &&
            nullptr != cookies &&
            !cookies->IsEmpty())
        {
            credentialsServiceMgr.Logout();
        }
        
		return loginResp;
	}

    SharedBaseResponsePtr SessionRenewer::Logout()
    {
        SharedBaseResponsePtr resp(new SharedBaseResponse());
        
        SharedCredSvcMgr credentialsServiceMgr;
        
        credentialsServiceMgr.Logout();
        return resp;
    }

     /*static*/
    void RestHelper::ReviseRestResponse(RestResponsePtr &restResponse)
    {
        restResponse->strCookies = restResponse->GetCookiesString();
        restResponse->strHeaders = restResponse->GetHeadersString();
        if(restResponse->httpResponseCode >= 200 && restResponse->httpResponseCode < 400) {
            restResponse->isRequestSuccess = true;
        } else if (restResponse->httpResponseCode == 0) {
            restResponse->isRequestSuccess = false;
        } else {
            restResponse->isRequestSuccess = false;
            
            try {
                rapidjson::Document jsonData;
                jsonData.Parse<RAPIDJSON_DEFAULT_PARSE_FLAG>(restResponse->strContent.c_str());
                
                //Check to make sure that we got a response from host
                if(jsonData.HasParseError() || jsonData.IsNull()) {
                    Logger::error("Failed to Parse JSON");
                    restResponse->strErrorMessage = "Failed to Parse JSON";
                } else if (!jsonData.IsNull()) {
                    restResponse->errorCode = Helpers::CheckIntegerValue(jsonData, "code");
                    restResponse->strErrorMessage = Helpers::CheckStringValue(jsonData, "message");
                    restResponse->isUseErrorMessageFromServer = Helpers::CheckBooleanValue(jsonData, "isMessageForDevice");
                }
            } catch (...) {
                Logger::error("Failed to Parse JSON");
            }
        }
    }
}
