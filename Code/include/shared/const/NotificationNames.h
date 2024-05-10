

#ifndef NotificationNames_h
#define NotificationNames_h

namespace BBMobileSDK
{
    namespace NotificationNames
    {
        constexpr const_string SDK_INIT_WITH_USER_LOGGED_IN = "SDK_INIT_WITH_USER_LOGGED_IN";
        
        constexpr const_string USER_RE_LOGIN = "USER_RE_LOGIN";
        constexpr const_string USER_LOGOUT = "USER_LOGOUT";
        constexpr const_string USER_LOGIN = "USER_LOGIN";
        constexpr const_string REFRESH_REST_HEADER = "REFRESH_REST_HEADER";
        constexpr const_string MOBILYTICS_MARKER_CURL = "MOBILYTICS_MARKER_CURL";
        
        constexpr const_string USER_COOKIE_REFRESH = "USER_COOKIE_REFRESH";
        
        constexpr const_string SESSION_OPEN = "SESSION_OPEN";
        constexpr const_string SESSION_CLOSE = "SESSION_CLOSE";
        constexpr const_string SESSION_PAUSE = "SESSION_PAUSE";
        constexpr const_string SESSION_RESUME = "SESSION_RESUME";
        constexpr const_string PROMPT_CONFIG_CHANGED = "PROMPT_CONFIG_CHANGED";
        
    }
}


#endif /* NotificationNames_h */
