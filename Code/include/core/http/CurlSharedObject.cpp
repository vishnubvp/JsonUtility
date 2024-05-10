

#include "core/http/CurlSharedObject.h"

#include "core/log/Logger.h"
#include "core/util/TimeUtils.h"
#include "shared/const/SharedInternalConst.h"

namespace BBMobileSDK
{
    CurlSharedObjectPtr CurlSharedObject::GetInstance()
    {
        static CurlSharedObjectPtr s_activeSharedObject(new CurlSharedObject);
        static std::mutex *s_activeObjectMtx = new std::mutex();
        
        BBScopeLock activeLock(*s_activeObjectMtx);
        
        CurlSharedObjectPtr sharedObj = s_activeSharedObject;
        
        if (sharedObj != nullptr &&
            sharedObj->IsExpired())
        {
            sharedObj = std::make_shared<CurlSharedObject>();
            s_activeSharedObject = sharedObj;
        }
        
        return sharedObj;
    }
    
    CurlSharedObject::CurlSharedObject()
    {
        m_initTime = TimeUtils::GetCurrentSecond();
        InitSharedObject();
    }
    
    void CurlSharedObject::InitSharedObject()
    {
        m_curlSharedObj = curl_share_init();
        curl_share_setopt(m_curlSharedObj, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
        curl_share_setopt(m_curlSharedObj, CURLSHOPT_LOCKFUNC, LockFunc);
        curl_share_setopt(m_curlSharedObj, CURLSHOPT_UNLOCKFUNC, UnlockFunc);
        curl_share_setopt(m_curlSharedObj, CURLSHOPT_USERDATA, this);
    }
    
    CURLSH* CurlSharedObject::GetCurlSharedObject()
    {
        return m_curlSharedObj;
    }
 
    CurlSharedObject::~CurlSharedObject()
    {
        curl_share_cleanup(m_curlSharedObj);
    }
    
    bool CurlSharedObject::IsExpired()
    {
        long long now = TimeUtils::GetCurrentSecond();
        return ((now - m_initTime) > RestConst::DNS_CACHE_TIMEOUT_SEC);
    }
    
    void CurlSharedObject::LockFunc(CURL *handle, curl_lock_data data, curl_lock_access access, void *userptr)
    {
        CurlSharedObject* sharedObj = static_cast<CurlSharedObject*>(userptr);
        if (sharedObj != nullptr)
        {
            sharedObj->Lock(data);
        }
        else
        {
            Logger::error("detect null user pointer in curl shared object lock function");
        }
    }
    
    void CurlSharedObject::UnlockFunc(CURL *handle, curl_lock_data data, void *userptr)
    {
        CurlSharedObject* sharedObj = static_cast<CurlSharedObject*>(userptr);
        if (sharedObj != nullptr)
        {
            sharedObj->Unlock(data);
        }
        else
        {
            Logger::error("detect null user pointer in curl shared object lock function");
        }
    }
    
    void CurlSharedObject::Lock(curl_lock_data data)
    {
        if (data == CURL_LOCK_DATA_DNS ||
            data == CURL_LOCK_DATA_SHARE)
        {
            m_sharedObjMtx.lock();
        }
        else
        {
            Logger::error("this lock data type not config as shared, please check!!!");
            m_sharedObjMtx.lock();
        }
    }
    
    void CurlSharedObject::Unlock(curl_lock_data data)
    {
        if (data == CURL_LOCK_DATA_DNS ||
            data == CURL_LOCK_DATA_SHARE)
        {
            m_sharedObjMtx.unlock();
        }
        else
        {
            Logger::error("this lock data type not config as shared, please check!!!");
            m_sharedObjMtx.unlock();
        }
    }
}
