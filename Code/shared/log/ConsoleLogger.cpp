/**
 *Copyright © 2018 HelloWorld. All rights reserved.
 *
 * @file    ConsoleLogger.cpp
 * @author  Yi Zheng
 * @brief   
 *
 */

#include "core/log/ConsoleLogger.h"

#ifdef _WIN32
    #ifdef _Serverbaas_SDK_WIN_DEBUG_
    #include <cstdio>
    #endif
#include "Windows.h"
#include "core/win32/WinStringUtils.h"
#elif ANDROID
    #include <android/log.h>
#endif

#include <iostream>

#include "core/log/LogEntity.h"

namespace BBMobileSDK
{
    void ConsoleLogger::WriteLog(const LogEntity &log)
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        WriteToOSConsole(log);
    }
    
#ifdef _WIN32
#ifdef _Serverbaas_SDK_WIN_DEBUG_
    
#define snprintf c99_snprintf
    
    inline int c99_vsnprintf(char* str, size_t size, const char* format, va_list ap)
    {
        int count = -1;
        
        if (size != 0)
            count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
        if (count == -1)
            count = _vscprintf(format, ap);
        
        return count;
    }
    
    inline int c99_snprintf(char* str, size_t size, const char* format, ...)
    {
        int count;
        va_list ap;
        
        va_start(ap, format);
        count = c99_vsnprintf(str, size, format, ap);
        va_end(ap);
        
        return count;
    }
    
    void WinOutput(const char *str, ...)
    {
        char buf[204800];
        va_list ptr;
        va_start(ptr, str);
        snprintf(buf, 204800, "%s", str);
        OutputDebugStringA(buf);
        OutputDebugStringA("\r\n");
    }
#endif
#endif

    
    void ConsoleLogger::WriteToOSConsole(const LogEntity &log)
    {
        auto logStr = log.ToString();
        auto tagStr = log.GetTag();
#ifdef ANDROID
        if (log.GetLogLevel() >= LogLevelError)
        {
            __android_log_print(ANDROID_LOG_ERROR, tagStr.c_str(), "%s", logStr.c_str());
        }
        else if (log.GetLogLevel() == LogLevelInfo)
        {
            __android_log_print(ANDROID_LOG_INFO, tagStr.c_str(), "%s", logStr.c_str());
        }
        else
        {
            __android_log_print(ANDROID_LOG_DEBUG, tagStr.c_str(), "%s", logStr.c_str());
        }
        
#elif _WIN32
#ifdef _Serverbaas_SDK_WIN_DEBUG_
        WinOutput(logStr.c_str());
#endif
#else
        std::cout << logStr << std::endl ;
#endif
    }
}
