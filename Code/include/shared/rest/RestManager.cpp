
#include "shared/rest/RestManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sstream>

#include "core/config/SharedMobileConfig.h"
#include "core/external/rapidjson/document.h"
#include "core/http/CookieUtils.h"
#include "core/http/PathBuilder.h"
#include "core/http/PathBuilderCreator.h"
#include "core/http/RestCookieCollection.h"
#include "core/http/RestHeaderField.h"
#include "core/notification/NotificationCenter.h"
#include "core/util/BasicUtils.h"
#include "core/util/Helpers.h"
#include "core/util/InternalConstData.h"
#include "core/util/TimeUtils.h"
#include "shared/businessLogic/SdkVersionManager.h"
#include "shared/businessLogic/SharedCredSvcMgr.h"
#include "shared/businessLogic/SharedServiceMgrUtils.h"
#include "shared/businessLogic/UserSessionManager.h"
#include "shared/businessLogic/UtilityServiceManager.h"
#include "shared/const/NotificationNames.h"
#include "shared/rest/RestHeaderManager.h"
#include "shared/rest/RestHelper.h"

namespace VSTestSDK {
    
    std::mutex RestManager::s_CallbackMutex;
    sf_callback_RequestAuthorizationFailed RestManager::s_requestAuthFailedCallback = nullptr;
    
	RestManager::RestManager()
    : m_PathList({})
    , m_Body("")
    , m_OverrideCookieStr("")
    , m_HttpMethod(Get)
    , m_ProgressMeter(nullptr)
    , m_needCallback(true)
    , m_ConnectionTimeout(-1)
    , m_ReadTimeout(-1)
    , m_SdpMgr(new UtilityServiceManager)
    , m_downloadPath("")
    , m_downloadedFileSize(0)
    , m_lastModifiedTimeStamp(LLONG_MAX)
    , m_needRedirect(false)
    , m_maxRedirectCount(RestConst::MAX_REDIRECT_COUNT)
    , m_customHeaders({})
    , m_pathBuilder(PathBuilderCreator::ConstructBuilderByType(RestConst::PathBuilderType::ServerbaasV1, {}))
    , m_isLearnApiCall(false)
	{
    }
    
    RestManager::RestManager(const std::vector<std::string> & pathList,
                             int connectionTimeout,
                             int readTimeout,
                             const HttpMethod httpMethod,
                             RestConst::PathBuilderType pathBuilderType)
    : m_PathList(pathList)
    , m_Body("")
    , m_OverrideCookieStr("")
    , m_HttpMethod(httpMethod)
    , m_ProgressMeter(nullptr)
    , m_needCallback(true)
    , m_ConnectionTimeout(connectionTimeout)
    , m_ReadTimeout(readTimeout)
    , m_SdpMgr(new UtilityServiceManager)
    , m_downloadPath("")
    , m_downloadedFileSize(0)
    , m_lastModifiedTimeStamp(LLONG_MAX)
    , m_needRedirect(false)
    , m_maxRedirectCount(RestConst::MAX_REDIRECT_COUNT)
    , m_customHeaders({})
    , m_pathBuilder(PathBuilderCreator::ConstructBuilderByType(pathBuilderType, pathList))
    , m_isLearnApiCall(false)
    {
    }
    
    RestManager::RestManager(const std::vector<std::string> & pathList, const HttpMethod httpMethod, RestConst::PathBuilderType pathBuilderType)
    : m_PathList(pathList)
    , m_Body("")
    , m_OverrideCookieStr("")
    , m_HttpMethod(httpMethod)
    , m_needCallback(true)
    , m_ProgressMeter(nullptr)
    , m_ConnectionTimeout(-1)
    , m_ReadTimeout(-1)
    , m_SdpMgr(new UtilityServiceManager)
    , m_downloadPath("")
    , m_downloadedFileSize(0)
    , m_lastModifiedTimeStamp(LLONG_MAX)
    , m_needRedirect(false)
    , m_maxRedirectCount(RestConst::MAX_REDIRECT_COUNT)
    , m_customHeaders({})
    , m_pathBuilder(PathBuilderCreator::ConstructBuilderByType(pathBuilderType, pathList))
    , m_isLearnApiCall(false)
	{
    }
    
