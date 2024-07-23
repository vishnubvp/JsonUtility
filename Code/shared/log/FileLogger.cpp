/**
 *Copyright © 2018 HelloWorld. All rights reserved.
 *
 * @file    FileLogger.cpp
 * @author  Yi Zheng
 * @brief   
 *
 */

#include "core/log/FileLogger.h"
#include "core/log/FileLogWriter.h"
#include "core/log/LoggingPool.h"
#include "shared/const/SharedInternalConst.h"


namespace BBMobileSDK
{
    std::atomic<bool> FileLogger::s_enableLogToFile{false};
    void FileLogger::SetEnableLogToFile(bool enableLogToFile)
    {
        s_enableLogToFile = enableLogToFile;
        if (enableLogToFile)
        {
            LoggingPool::GetInstance().AddAsyncLogger(Logging::FILE_LOGGER_NAME, FileLoggerUPtr(new FileLogger));
        }
        else
        {
            LoggingPool::GetInstance().RemoveAsyncLogger(Logging::FILE_LOGGER_NAME);
        }
    }
    
    bool FileLogger::GetEnableLogToFile()
    {
        return s_enableLogToFile;
    }
    
    void FileLogger::WriteLog(const LogEntity &log)
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        FileLogWriter::GetInstance().LogToFile(log.ToString());
    }
}
