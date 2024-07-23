/**
 *Copyright © 2018 HelloWorld. All rights reserved.
 *
 * @file    FileLogger.h
 * @author  Yi Zheng
 * @brief
 *
 */

#ifndef VsboardMobile_FileLogger_h
#define VsboardMobile_FileLogger_h

#include <mutex>

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"
#include "core/log/ILogger.h"
#include "core/util/NonCopyable.h"

namespace BBMobileSDK
{
    BB_FORWARD_DECLARE(FileLogger);
    
    class FileLogger : public ILogger
    {
    public:
        static void SetEnableLogToFile(bool enableLogToFile);
        static bool GetEnableLogToFile();
        void WriteLog(const LogEntity &log) override;
    private:
        std::mutex m_mtx;
        static std::atomic<bool> s_enableLogToFile;
    };
}

#endif /* VsboardMobile_FileLogger_h */
