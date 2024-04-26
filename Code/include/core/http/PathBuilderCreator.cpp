
#include "core/http/PathBuilderCreator.h"

#include "core/config/SharedMobileConfig.h"
#include "core/http/ServerbaasPathBuilder.h"
#include "core/http/PathBuilder.h"
#include "core/log/Logger.h"

namespace VSTestSDK
{
    PathBuilderPtr PathBuilderCreator::ConstructBuilderByType(RestConst::PathBuilderType builderType,
                                                              const std::vector<std::string> &pathList)
    {
        PathBuilderPtr pathBuilder = nullptr;
        
        switch (builderType) {
            case RestConst::PathBuilderType::Default:
            {
                pathBuilder = std::make_shared<PathBuilder>();
                break;
            }
            case RestConst::PathBuilderType::ServerbaasV1:
            {
                pathBuilder = std::make_shared<ServerbaasPathBuilder>(SharedMobileConfig::m_ServerbaasName,
                                                                 SharedMobileConfig::m_ApiName,
                                                                 RestConst::ServerbaasVersion::VERSION_1);
                break;
            }
            case RestConst::PathBuilderType::ServerbaasV2:
            {
                pathBuilder = std::make_shared<ServerbaasPathBuilder>(SharedMobileConfig::m_ServerbaasName,
                                                                 SharedMobileConfig::m_ApiName,
                                                                 RestConst::ServerbaasVersion::VERSION_2);
                break;
            }
            default:
            {
                Logger::error("Unknown Path builder type!!");
                pathBuilder = std::make_shared<PathBuilder>();
                break;
            }
        }
        pathBuilder->SetPathList(pathList);
        return pathBuilder;
    }
}
