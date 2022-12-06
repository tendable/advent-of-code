#pragma once
#include <string>
#include <vector>

#define MARKER_SIZE 4

size_t startOfMarker(std::string buffer);
bool isValidStartingMarker(std::vector<char> marker);