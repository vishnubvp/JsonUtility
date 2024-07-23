/*
 * FileLogWriter.h
 *
 *  Created on: Feb 9, 2015
 *      Author: Martyn Ye
		Email : Martyn.Ye@blackboard.com
 */

#ifndef BLACKBOARDMOBILE_INCLUDE_UTILS_FILE_FILELOGGER_H_
#define BLACKBOARDMOBILE_INCLUDE_UTILS_FILE_FILELOGGER_H_

#include "core/util/BaseInclude.h"
#include "core/util/NonCopyable.h"
#include "core/util/TypeDefs.h"
#include "core/util/InternalConstData.h"

namespace BBMobileSDK
{
    class FileLogWriter : NonCopyable
	{
	public:
		bool LogToFile(const std::string & log_str);
		bool ClearLogFile();
        void SetLogMaxSize(long long size);
        void SetLogSplitInterval(long long seconds);
        std::string GetLogPath();
        std::string GetLogDir();
        
        static FileLogWriter& GetInstance();
        
    private:
        FileLogWriter() = default;
        
        std::mutex m_logFileMtx;
        std::string m_logFullPath;
        std::atomic<long long> m_logMaxSize {File::LOG_MAX_SIZE};
        std::atomic<long long> m_logSplitInterval {File::LOG_SPLIT_INTERVAL};
	};
    
    GLB_SMART_PTR_DEF(FileLogWriter)
}

#endif /* BLACKBOARDMOBILE_INCLUDE_UTILS_FILE_FILELOGGER_H_ */
