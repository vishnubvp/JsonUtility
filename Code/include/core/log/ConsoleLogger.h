/**
 *Copyright © 2018 HelloWorld. All rights reserved.
 *
 * @file    ConsoleLogger.h
 * @author  Yi Zheng
 * @brief
 *
 */

#ifndef VsboardMobile_ConsoleLogger__h
#define VsboardMobile_ConsoleLogger__h

#include <mutex>

#include "core/util/BaseInclude.h"
#include "core/log/ILogger.h"
#include "core/util/NonCopyable.h"
#include "core/util/TypeDefs.h"

namespace BBMobileSDK
{
    BB_FORWARD_DECLARE(ConsoleLogger);
    
    class ConsoleLogger : public ILogger
    {
    public:
        void WriteLog(const LogEntity &log) override;
    private:
        void WriteToOSConsole(const LogEntity &log);        
        std::mutex m_mtx;
    }; 
}

#endif /* VsboardMobile_ConsoleLogger__h */
