

#ifndef VsboardMobile_Logger_h
#define VsboardMobile_Logger_h

#include <string>
#include <vector>
#include <exception>
#include <iostream>
#include <sstream>
#include <mutex>
#include "core/dispatch/queue.h"


#ifdef ANDROID
#include <android/log.h>
#endif

#ifdef _WIN32
//#define _Serverbaas_SDK_WIN_DEBUG_
#endif

#include "core/log/LogEntity.h"

using std::string;
using std::exception;

#define info(message) Info(message, __FILE__, __FUNCTION__)
#define error(message) Error(message, __FILE__, __FUNCTION__)
#define debug(message) Debug(message, __FILE__, __FUNCTION__)
#define trace(message) Trace(message, __FILE__, __FUNCTION__)


namespace BBMobileSDK
{
    class Logger
    {
    public:
        
        /**
         *  Log error level message directly based on incoming String value
         *
         *  @param message String message to write to error level log
         */
        static void Error(string message, const char* sourcefile, const char * function);
        /**
         *  Log info level message directly based on incoming String value
         *
         *  @param message String message to write to info level log
         */
        static void Info(string message, const char* sourcefile, const char * function);
        /**
         *  Log debug level message directly based on incoming String value
         *
         *  @param message String message to write to debug level log
         */
        static void Debug(string message, const char * sourcefile, const char * function);
        
        static void Trace(string message, const char * sourcefile, const char * function);
        
    public:
        static Logger& GetInstance();
        void Log(LogLevel level,
                 const char* sourcefile,
                 int line,
                 const char * function,
                 const string &message);
        void SetLogLevel(const std::string &level);
        inline int GetLogLevel() const { return m_level.load(std::memory_order_relaxed); };
        
    private:
        Logger();
        std::atomic<int> m_level;
    };
    
    template <typename T>
    void ConcatLog(std::ostream& os, T t)
    {
        os << t;
    }
    
    template<typename T, typename... Args>
    void ConcatLog(std::ostream& o, T t, Args... args)
    {
        ConcatLog(o, t);
        ConcatLog(o, args...);
    }
    
    template<typename... Args>
    void BBLog(LogLevel logLevel, const char* file, int line, const char* function, Args&&... args)
    {
        std::ostringstream oss;
        ConcatLog(oss, args...);
        Logger::GetInstance().Log(logLevel, file, line, function, oss.str());
    }
    
#define LOG_DEBUG(...) if (Logger::GetInstance().GetLogLevel() < LogLevelDebug);else {BBLog(LogLevelDebug, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);}
#define LOG_TRACE(...) if (Logger::GetInstance().GetLogLevel() < LogLevelTrace);else {BBLog(LogLevelTrace, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);}
#define LOG_INFO(...)  if (Logger::GetInstance().GetLogLevel() < LogLevelInfo);else {BBLog(LogLevelInfo , __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);}
#define LOG_ERROR(...) if (Logger::GetInstance().GetLogLevel() < LogLevelError);else {BBLog(LogLevelError, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);}
#define LOG_FATAL(...) if (Logger::GetInstance().GetLogLevel() < LogLevelFatal);else {BBLog(LogLevelFatal, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);}
}
#endif
