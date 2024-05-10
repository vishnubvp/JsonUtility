

#ifndef TDKUtils_LocalRestResponse_h
#define TDKUtils_LocalRestResponse_h

#include <string>
#include <vector>

#include "core/util/BaseInclude.h"
#include "core/util/StringUtils.h"
#include "core/util/TypeDefs.h"
#include "core/http//RestHeaderField.h"
#include "core/http//RestCookie.h"

namespace BBMobileSDK
{
    BB_FORWARD_DECLARE(RestResponse);
    
    class RestResponse
    {
    public:
        
        RestResponse();
        
        RestResponse(int   httpResponseCode,
                     const std::string & content,
                     const std::string & cookies = "");
        
        RestResponse(bool  isRequestSuccess,
                     int   httpResponseCode,
                     int   errorCode,
                     bool  isUseErrorMessageFromServer,
                     int   curlErrorCode,
                     long long requestSentTime,
                     long long responseReceivedTime,
                     const std::string & userId,
                     const std::string & errorMessage,
                     const std::string & content = "",
                     const std::string & cookies = "",
                     const std::string & headers = "");
        
        RestResponse(int   errorCode,
                     const std::string & content,
                     const std::vector<RestHeaderField> & headers,
                     const RestCookieVPtr & cookies);
        
        ~RestResponse() {}
        
        bool isRequestSuccess;
        int  httpResponseCode;
        int  errorCode;            // the error code parsed from Serverbaas response when the http code = [400, 500)
        int  curlErrorCode;        // store the curl failed detail code for further debugging and usage
        bool isUseErrorMessageFromServer;
        long long requestSentTime;
        long long responseReceivedTime;
        
        std::string strUserId;
        std::string strErrorMessage;
        std::string strContent;
        std::string redirectUrl;
        
        std::string strCookies;
        std::string strHeaders;
        std::vector<RestHeaderField> m_Headers;
        RestCookieVPtr m_Cookies;
        
        const std::string GetCookiesString();
        const std::string GetHeadersString();
        
    private:
        void Initialization();
    };
}


#endif
