#pragma once
#include <string>
#include <vector>

#define Packet std::vector<Element*>
#define PacketPair std::pair<Packet*, Packet*>

enum ElementType { array, number };
struct Element {
    public:
        ElementType type;
        union {
            std::vector<Element*>* array;
            int value;      
        };

        Element() { }
        ~Element() { if(type == ElementType::array) delete array; }
};

PacketPair readPacketPair(std::ifstream* file);
Element* getElement(std::string* packet);
Packet* getPacket(std::string packetString);
bool comparePackets(Packet* left, Packet* right);