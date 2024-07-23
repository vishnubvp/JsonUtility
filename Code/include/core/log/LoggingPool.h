/**
 *Copyright © 2018 HelloWorld. All rights reserved.
 *
 * @file    LoggingPool.h
 * @author  Yi Zheng
 * @brief
 *
 */

#ifndef VsboardMobile_LoggingPool_h
#define VsboardMobile_LoggingPool_h

#include <thread>

#include "core/concurrent/BlockingQueue.h"
#include "core/util/BaseInclude.h"
#include "core/log/ILogger.h"
#include "core/log/LogEntity.h"
#include "core/util/NonCopyable.h"
#include "core/util/TypeDefs.h"

namespace BBMobileSDK
{
    class LoggingPool : NonCopyable
    {
    public:
        static LoggingPool& GetInstance();
        
        void AddLogAsync(LogEntity &&log);
        void AddAsyncLogger(const std::string &name,
                            ILoggerUPtr &&logger);
        void RemoveAsyncLogger(const std::string &name);
        
        /**
         Add log to pool sync, will sync write log sync logger
         Then add log to async pool then writer log to async logger
         */
        void AddLog(LogEntity &&log);
        void AddLogger(const std::string &name,
                       ILoggerUPtr &&logger);
        void RemoveLogger(const std::string &name);
        ~LoggingPool();
        
    private:
        LoggingPool();
        void WriteSyncLog(LogEntity &log);
        void ConsumeAsyncLog();
        
        BlockingQueue<LogEntity> m_loggingQueue;
        std::atomic<bool> m_needStop;
        std::thread m_loggingThread;
        
        std::map<std::string, ILoggerUPtr> m_asyncLoggerList;
        std::mutex m_asyncLoggerListMtx;
        
        std::map<std::string, ILoggerUPtr> m_loggerList;
        std::mutex m_loggerListMtx;
    };
}

#endif /* VsboardMobile_LoggingPool_h */
