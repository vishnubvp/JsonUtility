/**
 *Copyright © 2017 HelloWorld. All rights reserved.
 *
 * @file    CommonJsonHelper.h
 * @author  Yi Zheng
 * @brief
 *
 */

#ifndef HelloWorld_CommonJsonHelper_h
#define HelloWorld_CommonJsonHelper_h

#include <cfloat>
#include <climits>
#include <string>
#include <vector>
#include <map>

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"
#include "core/external/rapidjson/document.h"
#include "core/external/rapidjson/stringbuffer.h"
#include "core/external/rapidjson/writer.h"
#include "shared/util/ToJsonFieldController.h"

namespace BBMobileSDK
{    
    namespace JsonHelper
    {
        // MARK: From Json Logic
        template <typename T>
        void BeforeFromJson(T* object, rapidjson::Value &jsonItems) { }
        
        template <typename T>
        void AfterFromJson(T* object, rapidjson::Value &jsonItems) { }
        
        template <typename T>
        void FromJson(T& object, rapidjson::Value &jsonItem)
        {
            static_assert(sizeof(T) == -1, "This type is not support for from json yet!" );
        }
        
        template<>
        void FromJson(int& intVal, rapidjson::Value &jsonItem);
        
        template<>
        void FromJson(std::string& strVal, rapidjson::Value &jsonItem);
        
        template<>
        void FromJson(bool& boolVal, rapidjson::Value &jsonItem);

        template<>
        void FromJson(double& doubleVal, rapidjson::Value &jsonItem);
        
        template<>
        void FromJson(long long& llongVal, rapidjson::Value &jsonItem);
        
        template<typename = std::shared_ptr<std::string>>
        void FromJson(std::shared_ptr<std::string> &ptr, rapidjson::Value &jsonItem);
        
        template <typename T>
        void FromJson(std::shared_ptr<T> &ptr, rapidjson::Value &jsonItem)
        {
            ptr = std::make_shared<T>();
            ptr->FromJson(jsonItem);
        }
        
        template <typename T>
        void FromJson(std::vector<T> &vec, rapidjson::Value &jsonItem)
        {
            if (jsonItem.IsArray())
            {
                vec.clear();
                for (int i = 0 ; i < jsonItem.Size(); i++)
                {
                    if (!jsonItem[i].IsNull())
                    {
                        T obj;
                        FromJson(obj, jsonItem[i]);
                        vec.push_back(obj);
                    }
                }
            }
        }
        
        template <typename ValueType>
        void FromJson(std::map<std::string, ValueType>& map, rapidjson::Value &jsonItem)
        {
            map.clear();
            
            for (auto it = jsonItem.MemberBegin(); it != jsonItem.MemberEnd(); it++)
            {
                std::string key;
                ValueType value;
                
                FromJson(key, it->name);
                FromJson(value, it->value);
                
                map[key] = value;
            }
        }
        
        template <typename T>
        void FromJson(T& object, rapidjson::Value &jsonItems, const char* key)
        {
            if (jsonItems.HasMember(key) && !jsonItems[key].IsNull())
            {
                FromJson(object, jsonItems[key]);
            }
        }
        
       
        
        // MARK: To Json logic
        template <typename T>
        void BeforeToJson(T* object, rapidjson::Writer<rapidjson::StringBuffer> &writer) { }
        
        template <typename T>
        void AfterToJson(T* object, rapidjson::Writer<rapidjson::StringBuffer> &writer) { }
        
