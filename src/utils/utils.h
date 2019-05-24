#ifndef CQUIC_UTILS_UTILS
#define CQUIC_UTILS_UTILS

#include "config.h"

namespace NAMESPACE_NAME {

template <class T>
constexpr auto hton(T x) -> T {
#if CQUIC_BYTE_ORDER == CQUIC_BYTE_BIG_ENDIAN
    return x;
#else
    decltype(x) y;
    uint8_t *px = (uint8_t*)(&x);
    uint8_t *py = (uint8_t*)(&y);
    const size_t len = sizeof(T);
    for (int i = 0; i != len; i++) {
        py[i] = px[len - 1 -i];
    }
    return y;
#endif

}

}

#endif
