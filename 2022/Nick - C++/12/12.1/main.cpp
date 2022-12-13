#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <queue>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;

    HeightMap map;

    // Read each line and store each character in the map
    // If we encounter S we mark that position as the startingPosition and set the value in themap to 'a'
    // Similarly if we encounter E we mark that position as destination and set the value in the map to 'z'
    size_t y = 0;
    while(std::getline(file, line, '\n')) {
        map.heights.insert(map.heights.end(), std::vector<char>());
        for(size_t x = 0; x < line.size(); x++) {
            char characterToInsert = line[x];
            if (characterToInsert == 'S') {
                characterToInsert = 'a';
                map.startingPosition.x = x;
                map.startingPosition.y = y;
            } else if (characterToInsert == 'E') {
                characterToInsert = 'z';
                map.destination.x = x;
                map.destination.y = y;
            }

            map.heights[y].insert(map.heights[y].end(), characterToInsert);
        }
        y++;
    }

    // Result should contain the index for each step between (and including) the startingPosition and the destination
    std::vector<Position>* result = dijkstra(&map);

    // Making the tiles uppercase to make them more visible when printing
    for (Position pos : *(result)) {
        map.heights[pos.y][pos.x] -= 32;
    }

    // Printing the characters. If they're uppercase, print them in green, otherwise print them in red. This makes it easy to visualise the path
    for(int i = 0; i < map.heights.size(); i++) {
        for(int j = 0; j < map.heights[0].size(); j++) {
            char c = map.heights[i][j];
            if (c >= 'a') { //lowercase
                std::cout << "\033[0;31m" << c << "\033[0m";
            } else { // uppercase
                std::cout << "\033[1;32m" << c << "\033[0m";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Number of moves: " << result->size() - 1 << std::endl;

    file.close();

    return 0;
}

std::vector<PositionType>* neighboursInSet(HeightMap* map, PositionType index, std::set<PositionType> *Q) {
    std::vector<PositionType>* result = new std::vector<PositionType>();
    // Get a list of all accessible (+-=1 height) neighbours for the index
    auto neighbours = map->accessibleNeighbours(map->positionFor(index));

    // Go through each of those and convert the x/y position to an index, and check if they are still in the set Q
    // If they are, add it to the result array and return it
    for (auto neighbour : *neighbours) {
        size_t neighbourIndex = map->indexFor(neighbour);
        if (Q->find(neighbourIndex) != Q->end()) {
            result->insert(result->end(), neighbourIndex);
        }
    }
    return result;
}

std::vector<Position>* dijkstra(HeightMap* map) {
    size_t width = map->heights[0].size();
    size_t height = map->heights.size();

    // A index's distance is the distance between it and the starting point
    std::vector<PositionType> dist(width * height, INT_MAX); // All distances are infinite to begin with
    std::vector<PositionType> prev(width * height, -1); // Previous indices initialised as Undefined
    std::set<PositionType> Q;

    // Add all the indices to the set Q
    for(size_t index = 0; index < map->heights.size() * map->heights[0].size(); index++) {
        Q.insert(Q.end(), index);
    }

    // The distance between the starting point and itself is 0
    dist[map->indexFor(map->startingPosition)] = 0;

    while(!Q.empty()) {
        // Find the index with the smallest distance from the starting point
        PositionType indexMinDistance = *(Q.begin());
        PositionType minDistance = dist[indexMinDistance];
        for (PositionType index : Q) {
            if (dist[index] < minDistance) {
                minDistance = dist[index];
                indexMinDistance = index;
            }
        }

        // Remove it from the queue
        Q.erase(indexMinDistance);

        // Find the neighbours of the tile that are valid moves (height +-= 1) and that are still in the set Q
        std::vector<PositionType>* neighbours = neighboursInSet(map, indexMinDistance, &Q);
        for (size_t i = 0; i < neighbours->size(); i++) {
            // Calculate the distance for this neighbour index if we came from the current index
            PositionType alt = dist[indexMinDistance] + 1;
            PositionType neighbourIndex = (*neighbours)[i];

            Position c = map->positionFor(indexMinDistance);
            Position n = map->positionFor(neighbourIndex);
            // If it's shorter to reach this neighbour through the current index, replace its distance and set its prev index to our index
            if (alt < dist[neighbourIndex]) {
                dist[neighbourIndex] = alt;
                prev[neighbourIndex] = indexMinDistance;
            }
        }
    }

    // // Start at the destination index and keep going through the prev indices to find the path
    std::vector<Position>* S = new std::vector<Position>();
    PositionType u = map->indexFor(map->destination);
    // If the previous index is defined or we've reached the starting position, keep going back and insert the indices into the array S
    if(prev[u] != -1 || u == map->indexFor(map->startingPosition)) {
        while (u != -1) {
            S->insert(S->begin(), map->positionFor(u));
            u = prev[u];
        }
    }

    // S should now contain all the steps to get from startingPosition to destination
    return S;
}