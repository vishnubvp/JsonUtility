
#ifndef VsboardMobile_PathBuilderCreator_h
#define VsboardMobile_PathBuilderCreator_h

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"
#include "shared/const/SharedInternalConst.h"

namespace BBMobileSDK
{
    BB_FORWARD_DECLARE(PathBuilder);
    
    class PathBuilderCreator
    {
    public:
        static PathBuilderPtr ConstructBuilderByType(RestConst::PathBuilderType builderType,
                                                     const std::vector<std::string> &pathList);
    };
}

#endif /* VsboardMobile_PathBuilderFactory_h */
