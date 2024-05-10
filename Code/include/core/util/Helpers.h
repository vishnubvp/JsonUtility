

#ifndef VsboardMobile_Helpers_h
#define VsboardMobile_Helpers_h

#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

#include "core/external/rapidjson/document.h"
#include "core/external/rapidjson/writer.h"
#include "core/external/rapidjson/stringbuffer.h"

namespace BBMobileSDK
{
    /**
     *  Helpers class that contains methods to do some utility function such as checking value in JSON, encoding/decoding URL's
     */
    class Helpers {
    public:
        /**
         *  Check the String value of a JSON element from a RapidJSON Document Value object. If the key does not exist in the Value object, a zero length String is returned
         *
         *  @param item RapidJSON::Value object that contains a JSON element
         *  @param key  String key to check the Value object if it exists
         *
         *  @return String value based on key/value pair or zero length String if not found
         */
        static std::string CheckStringValue(rapidjson::Value& item, std::string key);
        /**
         *  Check the Boolean value of a JSON element from a RapidJSON Document Value object. If the key does not exist in the Value object, false is returned
         *
         *  @param item RapidJSON::Value object that contains a JSON element
         *  @param key  String key to check the Value object if it exists
         *
         *  @return Boolean value based on key/value pair or false if not found
         */
        static bool CheckBooleanValue(rapidjson::Value& item, std::string key);
        /**
         *  Check the Integer value of a JSON element from a RapidJSON Document Value object. If the key does not exist in the Value object, INT_MAX is returned
         *
         *  @param item RapidJSON::Value object that contains a JSON element
         *  @param key  String key to check the Value object if it exists
         *
         *  @return Integer value based on key/value pair or zero if not found
         */
        static int CheckIntegerValue(rapidjson::Value& item, std::string key);
        /**
         *  Check the Double value of a JSON element from a RapidJSON Document Value object. If the key does not exist in the Value object, zero is returned
         *
         *  @param item RapidJSON::Value object that contains a JSON element
         *  @param key  String key to check the Value object if it exists
         *
         *  @return Double value based on key/value pair or zero if not found
         */
        static double CheckDoubleValue(rapidjson::Value& item, std::string key) ;
        /**
         *  Check the long long value of a JSON element from a RapidJSON Document Value object. If the key does not exist in the Value object, LLONG_MAX is returned
         *
         *  @param item RapidJSON::Value object that contains a JSON element
         *  @param key  String key to check the Value object if it exists
         *
         *  @return Double value based on key/value pair or zero if not found
         */
        static long long CheckInt64Value(rapidjson::Value& item, std::string key);

        static std::shared_ptr<rapidjson::Value> ValueFromString(const std::string & jsonString);

        static std::string ToStringFromValue(const std::shared_ptr<rapidjson::Value> & value);

        static std::string ToStringFromValue(const rapidjson::Value & value);

        // TODO: overload function for support more key/value types
        static void JsonFromKVMap(const std::map<std::string, std::string> &keyValueMap, rapidjson::Writer<rapidjson::StringBuffer> &writer);
        static void JsonFromKVMap(const std::map<std::string, bool> &keyValueMap, rapidjson::Writer<rapidjson::StringBuffer> &writer);

        static bool DeserializeMapJson(const std::string &content, std::map<std::string, std::string> &keyValueMap);
        static bool DeserializeMapJson(const std::string &content, std::map<std::string, bool> &keyValueMap);

        static void KVMapFromJson(std::map<std::string, std::string> &keyValueMap, rapidjson::Value &jsonData);
        static void KVMapFromJson(std::map<std::string, bool> &keyValueMap, rapidjson::Value &jsonData);
        
        static bool CheckIfJSonValueExist(const std::string & rawJSonStr, const std::string & key, const std::string & expectedValue);

        static double Round(double data, int prec = 1);

        static void DomFromStr(rapidjson::Document & dom, const std::string & jsonString);

        static std::string StrFromDom(const rapidjson::Value & value);
        
        static bool IsInvalidItem(const rapidjson::Value& item, const std::string &key);
    };
}
#endif
