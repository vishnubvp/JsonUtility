/**

 *
 * @file    ServerbaasPathBuilder.cpp
 * @author  
 * @brief   Path builder used to build the Serverbaas url path   
 *
 */

#include "core/http/ServerbaasPathBuilder.h"

#include "core/config/SharedMobileConfig.h"
#include "shared/const/SharedInternalConst.h"

namespace VSTestSDK
{
    ServerbaasPathBuilder::ServerbaasPathBuilder()
    : PathBuilder()
    {
    }
    
    ServerbaasPathBuilder::ServerbaasPathBuilder(const std::string &ServerbaasName,
                                       const std::string &apiName,
                                       const std::string &apiVersion)
    : PathBuilder()
    , m_ServerbaasName(ServerbaasName)
    , m_apiName(apiName)
    , m_apiVersion(apiVersion)
    {
    }
    
    ServerbaasPathBuilder::ServerbaasPathBuilder(ServerbaasPathBuilder &rhs)
    {
        *this = rhs;
    }
    
    ServerbaasPathBuilder& ServerbaasPathBuilder::operator=(const ServerbaasPathBuilder &rhs)
    {
        if (this != &rhs)
        {
            PathBuilder::operator=(rhs);
            m_ServerbaasName = rhs.m_ServerbaasName;
            m_apiName = rhs.m_apiName;
            m_apiVersion = rhs.m_apiVersion;
        }
        return *this;
    }
    
    ServerbaasPathBuilder::~ServerbaasPathBuilder()
    {
    }
    
    std::string ServerbaasPathBuilder::GetHost() const
    {
        return SharedMobileConfig::m_HostName;
    }
    
    std::string ServerbaasPathBuilder::GetPath() const
    {
        std::string basePath = PathBuilder::GetPath();
        std::stringstream ss;
        if (!m_ServerbaasName.empty() &&
            !m_apiName.empty() &&
            !m_apiVersion.empty())
        {
            ss << "/"
            << m_ServerbaasName << "/"
            << m_apiName << "/"
            << m_apiVersion;
        }
        ss << basePath;
        return ss.str();
    }
    
    std::string ServerbaasPathBuilder::GetServerbaasName() const
    {
        return m_ServerbaasName;
    }
    
    void ServerbaasPathBuilder::SetServerbaasName(const std::string &ServerbaasName)
    {
        m_ServerbaasName = ServerbaasName;
    }
    
    std::string ServerbaasPathBuilder::GetApiName() const
    {
        return m_apiName;
    }
    
    void ServerbaasPathBuilder::SetApiName(const std::string &apiName)
    {
        m_apiName = apiName;
    }
    
    std::string ServerbaasPathBuilder::GetApiVersion() const
    {
        return m_apiVersion;
    }
    
    void ServerbaasPathBuilder::SetApiVersion(const std::string &apiVersion)
    {
        m_apiVersion = apiVersion;
    }
}