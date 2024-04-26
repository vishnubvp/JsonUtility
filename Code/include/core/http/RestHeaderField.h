//
//  RestHeaderField.h
//  
//
//  Created 
//  Copyright (c) 20124
//

#ifndef VsboardMobile_RestHeaderField_h
#define VsboardMobile_RestHeaderField_h

#include "core/util/StringUtils.h"

namespace VSTestSDK
{
    
    namespace RestHeaderKeys
    {
        const std::string KEY_USER_AGENT = "User-Agent";
        const std::string KEY_ACCEPT_LANGUAGE = "Accept-Language";
        const std::string KEY_COOKIE = "Cookie";
        const std::string KEY_CONTENT_TYPE = "Content-Type";
        const std::string KEY_CONTENT_ENCODING = "Content-Encoding";
        const std::string KEY_CONTENT_LENGTH = "Content-Length";
        const std::string KEY_LAST_MODIFIED = "Last-Modified";
        const std::string KEY_LAST_MODIFIED_SINCE = "If-Modified-Since";
    }

    class RestHeaderField
    {
    public:
        RestHeaderField();
        RestHeaderField(const std::string & name, const std::string & value);
        RestHeaderField(const RestHeaderField & rhs);
        RestHeaderField& operator = (const RestHeaderField & rhs);
        
        ~RestHeaderField();
        
        static RestHeaderField InstanceFromHeaderString(const std::string & headerString);
        static std::string TrimHeaderString(const std::string & headerStr);
		std::string toString();
    
        inline std::string GetName() const { return Name; }
        inline std::string GetValue() const { return Value; }
    private:
        std::string Name;
        std::string Value;
    };
}

#endif
