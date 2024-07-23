/*
 * FileLogWriter.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: Martyn Ye
 Email : Martyn.Ye@blackboard.com
 */

#include "core/config/SharedMobileConfig.h"

#include "core/log/FileLogWriter.h"
#include "core/file/FileUtils.h"
#include "core/util/TimeUtils.h"

namespace BBMobileSDK
{
    FileLogWriter& FileLogWriter::GetInstance()
    {
        static FileLogWriter* s_logWriter = new FileLogWriter();
        return *s_logWriter;
    }
    
    bool FileLogWriter::LogToFile(const std::string& log_str)
    {
        if (log_str.empty() || SharedMobileConfig::m_LocalStoragePath.empty())
        {
            return false;
        }
        
        if (!FileUtils::CreateFolderAtPath(GetLogDir()))
        {
            return false;
        }

        auto fullPath = GetLogPath();;
        std::lock_guard<std::mutex> lock(m_logFileMtx);
        return FileUtils::writeFile(fullPath, log_str);
    }
    
    bool FileLogWriter::ClearLogFile()
    {
        if (SharedMobileConfig::m_LocalStoragePath.length() == 0)
        {
            return false;
        }
        auto fullPath = GetLogPath();
        return FileUtils::ClearFile(fullPath);
    }
    
    void FileLogWriter::SetLogMaxSize(long long size)
    {
        m_logMaxSize = size;
    }
    
    void FileLogWriter::SetLogSplitInterval(long long seconds)
    {
        m_logSplitInterval = seconds;
    }
    
    std::string FileLogWriter::GetLogPath()
    {
        if (m_logFullPath.empty())
        {
            m_logFullPath = GetLogDir() + "/" + File::LOG_FILE_NAME;
        }
        return m_logFullPath;
    }
    
    std::string FileLogWriter::GetLogDir()
    {
        return SharedMobileConfig::m_LocalStoragePath + "/" + File::LOG_DIR_NAME;
    }
}
