//
//  Logger.cpp
//  VsboardMobile
//
//  Created by Gurp Parmar on 5/9/14.
//  Copyright (c) 2014 HelloWorld. All rights reserved.
//

#include "core/log/Logger.h"
#include "core/util/TimeUtils.h"

#ifdef _WIN32
#ifdef _Serverbaas_SDK_WIN_DEBUG_
#include <cstdio>
#endif
#include "Windows.h"
#include "core/win32/WinStringUtils.h"
#endif

#include <algorithm>
#include <sstream>
#include <thread>

#include "core/dispatch/mdispatch.h"
#include "core/file/FileUtils.h"
#include "core/log/FileLogWriter.h"
#include "core/log/LoggingPool.h"
#include "core/util/BasicUtils.h"
#include "core/util/InternalConstData.h"
#include "core/util/StringUtils.h"

using namespace std;

namespace BBMobileSDK
{
    void Logger::Error(string message, const char * sourcefile, const char * function)
    {
        Logger::GetInstance().Log(LogLevelError, sourcefile, 0, function, message);
    }
    
    void Logger::Info(string message, const char * sourcefile, const char * function)
    {
        Logger::GetInstance().Log(LogLevelInfo, sourcefile, 0, function, message);
    }
    
    void Logger::Debug(string message, const char * sourcefile, const char * function)
    {
        Logger::GetInstance().Log(LogLevelDebug, sourcefile, 0, function, message);
    }
    
    void Logger::Trace(string message, const char * sourcefile, const char * function)
    {
        Logger::GetInstance().Log(LogLevelTrace, sourcefile, 0, function, message);
    }
    
    Logger& Logger::GetInstance()
    {
        static Logger* s_logger = new Logger();
        return *s_logger;
    }
    
    Logger::Logger()
    : m_level(LogLevelError)
    {
    }
    
    void Logger::Log(LogLevel level,
                     const char *sourcefile,
                     int line,
                     const char *function,
                     const string &message)
    {
        if (level < m_level.load(std::memory_order_acquire))    return;
        LogEntity logEntity(FileUtils::GetFileName(sourcefile), line, function, level, message, BasicUtils::GetThreadId());
        LoggingPool::GetInstance().AddLog(std::move(logEntity));
    }
    
    void Logger::SetLogLevel(const std::string &level)
    {
        auto result = std::find_if(std::begin(LogLevelString),
                                   std::end(LogLevelString),
                                   [&level](const char* levelStr){
                                       return StringUtils::CompareIgnoreCase(levelStr, level) == 0;
                                   });
        if (result == std::end(LogLevelString)) return;
        
        int levelIdx = static_cast<int>(std::distance(std::begin(LogLevelString), result));
        m_level.store(levelIdx, std::memory_order_release);
    }
    
}