    RestManager::RestManager(const std::vector<std::string> & pathList,
                             const HttpMethod httpMethod,
                             const std::string body,
                             RestConst::PathBuilderType pathBuilderType)
    : m_PathList(pathList)
    , m_Body(body)
    , m_OverrideCookieStr("")
    , m_HttpMethod(httpMethod)
    , m_needCallback(true)
    , m_ProgressMeter(nullptr)
    , m_ConnectionTimeout(-1)
    , m_ReadTimeout(-1)
    , m_SdpMgr(new UtilityServiceManager)
    , m_downloadPath("")
    , m_downloadedFileSize(0)
    , m_lastModifiedTimeStamp(LLONG_MAX)
    , m_needRedirect(false)
    , m_maxRedirectCount(RestConst::MAX_REDIRECT_COUNT)
    , m_customHeaders({})
    , m_pathBuilder(PathBuilderCreator::ConstructBuilderByType(pathBuilderType, pathList))
    , m_isLearnApiCall(false)
    {
    }
    
    void RestManager::InitCurl(int connectionTimeout, int readTimeout)
    {
        if (-1 == connectionTimeout)
        {
            connectionTimeout = getConnectionTimeoutInSecond();
        }
        
        if (-1 == readTimeout)
        {
            readTimeout = getReadTimeoutInSecond();
        }
        
        m_Curl = MobileCurlNetworkPtr(new MobileCurlNetwork(connectionTimeout, readTimeout));
    }

    
    RestManager::RestManager(const RestManager & rhs)
    {
        *this = rhs;
    }
    
    RestManager& RestManager::operator = (const RestManager & rhs)
    {
        if (&rhs != this)
        {
            m_PathList = rhs.m_PathList;
            m_Body = rhs.m_Body;
            m_OverrideCookieStr = rhs.m_OverrideCookieStr;
            m_HttpMethod = rhs.m_HttpMethod;
            m_needCallback = rhs.m_needCallback;
            m_ProgressMeter = rhs.m_ProgressMeter;
            m_ConnectionTimeout = rhs.m_ConnectionTimeout;
            m_ReadTimeout = rhs.m_ReadTimeout;
            m_SdpMgr = rhs.m_SdpMgr;
            m_Curl = rhs.m_Curl;
            m_downloadPath = rhs.m_downloadPath;
            m_downloadedFileSize = rhs.m_downloadedFileSize;
            m_lastModifiedTimeStamp = rhs.m_lastModifiedTimeStamp;
            m_needRedirect = rhs.m_needRedirect;
            m_maxRedirectCount = rhs.m_maxRedirectCount;
            m_customHeaders = rhs.m_customHeaders;
            m_pathBuilder = rhs.m_pathBuilder;
            m_isLearnApiCall = rhs.m_isLearnApiCall;
        }
        return *this;
    }
    
    RestManager::~RestManager()
    {
    }
    
    void RestManager::SetAppCommonParams()
    {
        if (SharedMobileConfig::m_AppName == SharedAppNames::APPNAME_STU) {
            AddQueryParam(RestConst::PARAM_APP_TYPE, StringUtils::strfval(RestConst::AppTypeStudent));
        } else if (SharedMobileConfig::m_AppName == SharedAppNames::APPNAME_INST) {
            AddQueryParam(RestConst::PARAM_APP_TYPE, StringUtils::strfval(RestConst::AppTypeInstructor));
        }
    }

    void RestManager::AddQueryParam(const std::string & key, bool value)
    {
        m_pathBuilder->AddQueryParam(key, value);
    }
    
    void RestManager::AddQueryParam(const std::string & key, const std::string & value)
    {
        m_pathBuilder->AddQueryParam(key, value);
    }
    
    void RestManager::AddQueryParam(const std::string &key, const char *value)
    {
        this->AddQueryParam(key, std::string(value));
    }
    
    void RestManager::SetSingleFileObj(FileObjPtr file)
    {
        m_file = file;
    }
    
    void RestManager::SetDownloadPath(const std::string &path)
    {
        m_downloadPath = path;
    }
    
    void RestManager::SetDownloadedFileSize(long long downloadedFileSize)
    {
        m_downloadedFileSize = downloadedFileSize;
    }
    
    void RestManager::SetLastModifiedTimeStamp(long long lastModifiedDate)
    {
        m_lastModifiedTimeStamp = lastModifiedDate;
    }
    
    void RestManager::SetNeedRedirect(bool needRedirect)
    {
        m_needRedirect = needRedirect;
    }
    
    void RestManager::SetMaxRedirectCount(int maxRedirectCount)
    {
        m_maxRedirectCount = maxRedirectCount;
    }
    
