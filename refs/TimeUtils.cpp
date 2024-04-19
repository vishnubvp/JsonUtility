

#include "core/util/TimeUtils.h"

#include <iomanip>

#ifndef _WIN32
#include <sys/time.h>
#else
#include <Windows.h>
#include "core/util/Helpers.h"
#include "core/win32/WinStringUtils.h"
#include "core/log/Logger.h"
#include "core/util/StringUtils.h"
#include <sys/types.h>
#include <sys/timeb.h>
#endif

#include "core/util/DateTime.h"

namespace VSMobileSDK
{
    //
    // local time thread safe
    //
    bool TimeUtils::CalcLocalTime(const time_t *time, struct tm *timeInfo)
    {
#ifdef _WIN32
        if (localtime_s(timeInfo, time) != 0)
        {
            Logger::error("timestamp is invalid, timestamp :" + StringUtils::strfval(*time));
            return false;
        }
        return true;
#else
        localtime_r(time, timeInfo);
        return true;
#endif
    }
    
    //
    // gmt time thread safe
    //
    bool TimeUtils::CalcGMTTime(const time_t *time, struct tm *timeInfo)
    {
#ifdef _WIN32
        if (gmtime_s(timeInfo, time) != 0)
        {
            Logger::error("timestamp is invalid, timestamp :" + StringUtils::strfval(*time));
            return false;
        }
        return true;
#else
        gmtime_r(time, timeInfo);
        return true;
#endif
    }
    
    long long TimeUtils::GetCurrentMillisecond()
    {
        using namespace std::chrono;
        return duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
    }
    
    long long TimeUtils::GetFirstMillisecondOfADayInLocal(long long timestamp)
    {
        DateTimePtr dateTime = TimeUtils::LocalDateTimeWithUnixMilliSecond(timestamp);
        return dateTime->GetFirstMilliSecond();
    }
    
    long long TimeUtils::GetLastMillisecondOfADayInLocal(long long timestamp)
    {
        DateTimePtr dateTime = TimeUtils::LocalDateTimeWithUnixMilliSecond(timestamp);
        return dateTime->GetLastMilliSecond();
    }
    
    time_t TimeUtils::GetCurrentSecond()
    {
#ifdef _WIN32
        return GetCurrentMillisecond() / 1000;
#else
        time_t currentTime;
        time(&currentTime);
        return currentTime;
#endif
    }
    
    std::string TimeUtils::UTCStrFromTimestamp(long long timestamp) {
        
        time_t rawtime = (time_t)(timestamp / 1000);
        struct tm timeinfo;
        char buffer[40];
        bool isCalcSuccess = true;
        
        isCalcSuccess = CalcLocalTime(&rawtime, &timeinfo);
#ifdef _WIN32
        if (!isCalcSuccess)
        {
            rawtime = 0;
            CalcLocalTime(&rawtime, &timeinfo);
        }
        
        strftime(buffer, 40, "%Y-%m-%dT%H:%M:%S", &timeinfo);
        std::string str(buffer);
        
        struct _timeb tstruct;
        _ftime64_s(&tstruct);
        long gmtOffset = tstruct.timezone;
        bool pos = gmtOffset < 0;
        if (pos) gmtOffset = -gmtOffset;
        int hourOffset = gmtOffset / 60;
        int minOffset = gmtOffset - hourOffset * 60;
        char timeZoneBuffer[6];
        sprintf_s(timeZoneBuffer, "%c%02d%02d", (pos ? '+' : '-'), hourOffset, minOffset);
        return str + timeZoneBuffer;
#else
        strftime(buffer, 40, "%FT%T%z", &timeinfo);
        return std::string(buffer);
#endif
    }
    
    std::string TimeUtils::GetISOCurrentTimestamp(long long timestamp)
    {
        time_t rawtime = (time_t)(timestamp / 1000);
        struct tm timeinfo;
        char buffer[40];
        bool isCalcSuccess = true;
        
        isCalcSuccess = CalcLocalTime(&rawtime, &timeinfo);
#ifdef _WIN32
        if (!isCalcSuccess)
        {
            rawtime = 0;
            CalcLocalTime(&rawtime, &timeinfo);
        }
        
        strftime(buffer, 40, "%Y-%m-%dT%H:%M:%S", &timeinfo);
        std::string str(buffer);
        
        struct _timeb tstruct;
        _ftime64_s(&tstruct);
        long gmtOffset = tstruct.timezone;
        bool pos = gmtOffset < 0;
        if (pos) gmtOffset = -gmtOffset;
        int hourOffset = gmtOffset / 60;
        int minOffset = gmtOffset - hourOffset * 60;
        char timeZoneBuffer[6];
        sprintf_s(timeZoneBuffer, "%c%02d%02d", (pos ? '+' : '-'), hourOffset, minOffset);
        return str + timeZoneBuffer;
#else
        strftime(buffer, 40, "%FT%TZ", &timeinfo);
        return std::string(buffer);
#endif

    }

