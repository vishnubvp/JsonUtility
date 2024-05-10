

#ifndef BBTYPEDEFS_H_
#define BBTYPEDEFS_H_

#include "core/util/BaseInclude.h"

#include <mutex>

#define GLB_SMART_PTR_DEF(NAME)										\
	typedef SMART_PTR::shared_ptr<NAME> NAME##Ptr;					\
	typedef SMART_PTR::weak_ptr<NAME>   NAME##WPtr;					\
    typedef SMART_PTR::unique_ptr<NAME> NAME##UPtr;					\


#define GLB_SMART_VEC_PTR_DEF(NAME)                                 \
	typedef std::vector< SMART_PTR::shared_ptr<NAME> > NAME##VPtr;  \
	typedef SMART_PTR::shared_ptr< NAME##VPtr > NAME##PVPtr;        \

#define BB_FORWARD_DECLARE(NAME) \
    class NAME;\
    GLB_SMART_PTR_DEF(NAME)\
    GLB_SMART_VEC_PTR_DEF(NAME)

typedef std::unique_lock<std::mutex> BBScopeLock;
#define BBScopeLock(x) static_assert(false, "pass mutex to init lock")
typedef std::unique_lock<std::recursive_mutex> BBRecursiveScopeLock;
#define BBRecursiveScopeLock(x) static_assert(false, "pass mutex to init lock")
typedef std::pair<std::string, std::string> KVPair;

#define BB_RELEASE(p) \
    do {\
        if (p) {\
            free(p); \
            p = NULL;\
								        }\
				    } while(0)


#define BB_CALLBACK_DEF(name, android_name, ret_type, params, ...) \
    typedef std::function<ret_type (params, ##__VA_ARGS__)> sf_callback_##name; \
    typedef ret_type (* pf_callback_##name) (params, ##__VA_ARGS__); \
    typedef pf_callback_##name android_name


// STR_VALUE(arg) == "arg"
#define STRINGIZER(arg)         #arg
#define STR_VALUE(arg)          STRINGIZER(arg)
#define BB_LABEL(name)          "com.blackboard.Serverbaas-sdk." STR_VALUE(name)

#define BB_THREAD_LABEL(name)   "com.blackboard.Serverbaas-sdk.threads." STR_VALUE(name)

#define REVERT_THREADPOOL 1

// change to public when enable unit test
#ifdef GTEST
#define private public
#define protected public
#define GTEST_API virtual
#else
#define GTEST_API
#endif

using const_string = const char* const;

//
// typeof is for C++ and __typeof__ works for C
// (void) (&_x1 == &_x2); can report an error / a warning if they two are in different types
//
#ifdef _WIN32
#define BB_MIN(a, b) (((a) < (b)) ? (a) : (b))
#else
#define BB_MIN(x, y) ({ \
    __typeof__(x) _min1 = (x); \
    __typeof__(y) _min2 = (y); \
    (void) (&_min1 == &_min2); \
    _min1 < _min2 ? _min1 : _min2; })
#endif

#ifdef _WIN32
#define BB_MAX(a, b) (((a) > (b)) ? (a) : (b))
#else
#define BB_MAX(x, y) ({ \
    __typeof__(x) _max1 = (x); \
    __typeof__(y) _max2 = (y); \
    (void) (&_max1 == &_max2); \
    _max1 > _max2 ? _max1 : _max2; })
#endif

#endif /* BBTYPEDEFS_H_ */
