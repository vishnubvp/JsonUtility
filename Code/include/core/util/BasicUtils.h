

#ifndef BasicUtils_h
#define BasicUtils_h

#include <algorithm>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <set>
#include <mutex>
#include <ctime>

#include "core/util/bb_type_traits.h"

namespace BBMobileSDK
{
    class BasicUtils
    {
    public:
        static int GetHammingWeight(unsigned int n);
        
        static inline std::string GetThreadId()
        {
            std::stringstream ss;
            ss << std::this_thread::get_id();
            return ss.str();
        }
        
        template <typename ElementType, typename Predicate>
        static void EraseIf(std::set<ElementType> &s, Predicate pred)
        {
            typename std::set<ElementType>::iterator it = s.begin();
            for (;;)
            {
                it = std::find_if(it, s.end(), pred);
                if (it == s.end())
                    break;
                it = s.erase(it);
            }
        }
        
        template <typename ElementType, typename Predicate>
        static void EraseIf(std::vector<ElementType>& vec, Predicate pred)
        {
            vec.erase(std::remove_if(vec.begin(), vec.end(), pred), vec.end());
        }
        
        template <typename ElementType, typename Predicate>
        static void EraseIf(std::shared_ptr<std::vector<ElementType> > pv, Predicate pred)
        {
            pv->erase(std::remove_if(pv->begin(), pv->end(), pred), pv->end());
        }
        
        template <typename K, typename V>
        static std::vector<K> KeyVec(const std::map<K, V> & map)
        {
            std::vector<K> kv;
            for (typename std::map<K, V>::const_iterator it = map.begin(); it != map.end(); ++it)
            {
                kv.push_back(it->first);
            }
            return kv;
        }
        
        template <typename K, typename V>
        static std::vector<V> ValueVec(const std::map<K, V> & map)
        {
            std::vector<V> vv;
            for (typename std::map<K, V>::const_iterator it = map.begin(); it != map.end(); ++it)
            {
                vv.push_back(it->second);
            }
            return vv;
        }
        
        template <class InputIt, class T>
        static typename std::iterator_traits<InputIt>::difference_type CalcDistance(InputIt first, InputIt last, const T& value)
        {
            auto pos = std::find(first, last, value);
            return std::abs(std::distance(pos, first));
        }
        
        template <typename T>
        static std::vector<typename std::remove_const<T>::type> ArrayToVec(T* array, int arraySize)
        {
            if (arraySize <= 0 || array == nullptr) return {};
            
            return std::vector<typename std::remove_const<T>::type>(array, array + arraySize);
        }
        
        static std::string GetRandomNumAsStr(int max = INT_MAX)
        {
            static std::once_flag flag;
            std::call_once(flag, []() {
                std::srand(static_cast<unsigned>(std::time(0)));
            });
            
            int random = std::rand() % max;
            std::stringstream ss;
            ss << random;
            return ss.str();
        }
        
        template <typename arrayType>
        static const char* GetValueInArray(int index, arrayType& array)
        {
            if (index < 0 ||
                index > size_of_array(array) - 1)
            {
                return "";
            }
            return array[index];
        }
    };
}

#endif /* BasicUtils_h */

