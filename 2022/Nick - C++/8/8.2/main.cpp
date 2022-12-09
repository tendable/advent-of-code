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
    
    int result = -1, maxY = 0, maxX = 0;
    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            int score = scoreForTree(y, x, grid);
            if (score > result) {
                result = score; maxY = y; maxX = x;
            }
        }
    }

    
    std::cout << "Result: " << result << ", Y: " << maxY << ", X: " << maxX << std::endl;

    file.close();

    return 0;
}

int scoreForTree(int y, int x, std::vector< std::vector<int> > grid) {
    int result = 1;

    ViewingDistanceFunction functions[4] = {topViewingDistance, rightViewingDistance, bottomViewingDistance, leftViewingDistance};

    for (int i = 0; i < 4; i++) {
        result *= functions[i](y, x, grid);
    }

    return result;
}

int topViewingDistance(int y, int x, std::vector< std::vector<int> > grid) {
    if (y == 0) { return 0; } // if we're on the top edge, viewing distance is 0

    int treeHeight = grid[y][x];

    int result = 0;
    for(int j = y-1; j >= 0; j--) {
        result += grid[j][x] < treeHeight;
        if (grid[j][x] >= treeHeight) {
            result++;
            break;
        }
    }

    return result;
}

int rightViewingDistance(int y, int x, std::vector< std::vector<int> > grid) {
    if (x == grid[y].size() - 1) { return 0; } // if we're on the right edge, viewing distance is 0

    int treeHeight = grid[y][x];

    int result = 0;
    for(int i = x+1; i < grid[y].size(); i++) {
        result += grid[y][i] < treeHeight;
        if (grid[y][i] >= treeHeight) {
            result++;
            break;
        }
    }

    return result;
}

int bottomViewingDistance(int y, int x, std::vector< std::vector<int> > grid) {
    if (y == grid.size()-1) { return 0; } // if we're on the bottom edge, viewing distance is 0

    int treeHeight = grid[y][x];

    int result = 0;
    for(int j = y+1; j < grid.size(); j++) {
        result += grid[j][x] < treeHeight;
        if (grid[j][x] >= treeHeight) {
            result++;
            break;
        }
    }

    return result;
}

int leftViewingDistance(int y, int x, std::vector< std::vector<int> > grid) {
    if (x == 0) { return 0; } // if we're on the left edge, viewing distance is 0

    int treeHeight = grid[y][x];

    int result = 0;
    for(int i = x-1; i >= 0; i--) {
        result += grid[y][i] < treeHeight;
        if (grid[y][i] >= treeHeight) {
            result++;
            break;
        }
    }

    return result;
}