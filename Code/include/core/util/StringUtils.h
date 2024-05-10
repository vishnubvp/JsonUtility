
#ifndef VsboardMobile_StringUtils_h
#define VsboardMobile_StringUtils_h

#include <initializer_list>
#include <string>
#include <type_traits>
#include <vector>

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"

namespace BBMobileSDK {
    
    class StringUtils
    {
    public:
        template<typename value_type = std::string, typename ... Args>
        static bool HasEmpty(Args ... args)
        {
            bool ret = false;
            const value_type paras[] = {args ...};
            for (const value_type &para : paras)
            {
                if (std::is_same<std::string, value_type>::value == true
                    && para.empty())
                {
                    ret = true;
                    break;
                }
            }
            
            return ret;
        };
        
        static std::string CombineStr(const std::string & separator, std::vector<std::string> list, bool separatorAtEnd = true);
        
        static bool EndsWith(const std::string & str1, const std::string & str2);
        
        static std::vector<std::string> Split(const std::string & s, const std::string & spliter);
        
        static int CompareIgnoreCase(const std::string &lhs, const std::string &rhs);
        
        static KVPair KVPairFromStr(const std::string & s, const std::string & spliter);
        
        static std::string StrFromKVPairVector(std::vector<KVPair> & pairs, const std::string & firstSpliter, const std::string & secondSpliter);
        
        static std::vector<KVPair> KVPairsFromStr(const std::string & s, const std::string & firstSpliter, const std::string & secondSpliter);
        
        static std::string LTrim(const std::string & s, const char c);
        static std::string RTrim(const std::string & s, const char c);
        static std::string Trim(const std::string & s, const char c = ' ');
        
        template <typename T>
        static T ConvertStringToNumeric(const std::string & str, T defaultVal = NULL)
        {
            T value = NULL;
            
            std::istringstream stream(str);
            if (!stream)
            {
                return value;
            }
            
            stream >> value;
            
            if (stream.fail())
                value = defaultVal;
            
            return value;
        }
        
        template <typename ValueType>
        static typename std::enable_if<std::is_enum<ValueType>::value, std::string>::type strfval(const ValueType & value)
        {
            return strfval(static_cast<typename std::underlying_type<ValueType>::type>(value));
        }
        
        /**
         * convert value to string
         */
        template <typename ValueType>
        static typename std::enable_if<!std::is_enum<ValueType>::value, std::string>::type strfval(const ValueType & value)
        {
            std::stringstream oss;      // create a stream
            oss << value;               // insert value to stream
            return oss.str();           // return as a string
        }
        
        static std::string UrlEncode(const std::string& str);
        static std::string UrlDecode(const std::string& str);
        
        static std::string UrlEncodeForQueryString(const std::string& str);
        
        
        static unsigned char ToHex(unsigned char x);
        static unsigned char FromHex(unsigned char x);
        
        static int ToUpper(int ch);
        static std::string ToLower(const std::string &str);
        
        static bool StartWithAlpha(const std::string &str);
        
        /**
         * these are the same way to lib `ASIHTTPRequest`
         */
        static bool GzipData(const std::string & str, unsigned char ** dest, unsigned long *len);
        static bool GuzipData(unsigned char * src, unsigned long srcLen, std::string &destStr, unsigned long *pDestLen);
        
        static std::string ReplaceFirst(const std::string & originalStr, const std::string & oldVal, const std::string & newVal);
        static std::string ReplaceFromStr(const std::string & originalStr, const std::string & newVal, const std::string & startStr, const std::string & endStr);
        static int VersionCompare(const std::string &v1, const std::string &v2);

    };
}

#endif

