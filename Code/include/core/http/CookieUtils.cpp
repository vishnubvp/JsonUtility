

#include "core/http/CookieUtils.h"

#include "core/http/RestCookie.h"
#include "core/util/StringUtils.h"

namespace BBMobileSDK
{

    const std::string CookieUtils::StringFromCookies(const RestCookieVPtr &cookies)
    {
        std::stringstream cookieStream;
        for (auto cookie : cookies)
        {
            if (cookie == nullptr) continue;
            
            cookieStream << cookie->Name << "=" << cookie->Value << ";";
        }
        return cookieStream.str();
    }
    
    const RestCookieVPtr CookieUtils::CookiesFromString(const std::string &cookiesString)
    {
        RestCookieVPtr cookies;
        if (cookiesString.empty())
            return cookies;
        
        cookies.reserve(100);
        std::vector<KVPair> cookiePairs = StringUtils::KVPairsFromStr(cookiesString, ";", "=");
        for (KVPair cookiePair : cookiePairs) {
            if (cookiePair.first.empty())
                continue;
            
            auto cookie = std::make_shared<RestCookie>(cookiePair.first, cookiePair.second);
            cookies.push_back(cookie);
        }
        return cookies;
    }
    
    void CookieUtils::URLEncodeCookie(RestCookieVPtr & cookies, bool encode)
    {
        for (auto & cookie : cookies)
        {
            if (cookie == nullptr) return;
            
            if (encode)
                cookie->Value = StringUtils::UrlEncode(cookie->Value);
            else
                cookie->Value = StringUtils::UrlDecode(cookie->Value);
        }
    }
    
    std::string CookieUtils::URLEncodeCookie(const std::string & cookies, bool encode)
    {
        std::vector<KVPair> cookiePairs;
        ParseCookies(cookies, cookiePairs);
        
        for (int i = 0; i < cookiePairs.size(); i++) {
            std::string cookieValue = cookiePairs[i].second;
            if (encode)
                cookiePairs[i].second = StringUtils::UrlEncode(cookieValue);
            else
                cookiePairs[i].second = StringUtils::UrlDecode(cookieValue);
        }
        
        std::string encoededCookies = StringUtils::StrFromKVPairVector(cookiePairs, ";", "=");
        return encoededCookies;
    }
    
    void CookieUtils::EncodeCookieValue(RestCookieVPtr &cookies)
    {
        return URLEncodeCookie(cookies, true);
    }

    void CookieUtils::DecodeCookieValue(RestCookieVPtr &cookies)
    {
        return URLEncodeCookie(cookies, false);
    }
    
    std::string CookieUtils::EncodeCookieValue(const std::string & cookies)
    {
        return URLEncodeCookie(cookies, true);
    }
    
    std::string CookieUtils::DecodeCookieValue(const std::string & cookies)
    {
        return URLEncodeCookie(cookies, false);
    }
    
    // r1 hot fix, by Martyn Ye
    void CookieUtils::ParseCookies(const std::string & input, std::vector<KVPair> & kvPairs)
    {
        std::string tmpinput = input;
        
        std::set<std::string> excludeSet;
        excludeSet.insert("domain");
        excludeSet.insert("path");
        excludeSet.insert("expires");
        excludeSet.insert("secure");
        excludeSet.insert("httponly");
        excludeSet.insert("version");
        excludeSet.insert("comment");
        excludeSet.insert("max-age");
        excludeSet.insert("discard");
        
        
        while (tmpinput.length() > 0)
        {
            if (tmpinput[tmpinput.length()-1] - ';')
            {
                tmpinput.append(";");
            }
            
            size_t equalPos = tmpinput.find("=");
            if (equalPos != std::string::npos)
            {
                std::string keyStr = tmpinput.substr(0, equalPos);
                
                
                while (keyStr.find_first_of(",;$") != std::string::npos)
                {
                    size_t pos = keyStr.find_first_of(",;$");
                    keyStr.erase(0, pos+1);
                }
                
                std::string tmpKey;
                
                // remove left & right space
                keyStr = StringUtils::Trim(keyStr);
                
                tmpKey.resize(keyStr.length());
                
                std::transform(keyStr.begin(), keyStr.end(), tmpKey.begin(), ::tolower);
                
                size_t divPos = tmpinput.find(";", equalPos);
                size_t commaPos = tmpinput.find(",", equalPos);
                
                std::string valStr;
                valStr= tmpinput.substr(equalPos+1, divPos-equalPos-1);
                
                // if there are double quote, need to update the semi-colon pos
                size_t quoatPos = tmpinput.find("\"", equalPos);
                if (quoatPos != std::string::npos && quoatPos < divPos)
                {
                    // in case it contains \" in the value string
                    while (tmpinput.find("\\\"", quoatPos) != std::string::npos)
                    {
                        quoatPos = tmpinput.find("\\\"", quoatPos);
                        quoatPos +=2;
                    }
                    
                    if (tmpinput.find("\"", quoatPos) != std::string::npos)
                    {
                        // renew divPos
                        divPos = tmpinput.find("\"", quoatPos+1);
                        valStr= tmpinput.substr(equalPos+1, divPos-equalPos);
                    }
                    else
                    {
                        // this is a invalid string because the double quote not in pair
                        return;
                    }
                }
                
                if (excludeSet.find(tmpKey) == excludeSet.end())
                {
                    
                    valStr = StringUtils::Trim(valStr);
                    
                    KVPair cookiePair(keyStr, valStr);
                    kvPairs.push_back(cookiePair);
                    
                    tmpinput.erase(0, divPos+1);
                }
                else
                {
                    
                    if (divPos == std::string::npos && commaPos == std::string::npos)
                    {
                        return;
                    }
                    tmpinput.erase(0, divPos < commaPos ? divPos+1 : commaPos+1);
                    equalPos = tmpinput.find_first_of("=");
                    divPos = tmpinput.find_first_of(";");
                    if (divPos < equalPos)
                    {
                        tmpinput.erase(0, divPos+1);
                    }
                }
                
            }
            else
            {
                break;
            }
            
        }
    }
    
}