        template <typename FieldType>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, FieldType& value)
        {
            static_assert(sizeof(FieldType) == -1, "This type is not support for to json yet!");
        }
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, int& value);
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, std::string& value);
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, bool& value);
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, double& value);
        
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, long long& value);
        
        template <typename = std::shared_ptr<std::string>>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    std::shared_ptr<std::string>& value);
        
        template <typename FieldType>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    std::shared_ptr<FieldType>& value)
        {
            if (value != nullptr)
            {
                value->ToJson(writer);
            }
        }
        
        template <typename T>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    std::vector<T> &vec)
        {
            writer.StartArray();
            for (auto & object : vec)
            {
                ToJson(writer, object);
            }
            writer.EndArray();
        }
        
        template <typename MapValueType>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    std::map<std::string, MapValueType>& map)
        {
            writer.StartObject();
            
            for (auto & kvPair : map)
            {
                writer.String(kvPair.first.c_str());
                ToJson(writer, kvPair.second);
            }
            
            writer.EndObject();
        }
        
        template <typename FieldType>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, FieldType& value, IToJsonFieldControllerPtr controller)
        {
            static_assert(sizeof(FieldType) == -1, "This type is not support for to json yet!");
        }
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, int& value, IToJsonFieldControllerPtr controller);
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, std::string& value, IToJsonFieldControllerPtr controller);
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, bool& value, IToJsonFieldControllerPtr controller);
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, double& value, IToJsonFieldControllerPtr controller);
        template <>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer, long long& value, IToJsonFieldControllerPtr controller);
        template <typename = std::shared_ptr<std::string>>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    std::shared_ptr<std::string>& value,
                    IToJsonFieldControllerPtr controller);
        
        template <typename FieldType>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    std::shared_ptr<FieldType>& value,
                    IToJsonFieldControllerPtr controller)
        {
            if (value != nullptr)
            {
                value->ToJson(writer, controller);
            }
        }
        
        template <typename T>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    std::vector<T> &vec,
                    IToJsonFieldControllerPtr controller)
        {
            writer.StartArray();
            for (auto & object : vec)
            {
                ToJson(writer, object, controller);
            }
            writer.EndArray();
        }
        
        template <typename MapValueType>
        void ToJson(rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    std::map<std::string, MapValueType>& map,
                    IToJsonFieldControllerPtr controller)
        {
            writer.StartObject();

            for (auto & kvPair : map)
            {
                writer.String(kvPair.first.c_str());
                ToJson(writer, kvPair.second, controller);
            }

            writer.EndObject();
        }

        
        template <typename T>
        inline bool NeedWriteJson(T& val, IToJsonFieldControllerPtr toJsonController)
        {
            return true;
        }
        
        template <typename T>
        inline bool NeedWriteJson(std::vector<T> &vec, IToJsonFieldControllerPtr toJsonController)
        {
            if (!vec.empty()) return true;
            else return toJsonController->NeedWriteEmptyVector();
        }
        
        template <typename T>
        inline bool NeedWriteJson(std::shared_ptr<T> &ptr, IToJsonFieldControllerPtr toJsonController)
        {
            return ptr != nullptr;
        }
        
        template <>
        inline bool NeedWriteJson(int32_t &intVal, IToJsonFieldControllerPtr toJsonController)
        {
            return toJsonController->NeedWriteJson(intVal);
        }
        
        template <>
        inline bool NeedWriteJson(int64_t &llongVal, IToJsonFieldControllerPtr toJsonController)
        {
            return toJsonController->NeedWriteJson(llongVal);
        }
        
        template <>
        inline bool NeedWriteJson(double &doubleVal, IToJsonFieldControllerPtr toJsonController)
        {
            return toJsonController->NeedWriteJson(doubleVal);
        }
        
        template <>
        inline bool NeedWriteJson(std::string &strVal, IToJsonFieldControllerPtr toJsonController)
        {
            return toJsonController->NeedWriteJson(strVal);
        }

        template <>
        inline bool NeedWriteJson(bool &boolVal, IToJsonFieldControllerPtr toJsonController)
        {
            return toJsonController->NeedWriteJson(boolVal);
        }
        
        template <typename ModelType, typename FieldType>
        void ToJson(ModelType* object,
                    FieldType& value,
                    rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    const char* key)
        {
            auto controller = ToJsonFieldControllerFactory::GetToJsonFieldController(ToJsonFieldControllerType::ToServer);
            if (NeedWriteJson(value, controller))
            {
                writer.String(key);
                ToJson(writer, value);
            }
        }
        
        template <typename ModelType, typename FieldType>
        void ToJson(ModelType* object,
                    FieldType& value,
                    rapidjson::Writer<rapidjson::StringBuffer> &writer,
                    const char* key,
                    IToJsonFieldControllerPtr toJsonController)
        {
            if (toJsonController == nullptr)
            {
                ToJson(object, value, writer, key);
            }
            else if (NeedWriteJson(value, toJsonController))
            {
                writer.String(key);
                ToJson(writer, value, toJsonController);
            }
        }
        
    }
}

#endif /* HelloWorld_CommonJsonHelper_h */
