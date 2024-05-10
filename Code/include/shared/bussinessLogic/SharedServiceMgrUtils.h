

#ifndef SDKShared_SharedServiceMgrUtils_h
#define SDKShared_SharedServiceMgrUtils_h

#include "shared/const/SharedConst.h"
#include "shared/model/SharedBaseResponse.h"
#include "shared/model/ISharedSerializableObject.h"
#include "core/util/BaseInclude.h"
#include "core/log/Logger.h"
#include "core/http/RestResponse.h"

namespace BBMobileSDK
{
    class SharedServiceMgrUtils
    {
    public:
        static int CalcResponseCodeFromRestResponse(const RestResponse* restResponse);
        
        static bool IsNeedCallRest(bool isMandatory, long long cacheUpdateTime);
        static std::string ExtractStableUrl(const std::string& url);
        
        template <typename SerializableObj>
        static bool DeserializeJson(const std::string & jsonStr, std::shared_ptr<SerializableObj> & object)
        {
            rapidjson::Document jsonData;
            
            try {
                jsonData.Parse<RAPIDJSON_DEFAULT_PARSE_FLAG>(jsonStr.c_str());
                
                //Check to make sure that we got a response from host
                if(jsonData.HasParseError() || jsonData.IsNull()) {
                    Logger::error("invalid json:" + jsonStr);
                    return false;
                }
                
                object.reset(new SerializableObj);
                object->FromJson(jsonData);
                return true;
            } catch (...) {
                Logger::error("unexpected exception");
                return false;
            }
            return true;
        }
        
        template <typename ObjectType>
        static bool DeserializeJson(const std::string &content, std::vector<SMART_PTR::shared_ptr<ObjectType> > &elemList)
        {
            rapidjson::Document jsonData;
            
            try
            {
                jsonData.Parse<RAPIDJSON_DEFAULT_PARSE_FLAG>(content.c_str());
                
                //Check to make sure that we got a response from host
                if(jsonData.HasParseError() || jsonData.IsNull())
                {
                    Logger::error("invalid json");
                    return false;
                }
                
                elemList.clear();
                for (int i=0; i<jsonData.Size(); i++)
                {
                    if (!jsonData[i].IsNull())
                    {
                        SMART_PTR::shared_ptr<ObjectType> sectionItem(new ObjectType);
                        sectionItem->FromJson(jsonData[i]);
                        elemList.push_back(sectionItem);
                    }
                }
            }
            catch (...)
            {
                Logger::error("invalid json");
                return false;
            }
            
            return true;
        }
        
        template <typename ObjectType>
        static bool SerializeToJson(const std::vector<SMART_PTR::shared_ptr<ObjectType>> &elemList, std::string &content)
        {
            try
            {
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                
                writer.StartArray();
                for(SMART_PTR::shared_ptr<ObjectType> element : elemList)
                {
                    if (element == nullptr)
                    {
                        writer.StartObject();
                        writer.EndObject();
                    }
                    else
                    {
                        element->ToJson(writer);
                    }
                }
                writer.EndArray();
                
                content = buffer.GetString();
            }
            catch (...)
            {
                Logger::error("serialization failed");
                return false;
            }
            return true;
        }
        
        template <typename ObjectType>
        static std::string ToJson(const std::vector<std::shared_ptr<ObjectType> > &elemList)
        {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            
            writer.StartArray();
            for (auto & ele : elemList)
            {
                if (ele)
                {
                    ele->ToJson(writer);
                }
            }
            
            writer.EndArray();
            
            return buffer.GetString();
        }
    private:
        static int MapCurlCodeToResponseCode(int curlCode, int originalResponseCode);
        static int MapHttpCodeToResponseCode(int httpCode, int originalResponseCode);
        static int MapMinorCodeToResponseCode(int httpCode, int minorCode, int originalResponseCode);
    };
}

#endif
