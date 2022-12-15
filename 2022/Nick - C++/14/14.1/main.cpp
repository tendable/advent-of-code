#include <iostream>
#include <fstream>
#include <algorithm>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;
    

    Matrix* matrix = new Matrix();

    while(std::getline(file, line, '\n')) {
        std::vector<Point>* points = lineToPositions(line);
        matrix->drawLines(points);
    }

    matrix->startDroppingSand();
    matrix->print();

    file.close();

    return 0;
}

std::vector<Point>* lineToPositions(std::string line) {
    std::vector<Point>* points = new std::vector<Point>();

    std::string delimiter = " -> ";
    size_t pos = 0;
    std::string token;
    
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        points->insert(points->end(), Point(token));
        line.erase(0, pos + delimiter.length());
    }
    points->insert(points->end(), Point(line));

    return points;
}

// MARK: - Matrix
void Matrix::drawLine(Point a, Point b) {
    if (a.x == b.x) { // Vertical line
        if (a.y < b.y) { // Line going up
            for(int y = a.y; y <= b.y; y++) {
                this->m_Matrix[y][a.x] = '#';
            }
        } else { // Line going down
            for(int y = b.y; y <= a.y; y++) {
                this->m_Matrix[y][a.x] = '#';
            }
        }
    } else if (a.y == b.y) { // Horizontal line
        size_t lineLength = std::abs(a.x - b.x);
        if (a.x < b.x) { // Line going right
            for(int x = a.x; x <= b.x; x++) {
                this->m_Matrix[a.y][x] = '#';
            }
        } else { // Line going left
            for(int x = b.x; x <= a.x; x++) {
                this->m_Matrix[a.y][x] = '#';
            }
        }
    }
}

void Matrix::print() {
    for(int y = 0; y < m_Matrix.size(); y++) {
        for(int x = 0; x < m_Matrix[0].size(); x++) {
            std::cout << m_Matrix[y][x];
        }
        std::cout << std::endl;
    }
}

void Matrix::drawLines(std::vector<Point>* points) {
    for (int index = 1; index < points->size(); index++) {
        this->drawLine((*points)[index-1], (*points)[index]);
    }
}

void Matrix::startDroppingSand() {
    int amountOfSandDropped = 0;
    while(dropSand()) {
        amountOfSandDropped++;
    }
    std::cout<< "Sand: " << amountOfSandDropped << std::endl;
}

Point Matrix::nextPointForSand(Point currentLocation) {
    // Try to move down
    {
        Point nextLocation = Point(currentLocation.x, currentLocation.y + 1);
        if (nextLocation.y >= m_Matrix.size()) { return OutOfMapPoint; } // Sand fell outside of the map
        if (m_Matrix[nextLocation.y][nextLocation.x] == '.') { return nextLocation; } // Sand should move down
    }

    // Try to move down-left
    {
        Point nextLocation = Point(currentLocation.x - 1, currentLocation.y + 1);
        if (nextLocation.y >= m_Matrix.size() || nextLocation.x < 0) { return OutOfMapPoint; } // Sand fell outside of the map
        if (m_Matrix[nextLocation.y][nextLocation.x] == '.') { return nextLocation; } // Sand should move down-left
    }

    // Try to move down-right
    {
        Point nextLocation = Point(currentLocation.x + 1, currentLocation.y + 1);
        if (nextLocation.y >= m_Matrix.size() || nextLocation.x >= m_Matrix[0].size()) { return OutOfMapPoint; } // Sand fell outside of the map
        if (m_Matrix[nextLocation.y][nextLocation.x] == '.') { return nextLocation; } // Sand should move down-right
    }

    return currentLocation; // Sand has nowhere to go;
}

bool Matrix::dropSand() {
    Point outOfMap = OutOfMapPoint;
    Point lastPoint = SandPoint;
    Point nextPoint = SandPoint;

    do {
        lastPoint = nextPoint;
        nextPoint = nextPointForSand(nextPoint);
    }while(lastPoint != nextPoint && nextPoint != outOfMap);

    if (lastPoint == nextPoint) {
        m_Matrix[lastPoint.y][lastPoint.x] = 'o';
        return true;
    }

    return false; // The sand fell outside of the map
}