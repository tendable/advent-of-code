#pragma once
#include <string>
#include <vector>

#define SEARCH_ROW 2000000-1

struct Position {
    long x;
    long y;
    Position() { this->x = 0; this->y = 0; }
    Position(long x, long y) { this->x = x; this->y = y; }
    bool operator<(const Position &other) const { return std::pair<long, long>(x, y) < std::pair<long, long>(other.x, other.y); }

    long distanceTo(Position otherPosition) const;
};

std::pair<Position, Position>* locationsFrom(std::string line);
std::set<Position>* positionsWithoutBeaconFor(Position sensor, Position closestBeacon);
std::set<Position>* positionsWithoutBeaconFor(std::vector<std::pair<Position, Position>*> locations);