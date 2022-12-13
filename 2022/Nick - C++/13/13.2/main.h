#pragma once
#include <string>
#include <vector>

#define Packet std::vector<Element*>
#define PacketPair std::pair<Packet*, Packet*>

#define DIVIDER_PACKET_1_VALUE 2
#define DIVIDER_PACKET_2_VALUE 6
#define DIVIDER_PACKET_1 "[[2]]"
#define DIVIDER_PACKET_2 "[[6]]"

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
bool leftLessThanRight(Element* left, Element* right);