    void RestManager::SetFullHost(const std::string &fullHost)
    {
        m_fullHost = fullHost;
    }
    
    void RestManager::SetNeedCallback(bool needCallback)
    {
        m_needCallback = needCallback;
    }
    
    void RestManager::RegisterCallbackProgressMeter(sf_callback_progress_meter progressMeter)
    {
        m_ProgressMeter = progressMeter;
    }
    
    void RestManager::SetOverrideCookieStr(const std::string & cookie)
    {
        m_OverrideCookieStr = cookie;
    }
    
    void RestManager::SetCustomHeader(const RestHeaderFieldVPtr &headers)
    {
        m_customHeaders = headers;
    }
    
    void RestManager::setBody(const std::string & body)
    {
        m_Body = body;
    }

    void RestManager::SetIsLearnApiCall(bool learnApiCall)
    {
        m_isLearnApiCall = learnApiCall;
    }
    
    RestResponsePtr RestManager::SendRestRequest()
    {
        return sendRestRequestWithRetry(true);
    }
    
    RestResponsePtr RestManager::SendRestRequestWithoutRetry()
    {
        return sendRestRequestWithRetry(false);
    }
    
    //
    // protected
    //
    bool RestManager::syncWaitForRenew()
    {
        int errRenewTimeout = SessionRenewer::GetInstance().renewingSession_->wait(SessionRenewer::GetInstance().GetRenewSessionTimeout());
        SessionRenewer::GetInstance().renewingSession_->signal();
        return errRenewTimeout == 0;
    }
    
    bool RestManager::renewSession()
    {
        SessionRenewer::GetInstance().sessionNeedRenew_.store(true);
        return SessionRenewer::GetInstance().SyncRenewSession();
    }
    
    
    int RestManager::getConnectionTimeoutInSecond()
    {
        std::string connectTimeoutStr = m_SdpMgr->GetServerDrivenDataByKey(ServerDrivenKey::HTTPOption::CONNECTION_TIMEOUT);
        return StringUtils::ConvertStringToNumeric<int>(connectTimeoutStr);
    }
    
    int RestManager::getReadTimeoutInSecond()
    {
        std::string readTimeoutStr = m_SdpMgr->GetServerDrivenDataByKey(ServerDrivenKey::HTTPOption::TRANSFER_TIMEOUT);
        return StringUtils::ConvertStringToNumeric<int>(readTimeoutStr);
    }
    
    void RestManager::RegisterRequestAuthorizationFailedCallback(sf_callback_RequestAuthorizationFailed failedCallback)
    {
        BBScopeLock lock(s_CallbackMutex);
        
        if (s_requestAuthFailedCallback != nullptr)
        {
            Logger::debug("request fail call back in rest manager is not null, new callback will overwrite it");
        }
        s_requestAuthFailedCallback = failedCallback;
    }
    
    void RestManager::UnRegisterRequestAuthorizationFailedCallback()
    {
        BBScopeLock lock(s_CallbackMutex);
        Logger::debug("unregister request fail call back!");
        
        s_requestAuthFailedCallback = nullptr;
    }
    
    void RestManager::RequestFailed(RestResponsePtr &response)
    {
        if (response == nullptr)
            return;
        
        if (response->httpResponseCode == 401) 
        {
            if (m_needCallback && s_requestAuthFailedCallback != nullptr)
            {
                std::thread callbackThread([]{
                    BBScopeLock lock(s_CallbackMutex);
                    
                    s_requestAuthFailedCallback();
                });
                callbackThread.detach();
            }
        }
    }
    
    std::string RestManager::GetUserAgentFromConfig()
    {
        std::stringstream userAgentStream;
        userAgentStream << "platform/" << SharedMobileConfig::m_DeviceOS << " "
        << "platform_version/" << SharedMobileConfig::m_DeviceOSVesion << " "
        << "carrier_code/" << SharedMobileConfig::m_CarrierCode << " "
        << "carrier_name/" << SharedMobileConfig::m_CarrierName << " "
        << "device_name/" << SharedMobileConfig::m_DeviceModel << " "
        << "device_id/" << SharedMobileConfig::m_DeviceId << " "
        << "sdk_version/" << SDKConstant::Version::SDK_BASIC_VERSION << " "
        << "app_name/" << SharedMobileConfig::m_AppName << " "
        << "app_version/" << SharedMobileConfig::m_AppVersion << " "
        << "timezone/" << SharedMobileConfig::m_Timezone;
        
        std::string rawStr = userAgentStream.str();
        std::string userAgentValue = rawStr;
        return userAgentValue;
    }
    
