//
//  LocalRestResponse.cpp
//  TDKUtils
//
//  Created b
//  Copyright (c) 2024 .
//


#include "core/http/RestResponse.h"

#include "core/http/CookieUtils.h"

namespace VSTestSDK
{
    void RestResponse::Initialization()
    {
        m_Cookies.reserve(100);
        m_Headers.reserve(100);
    }
    
    RestResponse::RestResponse()
    : isRequestSuccess(false)
    , httpResponseCode(0)
    , errorCode(0)
    , curlErrorCode(0)
    , isUseErrorMessageFromServer(false)
    , requestSentTime(LLONG_MAX)
    , responseReceivedTime(LLONG_MAX)
    , strUserId("")
    , strErrorMessage("")
    , strContent("")
    , redirectUrl("")
    , strCookies("")
    , strHeaders("")
    {
        Initialization();
    }
    
    RestResponse::RestResponse(int httpResponseCode,
                               const std::string & content,
                               const std::string & cookies)
    : isRequestSuccess(false)
    , httpResponseCode(httpResponseCode)
    , errorCode(0)
    , curlErrorCode(0)
    , isUseErrorMessageFromServer(false)
    , requestSentTime(LLONG_MAX)
    , responseReceivedTime(LLONG_MAX)
    , strUserId("") 
    , strErrorMessage("")
    , strContent(content)
    , redirectUrl("")
    , strCookies(cookies)
    , strHeaders("")
    {
        Initialization();
    }
    
    RestResponse::RestResponse(bool isRequestSuccess,
                               int  httpResponseCode,
                               int  errorCode,
                               bool isUseErrorMessageFromServer,
                               int  curlErrorCode,
                               long long requestSentTime,
                               long long responseReceivedTime,
                               const std::string & userId,
                               const std::string & errorMessage,
                               const std::string & content,
                               const std::string & cookies,
                               const std::string & headers)
    : isRequestSuccess(isRequestSuccess)
    , httpResponseCode(httpResponseCode)
    , errorCode(errorCode)
    , curlErrorCode(curlErrorCode)
    , isUseErrorMessageFromServer(isUseErrorMessageFromServer)
    , requestSentTime(requestSentTime)
    , responseReceivedTime(responseReceivedTime)
    , strUserId(userId)
    , strErrorMessage(errorMessage)
    , strContent(content)
    , redirectUrl("")
    , strCookies(cookies)
    , strHeaders(headers)
    {
        Initialization();
        
        std::vector<KVPair> cookiePairs = StringUtils::KVPairsFromStr(cookies, ";", "=");
        for (KVPair cookiePair : cookiePairs)
        {
            m_Cookies.push_back(std::make_shared<RestCookie>(cookiePair.first, cookiePair.second));
        }
        
        std::vector<KVPair> headerPairs = StringUtils::KVPairsFromStr(headers, " ", "/");
        for (KVPair headerPair : headerPairs)
        {
            RestHeaderField header(headerPair.first, headerPair.second);
            m_Headers.push_back(header);
        }
    }
    
    RestResponse::RestResponse(int errorCode,
                               const std::string & content,
                               const std::vector<RestHeaderField> & headers,
                               const RestCookieVPtr & cookies)
    : isRequestSuccess(false)
    , httpResponseCode(0)
    , errorCode(errorCode)
    , curlErrorCode(0)
    , isUseErrorMessageFromServer(false)
    , requestSentTime(LLONG_MAX)
    , responseReceivedTime(LLONG_MAX)
    , strUserId("")
    , strErrorMessage("")
    , strContent(content)
    , redirectUrl("")
    , m_Headers(headers)
    , m_Cookies(cookies)
    {
        Initialization();
    }
    
    const std::string RestResponse::GetCookiesString()
    {
        return CookieUtils::StringFromCookies(m_Cookies);
    }
    
    const std::string RestResponse::GetHeadersString()
    {
        std::string strHeaders = "";
        for (RestHeaderField header : m_Headers)
        {
            strHeaders += header.GetName() + "/" + header.GetValue() + " ";
        }
        return strHeaders;
    }
}
