

#ifndef task_block_h
#define task_block_h

#include <memory>
#include "core/dispatch/semaphore.h"

namespace BBMobileSDK
{
    class task_block_
    {
    public:
        virtual ~task_block_() {}
        virtual void execute() = 0;
        virtual bool is_barrier() = 0;
        virtual bool is_sync() = 0;
        virtual semaphore get_accomplished_sema() = 0;
    };
    
    typedef std::shared_ptr<task_block_> task_block;
    
    template <typename Function_T>
    class function_task_block_ : public task_block_
    {
    public:
        function_task_block_(Function_T function, bool is_sync = false, bool is_barrier = false)
        : function_(function)
        , is_sync_(is_sync)
        , is_barrier_(is_barrier)
        , accomplished_sema_(new semaphore_(0))
        {};
        
        virtual ~function_task_block_() {}
        
        bool is_barrier()
        {
            return is_barrier_;
        }
        
        bool is_sync()
        {
            return is_sync_;
        }
        
        void execute()
        {
            function_();
        }
        
        semaphore get_accomplished_sema()
        {
            return accomplished_sema_;
        }
        
    private:
        Function_T function_;
        bool is_sync_;
        bool is_barrier_;
        semaphore accomplished_sema_;
    };
    
    template <typename Function_T>
    using function_task_block =  typename std::shared_ptr<function_task_block_<Function_T> > ;
}



#endif /* task_block_h */
