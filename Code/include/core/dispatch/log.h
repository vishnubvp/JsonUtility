

#ifndef log_h
#define log_h

#include <thread>
#include "core/util/TimeUtils.h"
#include "core/file//FileUtils.h"

//#define S_DISPATCH_DEBUG
#ifdef S_DISPATCH_DEBUG
#define log_debug(fmt, ...) printf(STR_VALUE(0x%08x: %s: %s-%s: ) fmt STR_VALUE(\n), (unsigned int)std::hash<std::thread::id>()(std::this_thread::get_id()), TimeUtils::GetCurrentDateTimeString().c_str(), FileUtils::TrimFileName(__FILE__).c_str(), __FUNCTION__, __VA_ARGS__)
#else
#define log_debug(fmt, ...)
#endif
#define log_info(fmt, ...) printf(STR_VALUE(0x%08x: %s: %s-%s: ) fmt STR_VALUE(\n), (unsigned int)std::hash<std::thread::id>()(std::this_thread::get_id()), TimeUtils::GetCurrentDateTimeString().c_str(), FileUtils::TrimFileName(__FILE__).c_str(), __FUNCTION__, __VA_ARGS__)


#endif /* log_h */
