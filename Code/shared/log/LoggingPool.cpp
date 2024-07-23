/**
 *Copyright © 2018 HelloWorld. All rights reserved.
 *
 * @file    LoggingPool.cpp
 * @author  Yi Zheng
 * @brief
 *
 */
#include <thread>
#include <iostream>

#include "core/log/LoggingPool.h"

namespace BBMobileSDK
{
    LoggingPool& LoggingPool::GetInstance()
    {
        static LoggingPool *s_loggingPool = new LoggingPool();
        return *s_loggingPool;
    }
    
    LoggingPool::LoggingPool()
    : m_loggingQueue()
    , m_needStop(false)
    {
        m_loggingThread = std::thread(&LoggingPool::ConsumeAsyncLog, this);
    }
    
    LoggingPool::~LoggingPool()
    {
        m_needStop.store(true, std::memory_order_relaxed);
        LogEntity emptyEntity;
        m_loggingQueue.Put(emptyEntity);
        if (m_loggingThread.joinable()) m_loggingThread.join();
    }
    
    void LoggingPool::AddLogAsync(LogEntity &&log)
    {
        m_loggingQueue.Put(std::move(log));
    }
    
    void LoggingPool::AddAsyncLogger(const std::string &name,
                                     ILoggerUPtr &&logger)
    {
        if (!logger) return;
        
        std::lock_guard<std::mutex> lock(m_asyncLoggerListMtx);
        m_asyncLoggerList[name] = std::move(logger);
    }
    
    void LoggingPool::RemoveAsyncLogger(const std::string &name)
    {
        std::lock_guard<std::mutex> lock(m_asyncLoggerListMtx);
        m_asyncLoggerList.erase(name);
    }
    
    void LoggingPool::AddLog(LogEntity &&log)
    {
        WriteSyncLog(log);
        m_loggingQueue.Put(std::move(log));
    }
    
    void LoggingPool::AddLogger(const std::string &name,
                                ILoggerUPtr &&logger)
    {
        if (!logger) return;
        
        std::lock_guard<std::mutex> lock(m_loggerListMtx);
        m_loggerList[name] = std::move(logger);
    }
    
    void LoggingPool::RemoveLogger(const std::string &name)
    {
        std::lock_guard<std::mutex> lock(m_loggerListMtx);
        m_loggerList.erase(name);
    }
    
    void LoggingPool::WriteSyncLog(LogEntity &log)
    {
        try
        {
            std::lock_guard<std::mutex> lock(m_loggerListMtx);
            for (const auto &logger : m_loggerList)
            {
                logger.second->WriteLog(log);
            }
        }
        catch (const std::system_error& e)
        {
            std::cerr << "Log Failed!" << std::endl;
        }
    }
    
    void LoggingPool::ConsumeAsyncLog()
    {
        while (!m_needStop.load(std::memory_order_relaxed))
        {
            auto log = m_loggingQueue.Take();
            try
            {
                std::lock_guard<std::mutex> lock(m_asyncLoggerListMtx);
                for (const auto &logger : m_asyncLoggerList)
                {
                    logger.second->WriteLog(log);
                }
            }
            catch (const std::system_error& e)
            {
                std::cerr << "Log Failed!" << std::endl;
            }
        }
    }
}
