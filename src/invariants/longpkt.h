#ifndef CQUIC_INVARIANTS_LONGPKT_H
#define CQUIC_INVARIANTS_LONGPKT_H

#include "packet.h"

namespace NAMESPACE_NAME {

struct CID {
    uint8_t len;
    uint8_t id[0];
} MEM_ALIGN;

class LongPacket: public Packet {
    public:
        uint32_t  version;
        CID      *dcid;
        CID      *scid;
        uint8_t  *data;
        size_t    datalen;
    public:
        LongPacket();
        LongPacket(Packet &);
        LongPacket(const LongPacket &);
        ~LongPacket() = default;
    public:
        bool canParsed();
        Result<void> parse();
        Result<void> dump(uint8_t *);
        size_t headerLength();
};

}

#endif

