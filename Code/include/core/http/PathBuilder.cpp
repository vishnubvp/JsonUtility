

#include "core/http/PathBuilder.h"
#include "core/util/StringUtils.h"

namespace BBMobileSDK
{
    PathBuilder::PathBuilder() {}
    
    PathBuilder::PathBuilder(PathBuilder &rhs)
    {
        *this = rhs;
    }
    
    PathBuilder& PathBuilder::operator=(const PathBuilder &rhs)
    {
        if (this != &rhs)
        {
            m_host = rhs.m_host;
            m_path = rhs.m_path;
            m_queryParam = rhs.m_queryParam;
        }
        return *this;
    }
    
    PathBuilder::~PathBuilder() {}
    
    std::string PathBuilder::GenerateFullPath()
    {
        std::stringstream pathStream;
        
        pathStream << GetHost();
        std::string path = GetPath();
        if (!path.empty())
        {
            pathStream << path;
        }
        
        std::string queryParam = GetQueryParamString();
        if (!queryParam.empty())
        {
            pathStream << "?" << queryParam;
        }
        
        return pathStream.str();
    }
    
    void PathBuilder::SetHost(const std::string &host)
    {
        m_host = StringUtils::Trim(host, '/');
    }
    
    std::string PathBuilder::GetHost() const
    {
        return m_host;
    }
    
    std::string PathBuilder::GetPath() const
    {
        return m_path;
    }
    
    void PathBuilder::SetPath(const std::string &path)
    {
        m_path = "/" + StringUtils::Trim(path, '/');
    }
    
    void PathBuilder::SetPathList(const std::vector<std::string> &pathList)
    {
        m_path = PathListToString(pathList);
    }
    
    void PathBuilder::SetQueryParams(const std::map<std::string, std::string> &queryParams)
    {
        for(auto queryParam : queryParams)
        {
            AddQueryParam(queryParam.first, queryParam.second);
        }
    }
 
    void PathBuilder::AddQueryParam(const std::string &key, const char * value)
    {
        AddQueryParam(key, std::string(value));
    }
    
    void PathBuilder::AddQueryParam(const std::string & key, const bool value)
    {
        AddQueryParam(key, value ? StringValueForType::BOOL_TRUE : StringValueForType::BOOL_FALSE);
    }
    
    void PathBuilder::AddQueryParam(const std::string & key, const std::string & value)
    {
        if (key.empty()) return;
        
        m_queryParam += key + "=" + StringUtils::UrlEncodeForQueryString(value) + "&";
    }
    
    std::string PathBuilder::GetQueryParamString() const
    {
        return StringUtils::RTrim(m_queryParam, '&');
    }
    
    std::string PathBuilder::PathListToString(const std::vector<std::string> &pathList)
    {
        std::stringstream pathStream;
        
        for (const auto &path : pathList)
        {
            // WARNING
            // we do not support slash in path
            std::vector<std::string> pathElements = StringUtils::Split(path, "/");
            for (const auto &pathElement : pathElements) {
                pathStream << "/" << StringUtils::UrlEncodeForQueryString(pathElement);
            }
        }
        
        return pathStream.str();
    }
}
