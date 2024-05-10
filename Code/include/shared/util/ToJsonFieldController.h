

#ifndef VsboardMobile_ToJsonFieldController_h
#define VsboardMobile_ToJsonFieldController_h

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"

namespace BBMobileSDK
{
    enum class ToJsonFieldControllerType
    {
        ToServer,
        Minimal,
        Unknown
    };
    
    BB_FORWARD_DECLARE(IToJsonFieldController);
    class IToJsonFieldController
    {
    public:
        virtual bool NeedWriteJson(bool boolVal) = 0;
        virtual bool NeedWriteJson(int32_t int32Val) = 0;
        virtual bool NeedWriteJson(int64_t int64Val) = 0;
        virtual bool NeedWriteJson(std::string strVal) = 0;
        virtual bool NeedWriteJson(double strVal) = 0;
        virtual bool NeedWriteEmptyVector() = 0;
    };
    
    class ToJsonFieldControllerFactory
    {
    public:
        static IToJsonFieldControllerPtr GetToJsonFieldController(ToJsonFieldControllerType controllerType);
    };
   
}

#endif /* VsboardMobile_ToJsonFieldController_h */
