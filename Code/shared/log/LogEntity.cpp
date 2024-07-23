/**
 *Copyright © 2018 HelloWorld. All rights reserved.
 *
 * @file    LogEntity.cpp
 * @author  Yi Zheng
 * @brief   
 *
 */

#include "core/log/LogEntity.h"

#include <sstream>
#include "core/util/TimeUtils.h"

namespace BBMobileSDK
{
    LogEntity::LogEntity()
    : logTime(TimeUtils::GetCurrentDateTimeString())
    {}
    
    LogEntity::LogEntity(const char* sourceFile,
                         int line,
                         const char* function,
                         LogLevel logLevel,
                         const std::string &message,
                         const std::string &threadId)
    : sourceFile(sourceFile)
    , line(line)
    , function(function)
    , logLevel(logLevel)
    , message(message)
    , threadId(threadId)
    , logTime(TimeUtils::GetCurrentDateTimeString())
    , tag(Logging::LOG_TAG)
    {
    }
    
    std::string LogEntity::ToString() const
    {
        std::stringstream ss;
        char logLevlStr = (logLevel < 0 || logLevel >= size_of_array(LogLevelString)) ? 'U' : LogLevelString[logLevel][0];
        ss << "#" << threadId << ": " << logTime << " " << tag << "-" << logLevlStr << ": "
           << sourceFile << "(" << line << ")-" << function << ": " << message;
        return ss.str();
    }
}
