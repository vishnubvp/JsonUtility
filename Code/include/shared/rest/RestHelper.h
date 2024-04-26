

#ifndef RESTHELPER_H_
#define RESTHELPER_H_

#include <atomic>
#include <functional>

#include "core/dispatch/semaphore.h"
#include "core/http/RestResponse.h"
#include "core/log/Logger.h"
#include "core/util/SingletonBase.h"
#include "core/util/TypeDefs.h"
#include "shared/businessLogic/SharedServiceMgrUtils.h"

namespace VSTestSDK
{

    BB_FORWARD_DECLARE(LocalRestResponse)
    BB_FORWARD_DECLARE(SharedBaseResponse);
    
	class RestHelper
	{
	public:
        static void ReviseRestResponse(RestResponsePtr &restResponse);

        template <typename ServiceResponse>
        static void MapRestResponseToServiceResponse(const RestResponsePtr &restResponse,
                                                     std::shared_ptr<ServiceResponse> &serviceResponse)
        {
            if (serviceResponse == nullptr)
            {
                serviceResponse = std::make_shared<ServiceResponse>();
            }
            
            if (restResponse == nullptr)
            {
                serviceResponse->SetErrorCode(ResponseCodeUnknwonError);
                return;
            }
            
            auto jsonValid = true;
            if (!restResponse->strContent.empty())
            {
                jsonValid  = SharedServiceMgrUtils::DeserializeJson(restResponse->strContent, serviceResponse);
                if (!jsonValid)
                {
                    Logger::error("Invalid json");
                }
            }
            
            int responseCode = SharedServiceMgrUtils::CalcResponseCodeFromRestResponse(restResponse.get());
            
            serviceResponse->SetErrorCode(responseCode);
            if (responseCode == ResponseCodeOk &&
                !jsonValid)
            {
                serviceResponse->SetErrorCode(ResponseCodeInvalidJson);
            }
            
            serviceResponse->SetOriginalHttpStatusCode(restResponse->httpResponseCode);
            serviceResponse->SetErrorMessage(restResponse->strErrorMessage);
            serviceResponse->SetIsUseErrorMessageFromServer(restResponse->isUseErrorMessageFromServer);
        }
	};
    
    class SessionRenewer
    {
    public:
        static SessionRenewer& GetInstance();
        SessionRenewer();
        bool SyncRenewSession();
        SharedBaseResponsePtr RenewSession();
        SharedBaseResponsePtr Logout();
        std::atomic<bool> sessionNeedRenew_;
        semaphore renewingSession_;
        std::atomic<bool> renewSessionFailed_;
        unsigned long long GetRenewSessionTimeout();
    };
}



#endif /* RESTHELPER_H_ */
