/**
 *Copyright © 2018 HelloWorld. All rights reserved.
 *
 * @file    ILogger.h
 * @author  Yi Zheng
 * @brief
 *
 */

#ifndef VsboardMobile_ILogger_h
#define VsboardMobile_ILogger_h

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"


namespace BBMobileSDK
{
    BB_FORWARD_DECLARE(ILogger);
    class LogEntity;
    
    class ILogger
    {
    public:
        virtual void WriteLog(const LogEntity &log) = 0;
        ILogger(){};
        virtual ~ILogger(){};
    };
}

#endif /* VsboardMobile_ILogger_h */
