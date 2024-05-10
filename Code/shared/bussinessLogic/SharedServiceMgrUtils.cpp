

#include "shared/businessLogic/SharedServiceMgrUtils.h"

#include "curl.h"
#include "float.h"
#include "sqlite3.h"

#include "core/config/SharedMobileConfig.h"
#include "core/util/Helpers.h"
#include "core/log/Logger.h"
#include "core/util/StringUtils.h"
#include "core/util/TimeUtils.h"
#include "shared/businessLogic/UtilityServiceManager.h"
#include "shared/const/SharedConst.h"
#include "shared/const/SharedInternalConst.h"
#include "shared/daoManager/SqliteResponse.h"
#include "shared/rest/RestHelper.h"


namespace BBMobileSDK
{
    bool SharedServiceMgrUtils::IsNeedCallRest(bool isMandatory, long long cacheUpdateTime)
    {
        if (!SharedMobileConfig::m_EnableCachingLogic)
        {
            return true;
        }
        int mandatoryThreshold = TimeConst::SECONDS_MANDATORY_THRESHOLD;
        std::string sdpMandatoryThreshold = UtilityServiceManager::GetServerDrivenDataByKey("MANDATORY_REST_CALL_MIN_INTERVAL_IN_SECOND");
        if (!sdpMandatoryThreshold.empty())
        {
            mandatoryThreshold = StringUtils::ConvertStringToNumeric<int>(sdpMandatoryThreshold);
        }
        
        int refreshThreshold = TimeConst::SECONDS_REFRESH_THRESHOLD;
        std::string sdpRefreshThreshold = UtilityServiceManager::GetServerDrivenDataByKey("REST_CALL_MAX_INTERVAL_IN_SECOND");
        if (!sdpRefreshThreshold.empty())
        {
            refreshThreshold = StringUtils::ConvertStringToNumeric<int>(sdpRefreshThreshold);
        }
        
        long long currentTime = TimeUtils::GetCurrentMillisecond();
        long long interval = (currentTime - cacheUpdateTime)/TimeConst::MILLISEC_PER_SEC;
        if (interval < mandatoryThreshold)
        {
            return false;
        }
        if (interval < refreshThreshold)
        {
            return isMandatory;
        }
        return true;
    }
    
    int SharedServiceMgrUtils::CalcResponseCodeFromRestResponse(const RestResponse* restResponse)
    {
        if (restResponse == nullptr)
        {
            return ResponseCodeUnknwonError;
        }
        
        int responseCode = INT_MAX;
        responseCode = MapCurlCodeToResponseCode(restResponse->curlErrorCode, responseCode);
        if (responseCode == INT_MAX)    //if something wrong in curl, no further process needed
        {
            responseCode = MapHttpCodeToResponseCode(restResponse->httpResponseCode, responseCode);
            responseCode = MapMinorCodeToResponseCode(restResponse->httpResponseCode, restResponse->errorCode, responseCode);
        }
        
        return responseCode;
    }
    
    int SharedServiceMgrUtils::MapCurlCodeToResponseCode(int curlCode, int originalResponseCode)
    {
        if (curlCode == CURLE_OK ||
            originalResponseCode != INT_MAX)
        {
            return originalResponseCode;
        }
        
        switch (curlCode)
        {
            case CURLE_RANGE_ERROR:
            case CURLE_OPERATION_TIMEDOUT: 
                return ResponseCodeServerError;
            case CURLE_PARTIAL_FILE:
                return ResponseCodeCurlPartialFileError;
            case CURLE_WRITE_ERROR:
                return ResponseCodeCurlWriteError;
            case CURLE_COULDNT_RESOLVE_HOST:
                return ResponseCodeCouldNotResolveHostName;
            case CURLE_COULDNT_CONNECT:
                return ResponseCodeCouldNotConnectToServer;
            default:
                return ResponseCodeNetworkError;
        }
    }
    
    int SharedServiceMgrUtils::MapHttpCodeToResponseCode(int httpCode, int originalResponseCode)
    {
        if (originalResponseCode != INT_MAX)    return originalResponseCode;
        
        if (httpCode == HttpStatusCodeNotConnectedToServer)
            return ResponseCodeNetworkError;
        if (httpCode >= HttpStatusCodeOk && httpCode < HttpStatusCodeBadRequest)
            return ResponseCodeOk;
        if (httpCode == HttpStatusCodeUnauthorized)
            return ResponseCodeNeedAuthorization;
        if (httpCode == HttpStatusCodeForbidden)
            return ResponseCodeForbidden;
        if (httpCode == HttpStatusCodeLocked)
            return ResponseCodeCourseCompleted;
        if (httpCode == HttpStatusCodeRequestEntityTooLarge)
            return ResponseCodeEntityTooLarge;
        if (httpCode == HttpStatusCodeNotFound)
            return ResponseCodeResourceNotFound;
        if (httpCode >= HttpStatusCodeBadRequest && httpCode < HttpStatusCodeInternalServerError)
            return ResponseCodeRequestError;
        if (httpCode >= HttpStatusCodeInternalServerError)
            return ResponseCodeServerError;
        
        return ResponseCodeUnknwonError;
    }
    
