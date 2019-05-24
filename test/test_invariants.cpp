#include "invariants.h"

#include <iostream>
#include <iomanip>
#include <new>

using namespace NAMESPACE_NAME;
using namespace std;

void test_long_packet() {
    LongPacket pkt;
    pkt.flag.detail.lors = 1;
    pkt.flag.detail.other = 0;
    // 前缀-加密协议(TLS/Disco)-ARQ-版本
    pkt.version = 0xC0011101;
    
    uint8_t dcid[] = {0x04,0x01,0x02,0x03,0x00};
    pkt.dcid = (CID*)dcid;
    
    uint8_t scid[] = {0x04,0x01,0x02,0x03,0x01};
    pkt.scid = (CID*)scid;
    
    uint8_t data[] = {0xff};
    pkt.data = data;
    pkt.datalen = 1;
    
    size_t size = pkt.headerLength() + 1;
    cout << "size is: " << size << endl;
    
    uint8_t *buffer = new uint8_t[size];
    
    pkt.dump(buffer);
    
    for (int i = 0; i != size; i++) {
        cout << setw(2) << setfill('0') << hex << (uint32_t) buffer[i] << " ";
    }
    
    cout << endl;
    
    Packet pkt1(buffer, size);
    
    if(pkt1.parse().err == Err::OK) {
        cout << "parse pkt1 success" << endl;
    }
    
    cout << "pkt1 data len: " << setw(2) << setfill('0') << hex << (uint32_t)pkt1.datalen << endl;

    LongPacket pkt2(pkt1);
    
    cout << "pkt1 data len: " << setw(2) << setfill('0') << hex << (uint32_t)pkt1.datalen << endl;

    if(pkt2.parse().err == Err::OK) {
        cout << "parse pkt2 success" << endl;
    }
    cout << "version: " << setw(2) << setfill('0') << hex << (uint32_t)pkt2.version << endl;
    cout << "dcidlen: " << setw(2) << setfill('0') << hex << (uint32_t)pkt2.dcid->len << endl;
    cout << "scidlen: " << setw(2) << setfill('0') << hex << (uint32_t)pkt2.scid->len << endl;
    cout << "pkt2 data len: " << setw(2) << setfill('0') << hex << (uint32_t)pkt2.datalen << endl;
}

void test_short_packet() {
    ShortPacket pkt;
    pkt.flag.detail.lors = 1;
    pkt.flag.detail.other = 0;
    
    uint8_t dcid[] = {0x01,0x02,0x03,0x04};
    
    pkt.dcidlen = 4;
    pkt.dcid = dcid;
    
    size_t size = pkt.headerLength();
    cout << "size is: " << size << endl;
    
    uint8_t *buffer = new uint8_t[size];
    
    pkt.dump(buffer);
    
    for (int i = 0; i != size; i++) {
        cout << setw(2) << setfill('0') << hex << (uint32_t) buffer[i] << " ";
    }
    
    cout << endl;
    
    Packet pkt1(buffer, size);
    
    if(pkt1.parse().err == Err::OK) {
        cout << "parse pkt1 success" << endl;
    }
    
    ShortPacket pkt2(pkt1);
    pkt2.dcidlen = 4;
    
    if(pkt2.parse().err == Err::OK) {
        cout << "parse pkt2 success" << endl;
    }
    
    cout << "lors: "    << setw(2) << setfill('0') << hex << (uint32_t)pkt2.flag.byte << endl;
  
}

void test_vernego() {
    
    VersionNegotiationPacket pkt;
    pkt.flag.detail.lors = 1;
    pkt.flag.detail.other = 0;
    // 前缀-加密协议(TLS/Disco)-ARQ-版本
    pkt.version = 0xC0011101;
    
    uint8_t dcid[] = {0x04,0x01,0x02,0x03,0x00};
    pkt.dcid = (CID*)dcid;
    
    uint8_t scid[] = {0x04,0x01,0x02,0x03,0x01};
    pkt.scid = (CID*)scid;
    
    pkt.versions.push_back(0x00000001);
    pkt.versions.push_back(0x00000002);
    pkt.versions.push_back(0x00000003);
    pkt.versions.push_back(0x00000004);
    pkt.versions.push_back(0x00000005);
    pkt.versions.push_back(0x00000006);
    pkt.versions.push_back(0x00000007);
    pkt.versions.push_back(0x00000008);
    
    size_t size = pkt.headerLength();
    cout << "size is: " << size << endl;
    
    uint8_t *buffer = new uint8_t[size];
    
    pkt.dump(buffer);
    
    for (int i = 0; i != size; i++) {
        cout << setw(2) << setfill('0') << hex << (uint32_t) buffer[i] << " ";
    }
    
    cout << endl;
    
    Packet pkt1(buffer, size);
    if(pkt1.parse().err == Err::OK) {
        cout << "parse Packet success" << endl;
        cout << "pkt1 data len: " << setw(2) << setfill('0') << hex << (uint32_t)pkt1.datalen << endl;
    }
    

    LongPacket longpkt1(pkt1);
    auto res = longpkt1.parse();
    if(res.err == Err::OK) {
        cout << "parse LongPacket success" << endl;
        cout << "version: " << setw(2) << setfill('0') << hex << (uint32_t)longpkt1.version << endl;
        cout << "dcidlen: " << setw(2) << setfill('0') << hex << (uint32_t)longpkt1.dcid->len << endl;
        cout << "scidlen: " << setw(2) << setfill('0') << hex << (uint32_t)longpkt1.scid->len << endl;
        cout << "pkt2 data len: " << setw(2) << setfill('0') << hex << (uint32_t)longpkt1.datalen << endl;
    }

    VersionNegotiationPacket vnpkt1(longpkt1);
    if(vnpkt1.parse().err == Err::OK) {
        cout << "parse VNPacket success" << endl;
        for(auto &x: vnpkt1.versions) {
            cout << x << endl;
        }
    } 
    
    
}

int main() {
    test_long_packet();
    cout << "---------------" << endl;
    test_short_packet();
    cout << "---------------" << endl;
    test_vernego();
    return 0;
}


