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

    auto locationsWithNoBeacons = positionWithoutBeaconFor(sensorsAndBeacons);
    std::cout << locationsWithNoBeacons.x << " " << locationsWithNoBeacons.y << std::endl;
    std::cout << locationsWithNoBeacons.x * MAXCOORD + locationsWithNoBeacons.y << std::endl;
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

std::pair<long, long>* rangesWithNoBeacons(Position sensor, Position closestBeacon, long row) {
    long distance = sensor.distanceTo(closestBeacon);
    long deltaY = std::abs(sensor.y - row);
    if (deltaY > distance) return nullptr;

    long remaining = distance - deltaY;
    return new std::pair<long, long>(sensor.x - remaining, sensor.x + remaining);
}

std::vector<std::pair<long, long>*>* combineRanges(std::vector<std::pair<long, long>*>* ranges) {
    auto result = new std::vector<std::pair<long, long>*>();
    if (ranges->empty()) return result;

    long currentStart = (*ranges)[0]->first;
    long currentEnd = (*ranges)[0]->second;

    for(auto range : *ranges) {
        if(range->first <= currentEnd) {
            currentEnd = std::max(currentEnd, range->second);
            continue;
        } else {
            auto combinedRange = new std::pair<long, long>;
            combinedRange->first = currentStart;
            combinedRange->second = currentEnd;
            result->push_back(combinedRange);
        }
        currentStart = range->first;
        currentEnd = range->second;
    }
    auto combinedRange = new std::pair<long, long>;
    combinedRange->first = currentStart;
    combinedRange->second = currentEnd;
    result->push_back(combinedRange);
    
    return result;
}

std::vector<std::pair<long, long>*>* rangesWithNoBeaconsInRow(std::vector<std::pair<Position, Position>*> locations, long row) {
    auto ranges = new std::vector<std::pair<long, long>*>();
    for (auto location : locations) {
        auto range = rangesWithNoBeacons(location->first, location->second, row);
        if (range != nullptr)
            ranges->push_back(range);
    }
    std::sort(ranges->begin(), ranges->end(), []( const std::pair<long, long>* a, const std::pair<long, long>* b )
    {
        return a->first < b->first;
    });
    return combineRanges(ranges);
}

Position positionWithoutBeaconFor(std::vector<std::pair<Position, Position>*> locations) {
    long previousEnd = -1;
    for (long y = 0; y <= MAXCOORD; y++) {
        auto ranges = rangesWithNoBeaconsInRow(locations, y);
        for(auto itr = ranges->begin(); itr < ranges->end(); itr++) {
            long start = (*itr)->first;
            long end = (*itr)->second;
            // ignore all ranges that are fully < 0 or > MAXCOORD
            if ((start < 0 && end < 0) || (MAXCOORD < start && MAXCOORD < end)) continue;
            // if there is a gap in the ranges
            if (previousEnd + 1 < start && 0 <= previousEnd + 1) {
                return Position(previousEnd + 1, y);
            }
            previousEnd = end;
        }
    }

    return Position(-1, -1);
}

long Position::distanceTo(Position otherPosition) const {
    return std::abs(x - otherPosition.x) + std::abs(y - otherPosition.y);
}