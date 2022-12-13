#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include "main.h"

int main() {

    std::ifstream file("input");

    size_t packetIndex = 1;
    size_t sumOfCorrectPackets = 0;
    while(!file.eof()) {
        PacketPair pair = readPacketPair(&file);
        bool isOrderCorrect = comparePackets(pair.first, pair.second);
        sumOfCorrectPackets += isOrderCorrect * packetIndex;
        std::cout << "Packet " << packetIndex << ": " << (isOrderCorrect ? "True" : "False") << std::endl;
        packetIndex++;
    }
    std::cout << "Sum: " << sumOfCorrectPackets << std::endl;

    file.close();

    return 0;
}

bool leftLessThanOrEqualRight(Element* left, Element* right) {
    if (left->type == ElementType::array && right->type == ElementType::array) {
        // both are arrays
        return comparePackets(left->array, right->array);
    } else if (left->type == ElementType::number && right->type == ElementType::number) {
        // both are numbers
        return left->value <= right->value;
    } else {
        // one of them is a number
        if (left->type == ElementType::number) {
            Packet* leftPacket = new Packet();
            leftPacket->insert(leftPacket->end(), left);
            return comparePackets(leftPacket, right->array);
        } else {
            Packet* rightPacket = new Packet();
            rightPacket->insert(rightPacket->end(), right);
            return comparePackets(left->array, rightPacket);
        }
    }
}

bool comparePackets(Packet* left, Packet* right) {
    for (size_t leftIndex = 0; leftIndex < left->size(); leftIndex++) {
        if (leftIndex >= right->size()) {
            // we've run out of elements in the right array
            return false;
        }

        bool leftLTERight = leftLessThanOrEqualRight((*left)[leftIndex], (*right)[leftIndex]);
        bool rightLTELeft = leftLessThanOrEqualRight((*right)[leftIndex], (*left)[leftIndex]);
        bool leftEQRight = leftLTERight && rightLTELeft;
        if (leftEQRight) {
            // the two elements are the same
            continue;
        } else {
            return leftLTERight;
        }
    }
    
    // we've run out of elements in the left array
    return true;
}

PacketPair readPacketPair(std::ifstream* file) {
    std::string packetAString, packetBString, empty;
    std::getline(*file, packetAString, '\n');
    std::getline(*file, packetBString, '\n');
    if(!file->eof()) {
        std::getline(*file, empty, '\n');
    }

    return PacketPair(getPacket(packetAString), getPacket(packetBString));
}

Packet* getPacket(std::string packetString) {
    Packet* result = new Packet();

    packetString.erase(packetString.begin());
    packetString.erase(packetString.end() - 1);

    // remove any leading ]
    packetString.erase(0, packetString.find_first_not_of(']'));

    Element* element;
    while(element = getElement(&packetString)) {
        result->insert(result->end(), element);
    }

    return result;
}

size_t endBracketLocation(std::string packetWithStartingBracket) {
    int numberOfOpenBrackets = 1;
    for(size_t i = 1; i < packetWithStartingBracket.size(); i++) {
        if (packetWithStartingBracket[i] == '[') numberOfOpenBrackets++;
        else if (packetWithStartingBracket[i] == ']') numberOfOpenBrackets--;

        if (numberOfOpenBrackets == 0) {
            return i;
        }
    }
}

Element* getElement(std::string* packetString) {
    Element* result = new Element();

    if (packetString->empty()) {
        return nullptr;
    } else if ((*packetString)[0] == '[') {
        // Must be an array, we need to find the [...] substring for it
        size_t endBracketIndex = endBracketLocation(*packetString);
        std::string subPacketString = packetString->substr(0, endBracketIndex + 1);
        result->type = ElementType::array;
        result->array = getPacket(subPacketString);
        packetString->erase(0, endBracketIndex  + 2);
    } else {
        // Must be a number, find if it's delimited by , or ]
        auto commaIndex = packetString->find(',');
        auto endBracketIndex = packetString->find(']');
        bool isCommaNext = commaIndex < endBracketIndex;
        char nextSeparator = isCommaNext ? ',' : ']';
        auto nextSeparatorIndex = isCommaNext ? commaIndex : endBracketIndex;
        
        std::string number;
        std::stringstream ss(*packetString);
        std::getline(ss, number, nextSeparator);

        result->type = ElementType::number;
        result->value = std::stoi(number);
        *packetString = packetString->substr(commaIndex == endBracketIndex ? packetString->size() : nextSeparatorIndex + 1 , packetString->size());
    }

    return result;
}