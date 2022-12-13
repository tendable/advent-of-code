#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <set>
#include "main.h"

void displayKnots(std::vector<std::pair<int, int> >* knots) {
    std::vector<std::vector<char> > display(30, std::vector<char>(30, '.'));
    for(int i = knots->size()-1; i >=0 ; i--) {
        std::pair<int, int> knot = (*knots)[i];
        char charToDisplay = i == 0 ? 'H' : '0' + i;
        display[30 - (knot.second + 15)][knot.first + 15] = charToDisplay;
    }

    for(int y = 0; y < display.size(); y++) {
        for(int x = 0; x < display[0].size(); x++) {
            std::cout << display[y][x];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {

    std::ifstream file("input");
    std::string line;

    std::vector<std::pair<int, int> > knots(10, std::pair<int, int>(0, 0));

    std::set< std::pair<int, int> > visitedLocations;
    visitedLocations.insert(std::pair<int, int>(0, 0));

    while(std::getline(file, line, '\n')) {
        std::stringstream ss(line);

        std::string direction, amount;
        std::getline(ss, direction, ' ');
        std::getline(ss, amount, ' ');
        
        int amountValue = std::stoi(amount);

        performMove(stringToDirection(direction), amountValue, &visitedLocations, &knots);
        // displayKnots(&knots);
    }

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


int followHead(std::pair<int, int>* head, std::pair<int, int>* tail, bool isActualHead) {
    if (!areTouching(head, tail)) {
        bool shouldMoveUp = head->second - tail->second > isActualHead;
        bool shouldMoveDown = tail->second - head->second > isActualHead;
        bool shouldMoveRight = head->first - tail->first > isActualHead;
        bool shouldMoveLeft = tail->first - head->first > isActualHead;

        bool shouldMoveDiagonallyRight = (shouldMoveUp || shouldMoveDown) && (head->first - tail->first > 0) && isActualHead;
        bool shouldMoveDiagonallyLeft = (shouldMoveUp || shouldMoveDown) && (head->first - tail->first < 0) && isActualHead;
        bool shouldMoveDiagonallyUp = (shouldMoveLeft || shouldMoveRight) && (head->second - tail->second > 0) && isActualHead;
        bool shouldMoveDiagonallyDown = (shouldMoveLeft || shouldMoveRight) && (head->second - tail->second < 0) && isActualHead;

        if (shouldMoveUp || shouldMoveDiagonallyUp) {
            tail->second += 1;
        }

        if (shouldMoveRight || shouldMoveDiagonallyRight) {
            tail->first += 1;
        }

        if (shouldMoveDown || shouldMoveDiagonallyDown) {
            tail->second -= 1;
        }

        if (shouldMoveLeft || shouldMoveDiagonallyLeft) {
            tail->first -= 1;
        }
    }
}

void performMove(int direction, int amount, std::set<std::pair<int, int> >* visitedLocation, std::vector<std::pair<int, int> >* knots) {
    for (int i = 0; i < amount; i++) {
        switch(direction) {
            case UP:
                (*knots)[0].second += 1;
                break;
            case RIGHT:
                (*knots)[0].first += 1;
                break;
            case DOWN:
                (*knots)[0].second -= 1;
                break;
            case LEFT:
                (*knots)[0].first -= 1;
                break;
        }
        for (int knotIndex = 1; knotIndex < knots->size(); knotIndex++) {
            std::pair<int, int>* head = &((*knots)[knotIndex - 1]);
            std::pair<int, int>* tail = &((*knots)[knotIndex]);

            followHead(head, tail, knotIndex == 1);
            if(knotIndex == knots->size() - 1) {
                visitedLocation->insert(*tail);
            }
        }
        // displayKnots(knots);
    }
}

bool areTouching(std::pair<int, int>* head, std::pair<int, int>* tail) {
    int horizontalDifference = head->first - tail->first;
    int verticalDifference = head->second - tail->second;
    return 
        (std::abs(horizontalDifference) <= 1) &&
        (std::abs(verticalDifference) <= 1);
}