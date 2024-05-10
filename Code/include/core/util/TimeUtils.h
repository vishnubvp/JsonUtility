

#ifndef VsboardMobile_TimeUtils_h
#define VsboardMobile_TimeUtils_h

#include <time.h>
#include <iostream>

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"

namespace BBMobileSDK
{
    namespace TimeConst
    {
        const long long MILLISEC_PER_DAY = 1000 * 24 * 60 * 60;
        const long long MILLISEC_PER_SEC = 1000;
        
        const int SECONDS_PER_DAY = 24 * 60 * 60;
        const int SECONDS_PER_HOUR = 60 * 60;
        const int SECONDS_PER_MIN = 60;
        
        const int SECONDS_MANDATORY_THRESHOLD = 30;
        const int SECONDS_REFRESH_THRESHOLD = 300;
    }
    
    class DateTime;
    GLB_SMART_PTR_DEF(DateTime);
    
    class TimeUtils
    {
    public:
        //
        // local time thread safe
        //
        static bool CalcLocalTime(const time_t *time, struct tm *timeInfo);
        
        //
        // gmt time thread safe
        //
        static bool CalcGMTTime(const time_t *time, struct tm *timeInfo);
        
        static long long GetCurrentMillisecond();
        static time_t GetCurrentSecond();
        
        static std::string GetCurrentDateTimeString();
        static std::string GetCurrentDateString();
        
        static std::string UTCStrFromTimestamp(long long timestamp);
        static std::string GetISOCurrentTimestamp(long long timestamp);
        static std::string GetISOCurrentTimestampWithMilliSeconds(long long timestamp);

        static std::string GMTDateStrFromTimestamp(long long timestamp);
        static std::string LocalDateStrFromTimestamp(long long timestamp);
        
        static bool AreSameDayInLocal(long long timestampA, long long timestampB);
        static bool AreSameDayInGMT(long long timestampA, long long timestampB);
        
        static long long GetFirstMillisecondOfADayInLocal(long long timestamp);
        static long long GetLastMillisecondOfADayInLocal(long long timestamp);
        
        static DateTimePtr GMTDateTimeWithUnixMilliSecond(long long unixMilliSecond);
        static DateTimePtr LocalDateTimeWithUnixMilliSecond(long long unixMilliSecond);
        
        static DateTimePtr GetDateTimeWithIncDays(const DateTimePtr & dateTime, int dayOffset);
        
        static bool AreSameDay(const DateTimePtr &dateTimeA, const DateTimePtr &dateTimeB);
        static long long GetPastDateTimeInMillisecond(int NumberOfDays);

    };
}

#endif


