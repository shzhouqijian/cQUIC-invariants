#include "longpkt.h"

#include "utils/utils.h"

namespace NAMESPACE_NAME {

// Long Packet class
LongPacket::LongPacket(): 
    Packet(), version(0), dcid(nullptr), 
    scid(nullptr), data(nullptr), datalen(0) {}
    
LongPacket::LongPacket(Packet &pkt):
    Packet(pkt), version(0), dcid(nullptr), 
    scid(nullptr), data(nullptr), datalen(pkt.datalen) {}
    
LongPacket::LongPacket(const LongPacket &pkt): 
    Packet(pkt), version(pkt.version), dcid(pkt.dcid),
    scid(pkt.scid), data(pkt.data), datalen(pkt.datalen) {}
    
bool LongPacket::canParsed() {
    return flag.detail.lors == 1;
}

Result<void> LongPacket::parse() {
    if(Packet::data == nullptr)
        return { Err::PacketNullBuffer };
    
    uint8_t *pb = Packet::data;
    // Parse version
    version = hton(*((uint32_t *)pb));
    pb += 4;
    
    // Parse destination CID
    dcid = (CID*)pb;
    pb += dcid->len + 1;
    
    // Parse source CID
    scid = (CID*)pb;
    pb += scid->len + 1;
    
    // Parse data
    data = pb;
    size_t diff = headerLength() - Packet::headerLength();
    if(datalen >= diff)
        datalen -= diff;
    else
        return {Err::PacketTooShort};
    
    CDEBUG(datalen);
    return { Err::OK };
}

Result<void> LongPacket::dump(uint8_t *buffer) {
    if (this->buffer != nullptr)
        return { Err::PacketHavedBuffer };
    uint8_t *pb = buffer;
    // Dump packet
    Packet::dump(pb);
    pb += Packet::headerLength();
    
    // Dump version
    uint32_t v = hton(this->version);
    memcpy(pb, (uint8_t*)(&v), 4);
    pb += 4;
    
    // Dump destination CID
    memcpy(pb, dcid, dcid->len + 1);
    pb += dcid->len + 1;
    
    // Parse source CID
    memcpy(pb, scid, scid->len + 1);
    pb += scid->len + 1;
    
    if(datalen != 0)
        memcpy(pb,data,datalen);
    
    return { Err::OK };
}

size_t LongPacket::headerLength() {
    return 4 + dcid->len + 1 + scid->len + 1 + Packet::headerLength();
}

}
