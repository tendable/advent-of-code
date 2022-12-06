#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;

    int numberOfPairs = 0;
    while(std::getline(file, line, '\n')) {
        std::stringstream stringStream(line);
        std::string pair1, pair2;
        std::getline(stringStream, pair1, ',');
        std::getline(stringStream, pair2, ',');
        numberOfPairs += pairFullyContainsOtherPair(pair1, pair2) ? 1 : 0;
    }
    
    std::cout << "Result: " << numberOfPairs << std::endl;

    file.close();

    return 0;
}

void pairToInts(std::string pair, unsigned int* a, unsigned int* b) {
    std::stringstream stringStream(pair);
    std::string aString, bString;
    std::getline(stringStream, aString, '-');
    std::getline(stringStream, bString, '-');

    *a = stoi(aString);
    *b = stoi(bString);
}

bool pairFullyContainsOtherPair(std::string pair1, std::string pair2) {
    unsigned int a,b,c,d;
    pairToInts(pair1, &a, &b);
    pairToInts(pair2, &c, &d);
    bool pair1ContainsPair2 = a <= c && c <= d && d <= b;
    bool pair2ContainsPair1 = c <= a && a <= b && b <= d;
    return pair1ContainsPair2 || pair2ContainsPair1;
}