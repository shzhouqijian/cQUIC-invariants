#ifndef CQUIC_INVARIANTS_SHORTPKT_H
#define CQUIC_INVARIANTS_SHORTPKT_H

#include "packet.h"

namespace NAMESPACE_NAME {

class ShortPacket: public Packet {
    public:
        uint8_t  *dcid;
        uint8_t   dcidlen;
        uint8_t  *data;
        size_t    datalen;
    public:
        ShortPacket();
        ShortPacket(Packet &);
        ShortPacket(const ShortPacket &);
        ~ShortPacket() = default;
    public:
        bool canParsed();
        Result<void> parse();
        Result<void> dump(uint8_t *);
        size_t headerLength();
};

}

#endif

