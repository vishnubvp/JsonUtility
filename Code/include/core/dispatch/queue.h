

#ifndef queue_h
#define queue_h

#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <map>
#include <mutex>
#include <queue>
#include <atomic>
#include <vector>

#include "core/dispatch/semaphore.h"
#include "core/dispatch/task_block.h"
#include "core/dispatch/mthread.h"

#define SD_MAX_QUEUE_SIZE 7

namespace BBMobileSDK {
    
    class queue_ {
        
    public:
        queue_(const std::string & label, int width);
        ~queue_();
        
        // async task, add task into task_queue and return
        void add_task_async(task_block task);
        
        // sync task, add task into queue, wait until it run completely, and return
        void add_task_sync(task_block task);
        
        void start();
        
        int get_cur_task_count();
        
    private:
        std::string label_;
        
        semaphore queue_sema_;
        
        semaphore non_barrier_;
        
        std::vector<mthread> worker_threads_;
        
        // task adder lock
        semaphore task_adder_;
        
        // queue init flag, is 0 if there is nothing waiting in queue
        semaphore task_sema_;
        
        // add queue for task sequence
        std::queue<task_block> task_queue_;

        std::thread t_dispatch_;
        
        void dispatch();
        
        std::atomic<bool> should_stop_;
        
        std::atomic<int> task_count_;
        std::atomic<int> task_runned_count_;
    };
    
    typedef std::shared_ptr<queue_> queue;
}

#endif /* queue_h */
