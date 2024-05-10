

#ifndef VsboardMobile_LogEntity_h
#define VsboardMobile_LogEntity_h

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"
#include "core/util/bb_type_traits.h"
#include "shared/const/SharedInternalConst.h"

namespace BBMobileSDK
{
    enum LogLevel
    {
        LogLevelTrace,
        LogLevelDebug,
        LogLevelInfo,
        LogLevelError,
        LogLevelFatal,
        LogLevelLevelNumber
    };
    
    constexpr const char * const LogLevelString[] = {"TRACE", "DEBUG", "INFO", "ERROR", "FATAL"};
    static_assert(static_cast<size_t>(LogLevelLevelNumber) == size_of_array(LogLevelString), "LogLevelString size ! LogLevel enum number");
    
    class LogEntity
    {
    public:
        LogEntity();
        LogEntity(const char* sourceFile,
                  int line,
                  const char* function,
                  LogLevel logLevel,
                  const std::string &message,
                  const std::string &threadId);
        std::string ToString() const;
        inline std::string GetTag() const {return tag;}
        
        LogLevel GetLogLevel() const { return logLevel; }
        
    private:
        std::string sourceFile;
        int line {0};
        std::string function;
        LogLevel logLevel {LogLevelError};
        std::string message;
        std::string threadId;
        std::string logTime;
        std::string tag {Logging::LOG_TAG};
    };
}

#endif /* VsboardMobile_LogEntity_h */
