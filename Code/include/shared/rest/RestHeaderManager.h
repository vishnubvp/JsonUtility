

#ifndef VsboardMobile_RestHeaderManager_h
#define VsboardMobile_RestHeaderManager_h

#include <thread>

#include "core/util/SingletonBase.h"

namespace VSTestSDK
{
    BB_FORWARD_DECLARE(RestHeaderField);
    
    class RestHeaderManager : public SingletonBase<RestHeaderManager>
    {
        friend class SingletonBase<RestHeaderManager>;
        
    public:
        ~RestHeaderManager();
        
        RestHeaderFieldVPtr GetHeaders();
        void RefreshHeader();
        
    private:
        RestHeaderManager();
        RestHeaderManager(RestHeaderManager const&)             = delete;
        RestHeaderManager& operator=(RestHeaderManager const&)  = delete;
        
        void AddObserver();
        std::recursive_mutex m_mtx;
        RestHeaderFieldVPtr m_restHeaders;
    };
}

#endif /* VsboardMobile_RestHeaderManager_h */