    std::string TimeUtils::GetISOCurrentTimestampWithMilliSeconds(long long timestamp)
    {
        struct timeval tv;
        struct tm *tm;
        gettimeofday(&tv, NULL);
        tm = localtime(&tv.tv_sec);
        int millisecs = (int)(tv.tv_usec/1000);

        time_t rawtime = (time_t)(timestamp / 1000);
        struct tm timeinfo;
        char buffer[40];
        char tempbuff[40];
        bool isCalcSuccess = true;
        
        isCalcSuccess = CalcLocalTime(&rawtime, &timeinfo);
        //long long currentmilliSecs = TimeUtils::GetCurrentMillisecond();
        strftime(tempbuff, 40, "%FT%T",&timeinfo);
        sprintf(buffer, "%s.%03dZ",tempbuff,millisecs);
        return std::string(buffer);
    }
    
    std::string TimeUtils::GMTDateStrFromTimestamp(long long timestamp)
    {
        time_t rawtime = (time_t)(timestamp / 1000);
        struct tm timeinfo;
        char buffer[20];
        
        bool isCalcSuccess = true;
        
        isCalcSuccess = CalcGMTTime(&rawtime, &timeinfo);
        
#ifdef _WIN32
        if (!isCalcSuccess)
        {
            rawtime = 0;
            CalcLocalTime(&rawtime, &timeinfo);
        }
        strftime(buffer, 20, "%Y%m%d", &timeinfo);
#else
        strftime(buffer, 20, "%F", &timeinfo);
#endif
        return std::string(buffer);
    }
    
    std::string TimeUtils::LocalDateStrFromTimestamp(long long timestamp)
    {
        time_t rawtime = (time_t)(timestamp / 1000);
        struct tm timeinfo;
        char buffer[20];
        
        bool isCalcSuccess = true;
        
        isCalcSuccess = CalcLocalTime(&rawtime, &timeinfo);
        
#ifdef _WIN32
        if (!isCalcSuccess)
        {
            rawtime = 0;
            CalcLocalTime(&rawtime, &timeinfo);
        }
        strftime(buffer, 20, "%Y%m%d", &timeinfo);
#else
        strftime(buffer, 20, "%F", &timeinfo);
#endif
        return std::string(buffer);
    }
    
    bool TimeUtils::AreSameDayInLocal(long long timestampA, long long timestampB)
    {
        DateTimePtr dateTimeA = TimeUtils::LocalDateTimeWithUnixMilliSecond(timestampA);
        DateTimePtr dateTimeB = TimeUtils::LocalDateTimeWithUnixMilliSecond(timestampB);
        return TimeUtils::AreSameDay(dateTimeA, dateTimeB);
    }
    
    bool TimeUtils::AreSameDayInGMT(long long timestampA, long long timestampB)
    {
        DateTimePtr dateTimeA = TimeUtils::GMTDateTimeWithUnixMilliSecond(timestampA);
        DateTimePtr dateTimeB = TimeUtils::GMTDateTimeWithUnixMilliSecond(timestampB);
        return TimeUtils::AreSameDay(dateTimeA, dateTimeB);
    }
    
    std::string TimeUtils::GetCurrentDateTimeString()
    {
        DateTimePtr now = LocalDateTimeWithUnixMilliSecond(GetCurrentMillisecond());
        struct tm  tstruct;
        char       buf[80];
        tstruct = now->GetTimeInfo();
        
        memset(buf, 0, sizeof(char) * 80);
        strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);
        
        std::stringstream ss;
        ss << buf << "." << std::setfill('0') << std::setw(3) << now->GetMilliSecond();
        return ss.str();
    }
    
    std::string TimeUtils::GetCurrentDateString()
    {
        DateTimePtr now = LocalDateTimeWithUnixMilliSecond(GetCurrentMillisecond());
        struct tm  tstruct;
        char       buf[80];
        tstruct = now->GetTimeInfo();
        
        memset(buf, 0, sizeof(char) * 80);
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
        
        std::stringstream ss;
        ss << buf;
        return ss.str();
    }
    
    DateTimePtr TimeUtils::GMTDateTimeWithUnixMilliSecond(long long unixMilliSecond)
    {
        DateTimePtr dateTimePtr(new DateTime(unixMilliSecond));
        return dateTimePtr;
    }
    
    DateTimePtr TimeUtils::LocalDateTimeWithUnixMilliSecond(long long unixMilliSecond)
    {
        DateTimePtr dateTimePtr(new DateTime(unixMilliSecond));
        return dateTimePtr->CalcLocalDateTime();
    }
    
    DateTimePtr TimeUtils::GetDateTimeWithIncDays(const DateTimePtr & dateTime, int dayOffset)
    {
        struct tm newTm;
        newTm = dateTime->GetTimeInfo();
        newTm.tm_mday += dayOffset;
        DateTimePtr dateTimePtr;
        dateTimePtr.reset(new DateTime(newTm));
        return dateTimePtr;
    }
    
    bool TimeUtils::AreSameDay(const DateTimePtr &dateTimeA, const DateTimePtr &dateTimeB)
    {
        return dateTimeA->GetYear() == dateTimeB->GetYear() &&
        dateTimeA->GetMonth() == dateTimeB->GetMonth() &&
        dateTimeA->GetDay() == dateTimeB->GetDay();
    }

    long long TimeUtils::GetPastDateTimeInMillisecond(int NumberOfDays)
    {
        using namespace std::chrono;
        std::chrono::duration<int,std::ratio<60*60*24> > days (NumberOfDays);
        return duration_cast< milliseconds >((system_clock::now()-days).time_since_epoch()).count();
    }
}

