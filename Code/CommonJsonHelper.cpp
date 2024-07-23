/**
 *Copyright © 2017 HelloWorld. All rights reserved.
 *
 * @file    CommonJsonHelper.cpp
 * @author  Yi Zheng
 * @brief   
 *
 */

#include "shared/util/CommonJsonHelper.h"

#include "core/util/StringUtils.h"

namespace BBMobileSDK
{
    namespace JsonHelper
    {
        template<>
        void FromJson(int& intVal, rapidjson::Value &jsonItem)
        {
            const int DEFAULT_INT = INT_MAX;
            if (jsonItem.IsNull())
            {
                intVal = DEFAULT_INT;
            }
            else if (jsonItem.IsString())
            {
                auto intString = jsonItem.GetString();
                intVal = StringUtils::ConvertStringToNumeric(intString, DEFAULT_INT);
            }
            else if (jsonItem.IsNumber())
            {
                intVal = jsonItem.GetInt();
            }
            else
            {
                intVal = DEFAULT_INT;
            }
        }
        
        template<>
        void FromJson(std::string& strVal, rapidjson::Value &jsonItem)
        {
            if(jsonItem.IsNull() || !jsonItem.IsString())
            {
                strVal = "";
            }
            else
            {
                strVal = jsonItem.GetString();
            }
        }
        
        template<>
        void FromJson(bool& boolVal, rapidjson::Value &jsonItem)
        {
            if(jsonItem.IsNull() || !jsonItem.IsBool())
            {
                boolVal = false;
            }
            else
            {
                boolVal = jsonItem.GetBool();
            }
        }
        
        template<>
        void FromJson(double& doubleVal, rapidjson::Value &jsonItem)
        {
            const double DEFAULT_DOUBLE = DBL_MAX;
            if (jsonItem.IsNull())
            {
                doubleVal = DEFAULT_DOUBLE;
            }
            else if (jsonItem.IsString())
            {
                auto doubleString = jsonItem.GetString();
                doubleVal = StringUtils::ConvertStringToNumeric(doubleString, DEFAULT_DOUBLE);
            }
            else if (jsonItem.IsNumber())
            {
                doubleVal = jsonItem.GetDouble();
            }
            else
            {
                doubleVal = DEFAULT_DOUBLE;
            }
        }
        
        template<>
        void FromJson(long long& llongVal, rapidjson::Value &jsonItem)
        {
            const long long DEFAULT_LONG_LONG = LLONG_MAX;
            
            if (jsonItem.IsNull())
            {
                llongVal = DEFAULT_LONG_LONG;
            }
            else if (jsonItem.IsString())
            {
                auto llongStr = jsonItem.GetString();
                llongVal = StringUtils::ConvertStringToNumeric(llongStr, DEFAULT_LONG_LONG);
            }
            else if (jsonItem.IsNumber())
            {
                llongVal = jsonItem.GetInt64();
            }
            else
            {
                llongVal = DEFAULT_LONG_LONG;
            }
        }
        
        template<>
        void FromJson(std::shared_ptr<std::string> &ptr, rapidjson::Value &jsonItem)
        {
            if(nullptr != ptr)
            {
                FromJson(*ptr, jsonItem);
            }
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, int32_t& value)
        {
            writer.Int(value);
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, std::string& value)
        {
            writer.String(value.c_str());
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, bool& value)
        {
            writer.Bool(value);
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, double& value)
        {
            writer.Double(value);
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, long long& value)
        {
            writer.Int64(value);
        }
        
        template <>
        void ToJson( rapidjson::Writer<rapidjson::StringBuffer> &writer, std::shared_ptr<std::string>& value)
        {
            if(nullptr != value)
            {
                ToJson(writer, *value);
            }
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, int& value, IToJsonFieldControllerPtr controller)
        {
            ToJson(writer, value);
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, std::string& value, IToJsonFieldControllerPtr controller)
        {
            ToJson(writer, value);
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, bool& value, IToJsonFieldControllerPtr controller)
        {
            ToJson(writer, value);
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, double& value, IToJsonFieldControllerPtr controller)
        {
            ToJson(writer, value);
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, long long& value, IToJsonFieldControllerPtr controller)
        {
            ToJson(writer, value);
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, std::shared_ptr<std::string>& value, IToJsonFieldControllerPtr controller)
        {
            ToJson(writer, value);
        }
    }
}
