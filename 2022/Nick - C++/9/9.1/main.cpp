#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <set>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;

    std::pair<int, int> head(0, 0), tail(0, 0);

    std::set< std::pair<int, int> > visitedLocations;
    visitedLocations.insert(std::pair<int, int>(0, 0));

    while(std::getline(file, line, '\n')) {
        std::stringstream ss(line);

        std::string direction, amount;
        std::getline(ss, direction, ' ');
        std::getline(ss, amount, ' ');
        
        int amountValue = std::stoi(amount);

        performMove(stringToDirection(direction), amountValue, &visitedLocations, &head, &tail);
    }

    // display(visitedLocations);
    std::cout << "Result: " << visitedLocations.size() << std::endl;

    file.close();

    return 0;
}

int stringToDirection(std::string direction) {
    if(direction.compare("U") == 0) return UP;
    if(direction.compare("R") == 0) return RIGHT;
    if(direction.compare("D") == 0) return DOWN;
    if(direction.compare("L") == 0) return LEFT; 
    return -1;
}

void performMove(int direction, int amount, std::set<std::pair<int, int> >* visitedLocation, std::pair<int, int>* head, std::pair<int, int>* tail) {
    for (int i = 0; i < amount; i++) {
        switch(direction) {
            case UP:
                head->second += 1;
                break;
            case RIGHT:
                head->first += 1;
                break;
            case DOWN:
                head->second -= 1;
                break;
            case LEFT:
                head->first -= 1;
                break;
        }
        if (!areTouching(head, tail)) {
            bool shouldMoveHorizontally = head->first == tail->first;
            bool shouldMoveVertically = head->second == tail->second;
            bool shouldMoveDiagonally = !shouldMoveHorizontally && !shouldMoveVertically;
            bool headOnTheRightOfTail = (head->first - tail->first) > 0;
            bool headAboveTail = (head->second - tail->second) > 0;
            switch(direction) {
                case UP:
                    tail->first += (headOnTheRightOfTail ? 1 : -1) * shouldMoveDiagonally;
                    tail->second += 1;
                    break;
                case RIGHT:
                    tail->first += 1;
                    tail->second += (headAboveTail ? 1 : -1) * shouldMoveDiagonally;
                    break;
                case DOWN:
                    tail->first += (headOnTheRightOfTail ? 1 : -1) * shouldMoveDiagonally;
                    tail->second -= 1;
                    break;
                case LEFT:
                    tail->first -= 1;
                    tail->second += (headAboveTail ? 1 : -1) * shouldMoveDiagonally;
                    break;
            }
            visitedLocation->insert(*tail);
        }
    }
}

bool areTouching(std::pair<int, int>* head, std::pair<int, int>* tail) {
    int horizontalDifference = std::abs(head->first - tail->first);
    int verticalDifference = std::abs(head->second - tail->second);
    return 
        (horizontalDifference == 1 || horizontalDifference == 0) &&
        (verticalDifference == 1 || verticalDifference == 0);
}