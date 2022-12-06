#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;

    long sumOfPriorities = 0;
    while(std::getline(file, line, '\n')) {
        unsigned int priority = commonPriority(line);
        sumOfPriorities += priority;
    }

    std::cout << "Sum of priorities: " << sumOfPriorities << std::endl;
    
    file.close();

    return 0;
}

unsigned int priority(char character) {
    if (character <= 90) {
        // std::cout << character << ": " << character - 38 << std::endl;
        return character - 38;
    } else {
        // std::cout << character << ": " << character - 96 << std::endl;
        return character - 96;
    }
}

unsigned int commonPriority(std::string line) {
    size_t halfLength = line.length() / 2;

    std::vector<char> pocket1(line.begin(), line.end() - halfLength);
    std::sort(pocket1.begin(), pocket1.end());
    std::vector<char> pocket2(line.begin() + halfLength, line.end());
    std::sort(pocket2.begin(), pocket2.end());
    std::vector<char> intersection;
 
    std::set_intersection(pocket1.begin(), pocket1.end(), pocket2.begin(), pocket2.end(), std::inserter(intersection, intersection.begin()));

    return priority(intersection[0]);

    std::string p1s(pocket1.begin(), pocket1.end());
    std::string p2s(pocket2.begin(), pocket2.end());
    std::string is(intersection.begin(), intersection.end());
    std::cout << "Pocket1: " << p1s << "\nPocket2: " << p2s << "\nIntersection: " << is << std::endl << std::endl;
    return 0;
}