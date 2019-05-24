#ifndef CQUIC_CONFIG_H
#define CQUIC_CONFIG_H

#define CQUIC_BYTE_BIG_ENDIAN     0
#define CQUIC_BYTE_LITTLE_ENDIAN  1

#define CQUIC_BYTE_ORDER CQUIC_BYTE_LITTLE_ENDIAN

#define NAMESPACE_NAME cquic

#define MEM_ALIGN __attribute__((packed))

#include <cstdint>
using std::uint8_t;

#include <cstddef>
using std::size_t;

#include <cstring>
using std::memcpy;

#include <vector>
using std::vector;

#define CQUIC_DEBUG 1

#if CQUIC_DEBUG == 1

#include <iostream>

#define CDEBUG(x) std::cout << x << std::endl

#endif

#endif

