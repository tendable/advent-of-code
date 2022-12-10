#pragma once
#include <string>
#include <vector>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

int stringToDirection(std::string direction);
void performMove(int direction, int amount, std::set<std::pair<int, int> >* visitedLocation, std::pair<int, int>* head, std::pair<int, int>* tail);
bool areTouching(std::pair<int, int>* head, std::pair<int, int>* tail);