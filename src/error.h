#ifndef CQUIC_ERROR_H
#define CQUIC_ERROR_H

namespace NAMESPACE_NAME {

enum class Err {
    OK,
    PacketParseErr,
    PacketHavedBuffer,
    PacketNullBuffer,
    PacketTooShort
};

template<class T>
struct Result {
    Err err;
    T result;
};

template<>
struct Result<void> {
    Err err;
};

}

#endif
