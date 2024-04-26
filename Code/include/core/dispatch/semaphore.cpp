

#include "core/dispatch/semaphore.h"
#include "core/dispatch/log.h"

namespace VSTestSDK {
        
    semaphore_::semaphore_(int count)
    : count_(count)
    , raw_count_(count)
    {
        
    }
    
    semaphore_::~semaphore_()
    {
        
    }
    
    void semaphore_::signal()
    {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            ++count_;
        }
        
        condition_var_.notify_one();
    }
    
    int semaphore_::wait(unsigned long long timeout)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        auto now = std::chrono::system_clock::now();
        
        bool success = false;
        
        if (timeout == SD_TIME_FOREVER) {
            condition_var_.wait(lock, [this]() {
                return count_;
            });
            success = true;
        } else {
            success = condition_var_.wait_until(lock, now + std::chrono::milliseconds(timeout), [this](){
                return count_;
            });
        }
        
        if (count_ > 0)
            --count_;
        
        return !success;    // error
    }
    
    int semaphore_::wait_all(unsigned long long timeout)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        auto now = std::chrono::system_clock::now();
        
        bool success = false;
        
        if (timeout == SD_TIME_FOREVER) {
            condition_var_.wait(lock, [this]() {
                return count_ >= raw_count_;
            });
            success = true;
        } else {
            success = condition_var_.wait_until(lock, now + std::chrono::milliseconds(timeout), [this](){
                return count_ == raw_count_;
            });
        }
        
        if (count_ > 0)
            --count_;
        
        return !success;    // error

    }
    
    int semaphore_::available_res_count()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return count_;
    }

}
