

#ifndef _BBMobileSDK_SharedBaseResponse_H
#define _BBMobileSDK_SharedBaseResponse_H

#include <memory>
#include <string>
#include <vector>

#include "core/external/rapidjson/document.h"
#include "core/external/rapidjson/stringbuffer.h"
#include "core/external/rapidjson/writer.h"
#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"


namespace BBMobileSDK
{
    class SharedBaseResponse;
    GLB_SMART_PTR_DEF(SharedBaseResponse)
    GLB_SMART_VEC_PTR_DEF(SharedBaseResponse)

    class SharedBaseResponse 
    {
    public:
        SharedBaseResponse();
        SharedBaseResponse(int originalHttpStatusCode, int errorCode, int code, bool isUseErrorMessageFromServer, long long cacheUpdateTime, const std::string &errorMessage, bool isCacheValid);
        virtual ~SharedBaseResponse();
        SharedBaseResponse(const SharedBaseResponse &rhs);
        SharedBaseResponse& operator = (const SharedBaseResponse &rhs);
        

        void SetOriginalHttpStatusCode(int originalHttpStatusCode);
        int GetOriginalHttpStatusCode(void);

        void SetErrorCode(int errorCode);
        int GetErrorCode(void);

        void SetCode(int code);
        int GetCode(void);

        void SetIsUseErrorMessageFromServer(bool isUseErrorMessageFromServer);
        bool GetIsUseErrorMessageFromServer(void);

        void SetCacheUpdateTime(long long cacheUpdateTime);
        long long GetCacheUpdateTime(void);

        void SetErrorMessage(const std::string &errorMessage);
        std::string GetErrorMessage(void);

        void SetIsCacheValid(bool isCacheValid);
        bool GetIsCacheValid(void);


        virtual void FromJson(rapidjson::Value &json);
        virtual void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer);
        virtual void ToJsonWithoutObject(rapidjson::Writer<rapidjson::StringBuffer> &writer);
        
        std::string ToJsonString();
        
        void CopyBaseResponse(const SharedBaseResponse &other);
        void CopyBaseResponse(const SharedBaseResponsePtr &other);

        
    private: // public:
        int m_OriginalHttpStatusCode; 
        int m_ErrorCode; //see \ref BBMResponseCode for error code definitions
        int m_Code; //code is minor error code return by Serverbaas, currently only used by sdk
        bool m_IsUseErrorMessageFromServer; 
        long long m_CacheUpdateTime; 
        std::string m_ErrorMessage; 
        bool m_IsCacheValid;
    };

}

#endif // _BBMobileSDK_SharedBaseResponse_H
