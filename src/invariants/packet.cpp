#include "packet.h"

#include "utils/utils.h"

namespace NAMESPACE_NAME {

Packet::Packet():
    buffer(nullptr), data(nullptr), datalen(0) {}
    
Packet::Packet(uint8_t *buffer, size_t size): 
    buffer(buffer), data(nullptr), datalen(size) {}
    
Packet::Packet(const Packet &pkt): 
    buffer(pkt.buffer), data(pkt.data), datalen(pkt.datalen) {
    this->flag.byte = pkt.flag.byte;
}

Result<void> Packet::parse() {
    if (this->buffer == nullptr)
        return { Err::PacketNullBuffer};
    flag.byte = *buffer;
    data = buffer + 1;
    if(datalen >= headerLength())
        datalen --;
    else
        return {Err::PacketTooShort};
    return { Err::OK };
}

Result<void> Packet::dump(uint8_t *buffer) {
    if (this->buffer != nullptr)
        return { Err::PacketHavedBuffer };
    this->buffer = buffer;
    *buffer = flag.byte;
    if(datalen != 0)
        memcpy(buffer + 1,data,datalen);
    return { Err::OK };
}

bool Packet::canParsed() {
    if (buffer == nullptr)
        return false;
    return true;
}
size_t Packet::headerLength() {
    return 1;
}

}
