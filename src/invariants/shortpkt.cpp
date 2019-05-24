#include "shortpkt.h"

#include "utils/utils.h"

namespace NAMESPACE_NAME {

ShortPacket::ShortPacket():
    Packet(), dcid(nullptr), dcidlen(0),
    data(nullptr), datalen(0) {}
    
ShortPacket::ShortPacket(Packet &pkt):
    Packet(pkt), dcid(nullptr), dcidlen(0),
    data(nullptr), datalen(0) {}
    
ShortPacket::ShortPacket(const ShortPacket &pkt):
    Packet(pkt), dcid(pkt.dcid), dcidlen(pkt.dcidlen),
    data(pkt.data), datalen(pkt.datalen) {}
    
bool ShortPacket::canParsed() {
    return flag.detail.lors == 0;
}

Result<void> ShortPacket::parse() {
    uint8_t *pb = Packet::data;
    
    // Parse destination CID
    dcid = pb;
    pb += dcidlen;
    
    // Parse data
    data = pb;
    if(datalen >= headerLength())
        datalen -= headerLength();
    else
        return {Err::PacketTooShort};
    return { Err::OK };
}

Result<void> ShortPacket::dump(uint8_t *buffer) {
    uint8_t *pb = buffer;
    if (this->buffer != nullptr)
        return { Err::PacketHavedBuffer };
    Packet::dump(pb);
    pb += Packet::headerLength();
    
    if(dcidlen != 0)
        memcpy(pb,dcid,dcidlen);
    pb += dcidlen;
    
    if(datalen != 0)
        memcpy(pb,data,datalen);
    return { Err::OK };
}

size_t ShortPacket::headerLength() {
    return Packet::headerLength() + dcidlen;
}

}