    RestResponsePtr RestManager::sendRestRequestWithRetry(const bool withRetry)
    {
        if (withRetry) {
            if (!syncWaitForRenew()) {
                RestResponsePtr failResp(new RestResponse);
                failResp->httpResponseCode = 401;
                this->RequestFailed(failResp);
            }
        }
        
        RestResponsePtr restResponse(new RestResponse);
        std::string fullhost = m_fullHost;
        if (fullhost.empty())
        {
            fullhost = m_pathBuilder->GenerateFullPath();
        }
        
        // 1st request
        Logger::debug("json body: " + m_Body);
        getCurlResponse(fullhost, m_Body, restResponse);
        
        // retry for cases: CURLE_COULDNT_RESOLVE_HOST, CURLE_COULDNT_RESOLVE_PROXY, CURLE_COULDNT_CONNECT
        // retry scheme: In CURL_RETRY_TIMEOUT_MILLISEC(e.g. 2 sec), loop to do curl request if still returned the above error codes
//        RetryCurlRequest(restResponse, fullhost);
        bool isRenewSession = false;
        // renew session and retry if succeeded
        if (withRetry && restResponse->httpResponseCode == 401)
        {
            if (renewSession())
            {
                isRenewSession = true;
                NotificationCenter::PostNotification(NotificationNames::USER_COOKIE_REFRESH);
                getCurlResponse(fullhost, m_Body, restResponse);
            }
        }
        
        RestHelper::ReviseRestResponse(restResponse);
        if (isRenewSession && restResponse->httpResponseCode == 401)
        {
            std::string httpMethod = "POST";
            UtilityServiceManager::GetHttpTransactionDetails(restResponse,httpMethod);
            Logger::debug("Still get 401 error after renew session");
            SessionRenewer::GetInstance().Logout();
        }
        
        if (restResponse->httpResponseCode != 200)
        {
            this->RequestFailed(restResponse);
        }
        return restResponse;
    }
     
    static void updateCookiesWithResponse(const RestResponsePtr & curlResponse)
    {
        std::string responseCookies = curlResponse->GetCookiesString();
        if (responseCookies.empty())
            return;
        
        std::string decodedCookies = CookieUtils::DecodeCookieValue(responseCookies);
        
        RestCookieCollectionPtr cookieCollection = UserSessionManager::GetInstance().GetCookies();
        
        if (cookieCollection != nullptr) {
            cookieCollection->SetOrUpdateCookies(decodedCookies);
            std::string newCookieStr = cookieCollection->GetCookiesString();
            UserSessionManager::GetInstance().SetUserCookiesString(newCookieStr);

            SharedCredSvcMgr mgr;
            std::string previousCookies = mgr.GetCookies();
            if (newCookieStr != previousCookies)
                mgr.SaveCookies(newCookieStr);
        }
    }
    
