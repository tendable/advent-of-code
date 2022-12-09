#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;
    std::vector< std::vector<int> > grid;

    std::vector<int> currentLine;

    while(std::getline(file, line, '\n')) {
        currentLine = std::vector<int>();
        for (size_t index = 0; index < line.length(); index++) {
            currentLine.insert(currentLine.end(), line[index] - '0');
        }
        grid.insert(grid.end(), currentLine);
    }

    std::vector< std::vector<bool> > visibleTrees(grid.size(), std::vector<bool>(grid[0].size(), false));
    
    for (size_t y = 0; y < visibleTrees.size(); y++) {
        std::vector<bool> horizontallyVisibleTrees = lineOfVisibleTrees(grid[y]);
        for (size_t x = 0; x < visibleTrees[y].size(); x++) {
            visibleTrees[y][x] = visibleTrees[y][x] || horizontallyVisibleTrees[x];
        }
    }

    int result = 0;

    for (size_t x = 0; x < visibleTrees[0].size(); x++) {
        std::vector<int> verticalLineOfTrees;
        for (size_t y = 0; y < visibleTrees.size(); y++) {
            verticalLineOfTrees.insert(verticalLineOfTrees.end(), grid[y][x]);
        }
        std::vector<bool> verticallyVisibleTrees = lineOfVisibleTrees(verticalLineOfTrees);
        for (size_t y = 0; y < visibleTrees.size(); y++) {
            visibleTrees[y][x] = visibleTrees[y][x] || verticallyVisibleTrees[y];
            result += visibleTrees[y][x];
        }
    }

    std::cout << "Result: " << result << std::endl;

    file.close();

    return 0;
}

std::vector<bool> lineOfVisibleTrees(std::vector<int> lineOfTrees) {
    std::vector<bool> result(lineOfTrees.size(), false);
    int highestTreeSoFar = -1;

    for (int index = 0; index < lineOfTrees.size(); index++) {
        if (lineOfTrees[index] > highestTreeSoFar) {
            highestTreeSoFar = lineOfTrees[index];
            result[index] = true;
        }
    }

    highestTreeSoFar = -1;
    for (int index = lineOfTrees.size() - 1; index >= 0; index--) {
        if (lineOfTrees[index] > highestTreeSoFar) {
            highestTreeSoFar = lineOfTrees[index];
            result[index] = true;
        }
    }
    
    return result;
}