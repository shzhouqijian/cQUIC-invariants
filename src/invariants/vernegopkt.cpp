#include "vernegopkt.h"

#include "utils/utils.h"

namespace NAMESPACE_NAME {

VersionNegotiationPacket::VersionNegotiationPacket(const LongPacket &pkt):
    LongPacket(pkt) {}

VersionNegotiationPacket::VersionNegotiationPacket(const VersionNegotiationPacket &pkt):
    LongPacket(pkt) {}

bool VersionNegotiationPacket::canParsed() {
    return version == 0x0;
}

Result<void> VersionNegotiationPacket::parse() {
    if(LongPacket::data == nullptr)
        return { Err::PacketNullBuffer };
    
    uint8_t *pb = LongPacket::data;
    size_t length = LongPacket::datalen;
    
    do {
        uint32_t version = hton(*((uint32_t*) pb));
        pb += 4;
        length -= 4;
        versions.push_back(version);
    } while (length >= 4);
    
    return { Err::OK };
}

Result<void> VersionNegotiationPacket::dump(uint8_t *buffer) {
    uint8_t *pb = buffer;
    LongPacket::dump(pb);
    pb += LongPacket::headerLength();
    
    for (auto &x: versions) {
        uint32_t version = hton(x);
        memcpy(pb, (uint8_t*)&version, 4);
        pb += 4;
    }
    
    return { Err::OK };
}

size_t VersionNegotiationPacket::headerLength() {
    return LongPacket::headerLength() + versions.size() * 4;
}

}
