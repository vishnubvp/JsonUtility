

#ifndef VsboardMobile_RestManager_h
#define VsboardMobile_RestManager_h

#include <map>
#include <string>

#include "core/dispatch/semaphore.h"
#include "core/file/FileObj.h"
#include "core/http/RestResponse.h"
#include "core/util/InternalConstData.h"
#include "core/util/MobileCurlNetwork.h"
#include "shared/callbacks/ProgressMeterCallback.h"
#include "shared/callbacks/SharedCredSvcCallback.h"

namespace VSTestSDK {
    
    BB_FORWARD_DECLARE(UtilityServiceManager);
    BB_FORWARD_DECLARE(SharedCredSvcMgr);
    BB_FORWARD_DECLARE(PathBuilder);
    BB_FORWARD_DECLARE(MobileCurlNetwork);
    
    class RestManager
    {
    public:
    	RestManager();
        RestManager(const std::vector<std::string> & pathList,
                    int connectionTimeout,
                    int readTimeout,
                    const HttpMethod httpMethod = Get,
                    RestConst::PathBuilderType pathBuilderType = RestConst::PathBuilderType::ServerbaasV1);
        
        RestManager(const std::vector<std::string> & pathList,
                    const HttpMethod httpMethod = Get,
                    RestConst::PathBuilderType pathBuilderType = RestConst::PathBuilderType::ServerbaasV1);
        
        RestManager(const std::vector<std::string> & pathList,
                    const HttpMethod httpMethod,
                    const std::string body,
                    RestConst::PathBuilderType pathBuilderType = RestConst::PathBuilderType::ServerbaasV1);
        
        RestManager(const RestManager & rhs);
        
        RestManager& operator = (const RestManager & rhs);
        
        ~RestManager();
        
     public:
        template <typename T>
        void AddQueryParam(const std::string & key, T value) = delete;
        void AddQueryParam(const std::string & key, bool value);
        void AddQueryParam(const std::string & key, const char* value);
        void AddQueryParam(const std::string & key, const std::string & value);
        
        void SetOverrideCookieStr(const std::string & cookie);
        void setBody(const std::string & body);
        void SetAppCommonParams();
        void SetSingleFileObj(FileObjPtr file);
        void SetDownloadPath(const std::string &path);
        void SetDownloadedFileSize(long long downloadedFileSize);
        void SetLastModifiedTimeStamp(long long lastModifiedDate);
        void SetNeedRedirect(bool needRedirect);
        void SetMaxRedirectCount(int maxRedirectCount);
        void SetFullHost(const std::string &fullHost);
        void SetCustomHeader(const RestHeaderFieldVPtr &headers);
        void SetIsLearnApiCall(bool isLearnApiCall);
        RestResponsePtr SendRestRequest();
        RestResponsePtr SendRestRequestWithoutRetry();
        /**
         *  cancel current network request.
         */
        void Abort();
        
        void SetNeedCallback(bool needCallback);
        void RegisterCallbackProgressMeter(sf_callback_progress_meter progressMeter);
        static void RegisterRequestAuthorizationFailedCallback(sf_callback_RequestAuthorizationFailed failedCallback);
        static void UnRegisterRequestAuthorizationFailedCallback();
        
        static std::string GetUserAgentFromConfig();
    protected:
        bool syncWaitForRenew();
        bool renewSession();
        int getConnectionTimeoutInSecond();
        int getReadTimeoutInSecond();
        void RequestFailed(RestResponsePtr &response);

        
    private:
        void InitCurl(int connectionTimeout, int readTimeout);
        RestResponsePtr sendRestRequestWithRetry(const bool withRetry);
        void getCurlResponse(const std::string & fullhost, const std::string & jsonBody, RestResponsePtr &restResponse);
        
        void MergeCustomHeadersToRestHeaders(const RestHeaderFieldVPtr &customHeaders, RestHeaderFieldVPtr &restHeaders);
        void RetryCurlRequest(RestResponsePtr &restResponse, const std::string &url);
        
    private:
        static sf_callback_RequestAuthorizationFailed s_requestAuthFailedCallback;
        static std::mutex s_CallbackMutex;
        
        int m_ConnectionTimeout;
        int m_ReadTimeout;
        
        UtilityServiceManagerPtr m_SdpMgr;
        MobileCurlNetworkPtr m_Curl;
        
        std::vector<std::string> m_PathList;
        
        std::string m_Body;
        HttpMethod m_HttpMethod;
        
        FileObjPtr m_file;
        std::string m_downloadPath;
        // file size of downloaded file, use for resume download.
        long long m_downloadedFileSize;
        long long m_lastModifiedTimeStamp;
        
        sf_callback_progress_meter m_ProgressMeter;
        
        bool m_needCookie;
        bool m_needCallback;
        bool m_needRedirect;
        int m_maxRedirectCount;
        std::string m_fullHost;
        
        std::string m_OverrideCookieStr;
        RestHeaderFieldVPtr m_customHeaders;
        
        PathBuilderPtr m_pathBuilder;
        bool m_isLearnApiCall;
    };
    
}

#endif
