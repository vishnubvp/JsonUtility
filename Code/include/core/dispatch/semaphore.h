

#ifndef semaphore_h
#define semaphore_h

#include <memory>
#include <mutex>
#include <condition_variable>

namespace VSTestSDK {

    
#define SD_TIME_NOW 0ull
#define SD_TIME_FOREVER ~0ull
    
    class semaphore_ {
        
    public:
        semaphore_(int count = 1);
        ~semaphore_();
        
        void signal();
        
        int wait(unsigned long long timeout = SD_TIME_FOREVER);
        int wait_all(unsigned long long timeout = SD_TIME_FOREVER);
        int available_res_count();
        
    private:
        std::mutex mutex_;
        std::condition_variable condition_var_;
        volatile int count_;
        int raw_count_;
    };
    
    typedef std::shared_ptr<semaphore_> semaphore;
}


#endif /* semaphore_h */
