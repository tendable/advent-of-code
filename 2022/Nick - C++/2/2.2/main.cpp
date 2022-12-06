#include <iostream>
#include <fstream>
#include <sstream>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;

    long score = 0;
    while(std::getline(file, line, '\n')) {
        runRound(line, &score);
    }

    std::cout << "Score: " << score << std::endl;
    
    file.close();

    return 0;
}

void runRound(std::string line, long *totalScore) {
    std::stringstream stringStream(line);
    std::string opponentMoveCharacter, resultCharacter;
    std::getline(stringStream, opponentMoveCharacter, ' ');
    std::getline(stringStream, resultCharacter, ' ');
    unsigned int opponentMove = stringToMove(opponentMoveCharacter);
    unsigned int result = stringToResult(resultCharacter);
    unsigned int score = scoreFor(opponentMove, result);
    if (score != -1) {
        *totalScore += score;
    }
}

unsigned int scoreFor(unsigned int opponentMove, unsigned int expectedResult) {

    if (expectedResult == DRAW) {
        return opponentMove + DRAW;
    }

    switch(opponentMove) {
        case ROCK:
            return expectedResult == WIN ? PAPER + WIN : SCISSORS + LOSS;
        case PAPER:
            return expectedResult == WIN ? SCISSORS + WIN : ROCK + LOSS;
        case SCISSORS:
            return expectedResult == WIN ? ROCK + WIN : PAPER + LOSS;
    }

    return -1;
}

unsigned int stringToMove(std::string character) {
    if (character.compare(std::string("A")) == 0) return ROCK;
    else if (character.compare(std::string("B")) == 0) return PAPER;
    else if (character.compare(std::string("C")) == 0) return SCISSORS;
    return -1;
}

unsigned int stringToResult(std::string character) {
    if (character.compare(std::string("X")) == 0) return LOSS;
    else if (character.compare(std::string("Y")) == 0) return DRAW;
    else if (character.compare(std::string("Z")) == 0) return WIN;
    return -1;
}
