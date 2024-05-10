

#ifndef VsboardMobile_PathBuilder_h
#define VsboardMobile_PathBuilder_h

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"
#include "shared/const/SharedInternalConst.h"

namespace BBMobileSDK
{
    BB_FORWARD_DECLARE(PathBuilder);
    
    class PathBuilder
    {
    public:
        PathBuilder();
        PathBuilder(PathBuilder &rhs);
        PathBuilder& operator=(const PathBuilder &rhs);
        virtual ~PathBuilder();
        
        std::string GenerateFullPath();
        
        virtual std::string GetHost() const;
        virtual std::string GetPath() const;
        
        void SetPath(const std::string &path);
        void SetPathList(const std::vector<std::string> &pathList);
        
        void SetQueryParams(const std::map<std::string, std::string> &queryParams);
        void AddQueryParam(const std::string & key, const char* value);
        void AddQueryParam(const std::string & key, const std::string & value);
        void AddQueryParam(const std::string & key, const bool value);
        
        template <typename T>
        void AddQueryParam(const std::string & key, T value) = delete;
        
        std::string GetQueryParamString() const;
        
    private:
        void SetHost(const std::string &host);
        std::string PathListToString(const std::vector<std::string> &pathList);
        
        std::string m_host; //host represent the combination of schema and authority
        std::string m_path;
        std::string m_queryParam;
    };
}

#endif /* VsboardMobile_PathBuilder_h */
