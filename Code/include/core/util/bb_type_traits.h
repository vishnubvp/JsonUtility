
#ifndef VsboardMobile_bb_type_traits_h
#define VsboardMobile_bb_type_traits_h

namespace BBMobileSDK
{
    template<class T, size_t N>
    constexpr size_t size_of_array(T (&)[N]) { return N; }
}

#endif /* VsboardMobile_bb_type_traits_h */
