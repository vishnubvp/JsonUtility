
#ifndef NotificationCenter_h
#define NotificationCenter_h

#include "core/util/BaseInclude.h"

namespace BBMobileSDK
{
    typedef std::string event_t;
    typedef void * observer_t;
    typedef void * payload_t;
    typedef std::function<void(payload_t)> selector_t;
    typedef int selector_id_t;
    
    typedef struct {
        observer_t observer;
        selector_t selector;
        selector_id_t selector_id;
    } observer_note_s;
    
    typedef std::vector<observer_note_s> observer_note_list_t;
    typedef std::shared_ptr<std::vector<observer_note_s>> observer_note_list_p;
    
    class NotificationCenter
    {
    public:
        // must have an observer(instance)
        // selector can be member method or lambda, will be copied
        static void AddObserver(const event_t & name, const observer_t & observer, const selector_t selector, const selector_id_t selector_id = INT_MAX);
        
        // remove observer by name and instance reference
        static void RemoveObserver(const event_t & name, const observer_t & observer, const selector_id_t selector_id = INT_MAX);
        
        // post notification
        static void PostNotification(const event_t & name);
        static void PostNotification(const event_t & name, const payload_t payload);
        
        // TODO add observer for static method and return an observer
        //        observer_t AddObserver(const std::string & name, const selector_t selector);
    };
}

#endif /* NotificationCenter_h */

