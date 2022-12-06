#pragma once
#include <string>
#define ROCK 1
#define PAPER 2
#define SCISSORS 3

#define LOSS 0
#define DRAW 3
#define WIN 6

unsigned int stringToMove(std::string character);
unsigned int stringToResult(std::string character);
unsigned int scoreFor(unsigned int opponentMove, unsigned int expectedResult);
void runRound(std::string line, long *score);