#pragma once
#include <string>
#include <vector>
#include <sstream>

#define X_TRANSLATION -400
#define SandPoint Point(500 + X_TRANSLATION, 0)
#define OutOfMapPoint Point(-1, -1)

struct Point {
    int x,y;
    Point(int x, int y) { this->x = x; this->y = y; }
    Point(std::string pointString) {
        std::stringstream ss(pointString);
        std::string x, y;
        std::getline(ss, x, ',');
        std::getline(ss, y, ',');
        this->x = std::stoi(x) + X_TRANSLATION; // Translating x by -300 points as there's a lot of wasted space
        this->y = std::stoi(y);
    }
    inline bool operator==(const Point& otherPoint) const {
        return x == otherPoint.x && y == otherPoint.y;
    }
    inline bool operator!=(Point& otherPoint) {
        return x != otherPoint.x || y != otherPoint.y;
    }
};

class Matrix {
    private:
        std::vector<std::vector<char> > m_Matrix;

    private:
        void drawLine(Point a, Point b);
        bool dropSand();
        Point nextPointForSand(Point currentLocation);

    public:
        Matrix() { this->m_Matrix = std::vector<std::vector<char> >(200, std::vector<char>(200, '.')); }
        void drawLines(std::vector<Point>* points);
        void print();
        void startDroppingSand();
};

std::vector<Point>* lineToPositions(std::string line);