    int SharedServiceMgrUtils::MapMinorCodeToResponseCode(int httpCode, int minorCode, int originalResponseCode)
    {
        if (minorCode == 0)   return originalResponseCode;
        
        if (httpCode == HttpStatusCodeForbidden)
        {
            switch (minorCode)
            {
                case ServerMinorCodeB2NotSupportBbInstructor:               return ResponseCodeB2NotSupportBbInstructor;
                case ServerMinorCodeB2NotSupportVsboard:                 return ResponseCodeB2NotSupportVsboard;
                case ServerMinorCodeCredentialInvalidLicense:               return ResponseCodeInvalidLicense;
                case ServerMinorCodeCredentialInvalidRole:                  return ResponseCodeInvalidRole;
                case ServerMinorCodeDiscussionForumUnavailable:             return ResponseCodeDiscussionForumUnavailable;
                case ServerMinorCodeDiscussionForumDeleted:                 return ResponseCodeDiscussionForumDeleted;
                case ServerMinorCodeDiscussionThreadDeleted:                return ResponseCodeDiscussionThreadDeleted;
                case ServerMinorCodeDiscussionThreadUnavailable:            return ResponseCodeDiscussionThreadUnavailable;
                case ServerMinorCodeLearnVersionNotSupportEntitlementCheck: return ResponseCodeLearnNotSupportEntitlementCheck;
                case ServerMinorCodeAppVersionTooLowToGrade:                return ResponseCodeAppVersionTooLowToGrade;
                case ServerMinorCodeTestBadPassword:                        return ResponseCodeTestAssignmentPasswordError;
                default:
                    break;  
            }
        }
        else if (httpCode == HttpStatusCodeInternalServerError)
        {
            switch (minorCode)
            {
                case ServerMinorCodeSchoolUnavailable:  return ResponseCodeSchoolUnavailable;
                default:
                    break;
            }
        }
        else if (httpCode == HttpStatusCodeBadGateway)
        {
            switch (minorCode)
            {
                case ServerMinorCodeB2Unavailable:  return ResponseCodeB2Unavailable;

                default:
                    break;
            }
        }
        // Apt
        else if (httpCode == HttpStatusCodeBadRequest)
        {
            switch (minorCode)
            {
                case ServerMinorErrorCodeExceedCreditsLimitation:   return ResponseCodeExceedCreditsLimitationError;
                case ServerMinorErrorCodeAlreadyExistInTrem:        return ResponseCodeCourseAlreadyExistInTermError;
                case ServerMinorErrorCodeNotExistInTrem:            return ResponseCodeCourseNotExistInTermError;
                case ServerMinorErrorCodeNoEnoughTerms:             return ResponseCodeNoEnoughTermsError;
                case ServerMinorErrorCodeMessageNotFound:           return ResponseCodeMessageNotFound;
                case ServerMinorErrorCodeCourseNotAccessible:       return ResponseCodeCourseNotAccessible;
                default:
                    break;
            }
        }
        
        Logger::error("minor code may be not mapping correctly! httpCode = " + StringUtils::strfval(httpCode) +
                      " minor code = " + StringUtils::strfval(minorCode));
        return originalResponseCode;
    }
    
    std::string SharedServiceMgrUtils::ExtractStableUrl(const std::string& url)
    {
        static std::string sKeyword4TimeStamp = "timestamp";
        static std::string sKeyword4Hash = "hash";
        std::vector<KVPair> urlPairs = StringUtils::KVPairsFromStr(url, "&", "=");
        for (auto iter = urlPairs.begin(); iter != urlPairs.end(); )
        {
            if (iter->first == sKeyword4TimeStamp ||
                iter->first == sKeyword4Hash)
            {
                iter = urlPairs.erase(iter);
            }
            else
            {
                iter++;
            }
        }
        
        return StringUtils::StrFromKVPairVector(urlPairs, "&", "=");
    }
}
