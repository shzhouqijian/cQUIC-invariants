#ifndef CQUIC_INVARIANTS_PACKET_H
#define CQUIC_INVARIANTS_PACKET_H

#include "config.h"
#include "error.h"

namespace NAMESPACE_NAME {

union Flag {
    uint8_t byte;
    struct {
        uint8_t other:7;
        uint8_t lors:1;
    } detail;
} MEM_ALIGN;

class Packet {
    public:
        Flag       flag;
        uint8_t   *data;
        size_t     datalen;
    protected:
        uint8_t   *buffer;
    public:
        Packet();
        Packet(uint8_t *, size_t);
        Packet(const Packet &);
        ~Packet() = default;
    public:
        Result<void> parse();
        Result<void> dump(uint8_t *);
        bool canParsed();
        size_t headerLength();
};

}

#endif

