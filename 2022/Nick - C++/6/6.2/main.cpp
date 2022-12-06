#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;
    std::getline(file, line, '\n');

    size_t startMarkerIndex = startOfMarker(line);
    std::cout << "Start of marker: " << startMarkerIndex + 1 << std::endl;

    file.close();

    return 0;
}

size_t startOfMarker(std::string buffer) {

    std::vector<char> marker;
    for(size_t index = 0; index < buffer.size(); index++) {
        marker.insert(marker.begin(), buffer[index]);
        if (marker.size() > MARKER_SIZE) marker.erase(marker.end()-1);
        if (isValidStartingMarker(marker, MARKER_SIZE)) return index;
    }

    return -1;
}

bool isValidStartingMarker(std::vector<char> marker, size_t expectedSize) {
    std::set<char> set(marker.begin(), marker.end());
    return set.size() == expectedSize;
}