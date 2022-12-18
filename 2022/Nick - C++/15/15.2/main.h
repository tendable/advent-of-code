#pragma once
#include <string>
#include <vector>

#define MAXCOORD 4000000L

struct Position {
    long x;
    long y;
    Position() { this->x = 0; this->y = 0; }
    Position(long x, long y) { this->x = x; this->y = y; }

    long distanceTo(Position otherPosition) const;
};

std::pair<Position, Position>* locationsFrom(std::string line);
Position positionWithoutBeaconFor(std::vector<std::pair<Position, Position>*> locations);