    void RestManager::getCurlResponse(const std::string & fullhost, const std::string & jsonBody, RestResponsePtr & restResponse)
    {
        // need create curl every time send curl request to avoid wrong state in MobileCurlNetwork instance
        InitCurl(m_ConnectionTimeout, m_ReadTimeout);

        int redirectCount = 0;
        bool redirected = false;
        std::string url = fullhost;
        long long requestTime = LLONG_MAX;
        long long responseTime = LLONG_MAX;
        
        do {
            redirected = false;

            RestHeaderFieldVPtr headers = RestHeaderManager::GetInstance().GetHeaders();
            std::string cookieValue = "";
            
            if (!m_OverrideCookieStr.empty())
                cookieValue = m_OverrideCookieStr;
            else
                cookieValue = UserSessionManager::GetInstance().GetCookiesForUrl(url);
            
            auto headerCookie = std::make_shared<RestHeaderField>(RestHeaderKeys::KEY_COOKIE, cookieValue);
            headers.push_back(headerCookie);
            
            if (!m_customHeaders.empty())
            {
                MergeCustomHeadersToRestHeaders(m_customHeaders, headers);
            }
            
            if (nullptr == m_Curl)
            {
                Logger::error("MobileCurlNetwork isn't initialized!");
                restResponse->httpResponseCode = HttpStatusCodeBadRequest;
                restResponse->strErrorMessage = "Instantiate MobileCurlNework failed from SDK side.";
                break;
            }
            
            if (LLONG_MAX != m_lastModifiedTimeStamp)
            {
                m_Curl->SetLastModifiedTimeStamp(m_lastModifiedTimeStamp);
            }
            
            if (m_ProgressMeter) {
                m_Curl->RegisterTransferCallback(m_ProgressMeter);

            }
            requestTime = TimeUtils::GetCurrentMillisecond();
            switch (m_HttpMethod) {
                case Post:
                    restResponse = m_Curl->Post(url, jsonBody, headers);
                    break;
                    
                case PostUsingGzip:
                    restResponse = m_Curl->Post(url, jsonBody, headers, true);
                    break;
                    
                case PostForm:
                    restResponse = m_Curl->PostForm(url, jsonBody, headers);
                    break;
                    
                case Put:
                    restResponse = m_Curl->Put(url, jsonBody, headers);
                    break;
                    
                case Patch:
                    restResponse = m_Curl->Patch(url, jsonBody, headers);
                    break;
                    
                case Delete:
                    restResponse = m_Curl->Delete(url, headers);
                    break;
                    
                case Head:
                    restResponse = m_Curl->Head(url, headers);
                    break;
                    
                case Get:
                    restResponse = m_Curl->Get(url, headers);
                    break;
                    
                case UploadSingleFile:
                    restResponse = m_Curl->UploadSingleFile(url, m_file, headers);
                    break;

                case Download:
                    restResponse = m_Curl->Download(url, m_downloadPath, headers, m_downloadedFileSize);
                    break;
                    
                default:
                    break;
            }
            
            if (restResponse->httpResponseCode == HttpStatusCodeMovedPermanently ||
                restResponse->httpResponseCode == HttpStatusCodeFound ||
                restResponse->httpResponseCode == HttpStatusCodeSeeOther) {
                redirectCount ++;
                redirected = true;
                Logger::debug("redirect: " + StringUtils::strfval(redirectCount));
                url = restResponse->redirectUrl;
            }
            
        } while (redirected &&
                 m_needRedirect &&
                 !url.empty() &&
                 redirectCount < m_maxRedirectCount);
        responseTime = TimeUtils::GetCurrentMillisecond();
        restResponse->requestSentTime = requestTime;
        restResponse->responseReceivedTime = responseTime;
        
        //Restrict updating the cookies when SDK calls direct learn api, To avoid frequent Logout issues in Mobile app
        if(!m_isLearnApiCall)
            updateCookiesWithResponse(restResponse);
    }
    
    void RestManager::MergeCustomHeadersToRestHeaders(const RestHeaderFieldVPtr &customHeaders, RestHeaderFieldVPtr &restHeaders)
    {
        RestHeaderFieldVPtr tmpHeaders = restHeaders;
        for (auto customHeader : customHeaders)
        {
            BasicUtils::EraseIf(tmpHeaders, [customHeader](RestHeaderFieldPtr header){
                return customHeader->GetName() == header->GetName();
            });
        }
        
        tmpHeaders.insert(tmpHeaders.begin(), customHeaders.begin(), customHeaders.end());
        restHeaders = tmpHeaders;
    }
    
    void RestManager::RetryCurlRequest(RestResponsePtr &restResponse, const std::string &url)
    {
        if ((restResponse->curlErrorCode == CURLE_COULDNT_RESOLVE_HOST) ||
            (restResponse->curlErrorCode == CURLE_COULDNT_RESOLVE_PROXY)||
            (restResponse->curlErrorCode == CURLE_COULDNT_CONNECT))
        {
            long long start = TimeUtils::GetCurrentMillisecond();
            bool isContinue = true;
            do {
                // sleep for 200 ms, approximately about 5 retry times within 2 seconds
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                
                getCurlResponse(url, m_Body, restResponse);
                
                if ((restResponse->curlErrorCode != CURLE_COULDNT_RESOLVE_HOST)  &&
                    (restResponse->curlErrorCode != CURLE_COULDNT_RESOLVE_PROXY) &&
                    (restResponse->curlErrorCode != CURLE_COULDNT_CONNECT))
                {
                    isContinue = false;
                }
                
                long long elapsed = TimeUtils::GetCurrentMillisecond() - start;
                if (elapsed >= RestConst::CURL_RETRY_TIMEOUT_MILLISEC)
                {
                    isContinue = false;
                }
            } while(isContinue);
        }
    }
    
    void RestManager::Abort()
    {
        if (nullptr != m_Curl)
        {
            m_Curl->AbortTransfer();
        }
        else
        {
            Logger::error("No initialization for MobileCurlNetwork!");
        }
    }
}

