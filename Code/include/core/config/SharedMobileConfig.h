

#ifndef _BBMobileSDK_SharedMobileConfig_H
#define _BBMobileSDK_SharedMobileConfig_H

#include <string>

#include "shared/const/SharedConst.h"

namespace BBMobileSDK
{
    class SharedMobileConfig
    {
    public:
        static void SetMobileConfig(const std::string &hostName, const std::string &appName, const std::string &appVersion, const std::string &apiName, const std::string &apiVersion);

        static void SetHostName(const std::string &hostName);
        static std::string GetHostName();

        static void SetAppName(const std::string &appName);
        static std::string GetAppName();
        static AppType GetAppType();
        
        static void SetAppVersion(const std::string &appVersion);
        static std::string GetAppVersion();
        
        static void SetServerbaasName(const std::string &ServerbaasName);
        static std::string GetServerbaasName();
        
        static void SetApiName(const std::string &apiName);
        static std::string GetApiName();
        
        static void SetApiVersion(const std::string &apiVersion);
        static std::string GetApiVersion();
        
        
        static void SetCarrierCode(const std::string &carrierCode);
        static std::string GetCarrierCode();
        
        static void SetCarrierName(const std::string &carrierName);
        static std::string GetCarrierName();
        
        static void SetDeviceOS(const std::string &deviceOS);
        static std::string GetDeviceOS();
        
        static void SetDeviceOSVesion(const std::string &deviceOSVesion);
        static std::string GetDeviceOSVesion();
        
        static void SetDeviceModel(const std::string &deviceModel);
        static std::string GetDeviceModel();
        
        static void SetDeviceId(const std::string &deviceId);
        static std::string GetDeviceId();
        
        static void SetLocale(const std::string &locale);
        static std::string GetLocale();
        
        static void SetTimezone(const std::string &timezone);
        static std::string GetTimezone();
        
        static void SetLocalStoragePath(const std::string &localStoragePath);
        static std::string GetLocalStoragePath();
        
        static void SetLogLevel(const std::string &logLevel);
        static std::string GetLogLevel();
        
        static void SetLogMaxSize(const long long bytes);
        static long long GetLogMaxSize();
        
        static void SetLogSplitInterval(const long long seconds);
        static long long GetLogSplitInterval();
        
        static void SetEnableCachingLogic(const bool enableCachingLogic);
        static bool GetEnableCachingLogic();
        
        static void SetEnableLogToFile(const bool enableLogToFile);
        static bool GetEnableLogToFile();
        
        static void SetDBStoragePath(const std::string & dbStoragePath);
        static std::string GetDBStoragePath();
        
        static void SetIgnoreSSLErrors(bool ignoreSSLError);
        static bool GetIgnoreSSLErrors();
        
        static void SetCertStoragePath(const std::string & certStoragePath);
        static std::string GetCertStoragePath();
        
        static void SetProxy(const std::string & proxy);
        static std::string GetProxy();
        
        static void SetEnableDebugMobilytics(bool enableDebugMobilytics);
        static bool GetEnableDebugMobilytics();
        
        static void SetNetworkStatus(int networkStatus);
        static int GetNetworkStatus();
        
        static void SetNetworkRestriction(int status);
        static int GetNetworkRestriction() ;
        
        static void SetEnableAutoSync(bool enableAutoSync);
        static bool GetEnableAutoSync();
        
        static void SetAutoSyncInterval(long long seconds);
        static long long GetAutoSyncInterval();

        static void SetTimeWithActivityInSecond(const long long timeWithActivityInSecond);
        static long long GetTimeWithActivityInSecond();
        
        static void SetDaysWithActivity(const int daysWithActivity);
        static int GetDaysWithActivity();
        
        static void SetDismissPrompt(const bool dismissPrompt);
        static bool GetDismissPrompt();
        
        static void SetEnableMockDiskFull(const bool diskFull);
        static bool GetEnableMockDiskFull();
        
        static void SetEnableGradingFeature(const bool enableGradingFeature);
        static bool GetEnableGradingFeature();
        
        static void SetEnableGradingForUltra(const bool enableGradingForUltra);
        static bool GetEnableGradingForUltra();
        
        static void SetF2WLoginCookie(const std::string &f2WLoginCookie);
        static std::string GetF2WLoginCookie();

        static void SetNewRelicLoggingEnabled(const bool newRelicLoggingEnabled);
        static bool GetNewRelicLoggingEnabled();

        static void PrintAllConfig();

        static bool isNetworkAvailable();

    public:
        static std::string m_HostName; 
        static std::string m_AppName; 
        static std::string m_AppVersion;
        static std::string m_ServerbaasName;
        static std::string m_ApiName;
        static std::string m_ApiVersion;
        
        static std::string m_CarrierCode; 
        static std::string m_CarrierName;
        static std::string m_DeviceOS; 
        static std::string m_DeviceOSVesion; 
        static std::string m_DeviceModel; 
        static std::string m_DeviceId;
        
        static std::string m_Locale;
        static std::string m_Timezone;
        static std::string m_LocalStoragePath;
        static std::string m_LogLevel;
        static long long m_LogMaxSize;
        static long long m_LogSplitInterval;
        static bool m_EnableCachingLogic;
        static std::string m_dbStoragePath;
        
        static bool m_ignoreSSLErrors;
        static std::string m_certStoragePath;
        static std::string m_proxy;
        
        static NetworkReachabilityStatus m_NetworkStatus;
        static bool m_EnableDebugMobilytics;
	
        static long long m_TimeWithActivityInSecond;
        static int m_DaysWithActivity;
        static bool m_DismissPrompt;
        static bool m_EnableMockDiskFull;
        static bool m_EnableGradingFeature;
        static bool m_EnableGradingForUltra;
        static std::string m_F2WLoginCookie;
        static bool m_NewRelicLoggingEnabled;
        
    private:
        static std::string ConvertEnum2String(NetworkReachabilityStatus status);
        static NetworkReachabilityStatus ConvertString2Enum(std::string status);
        
#ifdef GTEST
        static void ResetAllConfig();
#endif

    private:
        static std::map<NetworkReachabilityStatus, std::string> m_sMapNetworkStatus;
    };

}

#endif // _BBMobileSDK_SharedMobileConfig_H
