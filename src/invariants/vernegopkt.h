#ifndef CQUIC_INVARIANTS_VERNEGOPKT_H
#define CQUIC_INVARIANTS_VERNEGOPKT_H

#include "longpkt.h"

namespace NAMESPACE_NAME {

class VersionNegotiationPacket: public LongPacket {
    public:
        vector<uint32_t> versions;
    public:
        VersionNegotiationPacket() = default;
        VersionNegotiationPacket(const LongPacket &);
        VersionNegotiationPacket(const VersionNegotiationPacket &);
        ~VersionNegotiationPacket() = default;
    public:
        bool canParsed();
        Result<void> parse();
        Result<void> dump(uint8_t *);
        size_t headerLength();
};

}

#endif