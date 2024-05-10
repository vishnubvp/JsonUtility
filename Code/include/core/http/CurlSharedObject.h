

#ifndef VsboardMobile_CurlSharedObject_h
#define VsboardMobile_CurlSharedObject_h

#include "core/util/BaseInclude.h"
#include "core/util/TypeDefs.h"

#include "curl.h"

namespace BBMobileSDK
{
    BB_FORWARD_DECLARE(CurlSharedObject)
    
    class CurlSharedObject
    {
    public:
        CurlSharedObject();
        ~CurlSharedObject();
        bool IsExpired();
        
        CURLSH* GetCurlSharedObject();
        static CurlSharedObjectPtr GetInstance();
        
    private:
        void InitSharedObject();
        
        static void LockFunc(CURL *handle, curl_lock_data data, curl_lock_access access, void *userptr);
        static void UnlockFunc(CURL *handle, curl_lock_data data, void *userptr);
        
        void Lock(curl_lock_data data);
        void Unlock(curl_lock_data data);
        
        long long m_initTime;
        CURLSH* m_curlSharedObj;
        std::mutex m_sharedObjMtx;
    };
}

#endif /* VsboardMobile_CurlSharedObject_h */
