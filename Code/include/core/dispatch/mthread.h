

#ifndef mthread_h
#define mthread_h

#include <thread>
#include <memory>
#include <atomic>
#include <mutex>

#include "core/dispatch/semaphore.h"
#include "core/dispatch/task_block.h"

namespace BBMobileSDK
{
    typedef std::function<void ()> mfunction_t;
    
    class mthread_
    {
    public:

        mthread_();
        ~mthread_();
        
        void add_task(mfunction_t task, mfunction_t completion);
        
        std::atomic<bool> is_running_;
        std::thread thread_;

    private:
        semaphore task_sema_;
        semaphore stopped_sema_;
        std::mutex mtx_;
        std::atomic<bool> should_stop_;
        
        mfunction_t task_;
        mfunction_t completion_;
        
        void start_thread();
        void stop_thread();
    };
    
    typedef std::shared_ptr<mthread_> mthread;
}

#endif /* mthread_h */
