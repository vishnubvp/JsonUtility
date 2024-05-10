

#ifndef SINGLETONBASE_H_
#define SINGLETONBASE_H_

#include "core/util/BaseInclude.h"

namespace BBMobileSDK
{
    template <class T>
    class SingletonBase
    {
        
    public:
        template <class ...Args>
        static T & GetInstance(Args... args)
        {
            static T *ins = new T(args...);
            return *ins;
        }
        
    protected:
        template <class ...Args>
        SingletonBase(Args... args){}
        SingletonBase() {}
        virtual ~SingletonBase() {}
        
    private:
        SingletonBase(const SingletonBase&) = delete;
        const SingletonBase& operator=(const SingletonBase&) = delete;
    };
}

#endif /* SINGLETONBASE_H_ */
