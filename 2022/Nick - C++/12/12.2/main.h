#pragma once
#include <string>
#include <vector>

#define PositionType int

struct Position {
    public:
        PositionType x;
        PositionType y;
        bool equals(Position otherPosition) {
            return x == otherPosition.x && y == otherPosition.y;
        }
        Position(PositionType x, PositionType y) { this->x = x; this->y = y; }
        Position() { this->x = -1; this->y = -1; }
};

class HeightMap {
    public:
        std::vector<std::vector<char> > heights;
        Position startingPosition;
        Position destination;
    
    private:
        bool isValidMove(Position from, Position to) {
            return (PositionType)heights[to.y][to.x] - (PositionType)heights[from.y][from.x] <= 1;
        }

    public:
        size_t indexFor(Position position) {
            size_t width = heights[0].size();
            return position.y * width + position.x;
        }
        Position positionFor(size_t index) {
            size_t width = heights[0].size();
            PositionType y = index / width;
            PositionType x = index % width;
            return Position(x, y);
        }
        std::vector<Position>* accessibleNeighbours(Position otherPosition) {
            std::vector<Position>* positions = new std::vector<Position>();
            if (otherPosition.x > 0) {
                Position leftNeighbour = Position(otherPosition.x - 1, otherPosition.y);
                if (isValidMove(otherPosition, leftNeighbour)) {
                    positions->insert(positions->end(), leftNeighbour);
                }
            }
            if (otherPosition.x < heights[0].size()-1) {
                Position rightNeighbour = Position(otherPosition.x + 1, otherPosition.y);
                if (isValidMove(otherPosition, rightNeighbour)) {
                    positions->insert(positions->end(), rightNeighbour);
                }
            }
            if (otherPosition.y > 0) {
                Position topNeighbour = Position(otherPosition.x, otherPosition.y - 1);
                if (isValidMove(otherPosition, topNeighbour)) {
                    positions->insert(positions->end(), topNeighbour);
                }
            }
            if (otherPosition.y < heights.size() - 1) {
                Position bottomNeighbour = Position(otherPosition.x, otherPosition.y + 1);
                if (isValidMove(otherPosition, bottomNeighbour)) {
                    positions->insert(positions->end(), bottomNeighbour);
                }
            }
            return positions;
        }
};

std::vector<Position>* dijkstra(HeightMap* map);