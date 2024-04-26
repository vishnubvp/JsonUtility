/**
 *  Copyright © 
 *
 * @file    ServerbaasPathBuilder.h
 * @author  
 * @brief   
 *
 */

#ifndef VsboardMobile_ServerbaasPathBuilder_h
#define VsboardMobile_ServerbaasPathBuilder_h

#include "core/http/PathBuilder.h"
#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"

namespace VSTestSDK
{
    BB_FORWARD_DECLARE(ServerbaasPathBuilder);
    
    class ServerbaasPathBuilder: public PathBuilder
    {
    public:
        ServerbaasPathBuilder();
        ServerbaasPathBuilder(const std::string &ServerbaasName,
                         const std::string &apiName,
                         const std::string &apiVersion);
        ServerbaasPathBuilder(ServerbaasPathBuilder &rhs);
        ServerbaasPathBuilder& operator=(const ServerbaasPathBuilder &rhs);
        virtual ~ServerbaasPathBuilder();
        
        virtual std::string GetHost() const;
        virtual std::string GetPath() const;
        
        std::string GetServerbaasName() const;
        void SetServerbaasName(const std::string &ServerbaasName);
        
        std::string GetApiName() const;
        void SetApiName(const std::string &apiName);
        
        std::string GetApiVersion() const;
        void SetApiVersion(const std::string &apiVersion);
    private:
        std::string m_ServerbaasName;
        std::string m_apiName;
        std::string m_apiVersion;
    };
}

#endif /* VsboardMobile_ServerbaasPathBuilder_h */
