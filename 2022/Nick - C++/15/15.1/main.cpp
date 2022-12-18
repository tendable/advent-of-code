#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include "main.h"
#include <regex>

int main() {

    std::ifstream file("input");
    std::string line;

    std::vector<std::pair<Position, Position>*> sensorsAndBeacons;
    while(std::getline(file, line, '\n')) {
        auto pair = locationsFrom(line);
        sensorsAndBeacons.insert(sensorsAndBeacons.begin(), pair);
    }

    auto locationsWithNoBeacons = positionsWithoutBeaconFor(sensorsAndBeacons);
    std::cout << locationsWithNoBeacons->size() + 1<< std::endl;
    file.close();

    return 0;
}

std::pair<Position, Position>* locationsFrom(std::string line) {
    std::pair<Position, Position>* result = new std::pair<Position, Position>();
    long x, y;
    std::stringstream ss(line);
    std::string current;

    for (size_t index = 0; index < 2; index++) {
        std::getline(ss, current, '='); // Skip everything until the first =
        std::getline(ss, current, ','); // Read everything until the first comma, leaving us with the x value
        x = std::stol(current);
        std::getline(ss, current, '='); // Skip everything until the second =
        std::getline(ss, current, ':'); // Read everything until the first : leaving us with the x value
        y = std::stol(current);

        Position pos(x, y);
        if (index == 0) { result->first = pos; }
        else { result->second = pos; }
    }

    return result;
}

std::set<Position>* positionsWithoutBeaconFor(Position sensor, Position closestBeacon) {
    std::set<Position>* result = new std::set<Position>();

    long distance = sensor.distanceTo(closestBeacon);
    long minX = sensor.x - distance;
    long maxX = sensor.x + distance;
    long minY = SEARCH_ROW;
    long maxY = SEARCH_ROW; 

    for(long y = minY; y <= maxY; y++) {
        for(long x = minX; x <= maxX; x++) {
            Position pos(x, y);
            if (pos.distanceTo(sensor) > distance) continue; // we only want the radius around the sensor
            result->insert(pos);
        }
    }
    result->erase(sensor);

    return result;
}

std::set<Position>* positionsWithoutBeaconFor(std::vector<std::pair<Position, Position>*> locations) {
    std::set<Position>* result = new std::set<Position>();

    for(auto location : locations) {
        auto positions = positionsWithoutBeaconFor(location->first, location->second);
        result->insert(positions->begin(), positions->end());
    }

    return result;
}

long Position::distanceTo(Position otherPosition) const {
    return std::abs(x - otherPosition.x) + std::abs(y - otherPosition.y);
}