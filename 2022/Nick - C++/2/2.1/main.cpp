#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
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
    std::string opponentMoveCharacter, myMoveCharacter;
    std::getline(stringStream, opponentMoveCharacter, ' ');
    std::getline(stringStream, myMoveCharacter, ' ');
    unsigned int opponentMove = stringToMove(opponentMoveCharacter);
    unsigned int myMove = stringToMove(myMoveCharacter);
    unsigned int score = scoreFor(opponentMove, myMove);
    if (score != -1) {
        *totalScore += score;
    }
}

unsigned int scoreFor(unsigned int opponentMove, unsigned int myMove) {
    if (opponentMove == myMove) {
        return myMove + DRAW;
    }

    if (myMove % 2 == opponentMove % 2) {
        if (myMove == std::min(myMove, opponentMove)) { return myMove + WIN; }
        else return myMove + LOSS;
    } else {
        if (myMove == std::max(myMove, opponentMove)) { return myMove + WIN; }
        else return myMove + LOSS;
    }

    switch(opponentMove) {
        case ROCK:
            if (myMove == PAPER) return myMove + WIN;
            if (myMove == SCISSORS) return myMove + LOSS;
            break;
        case PAPER:
            if (myMove == ROCK) return myMove + LOSS;
            if (myMove == SCISSORS) return myMove + WIN;
            break;
        case SCISSORS:
            if (myMove == ROCK) return myMove + WIN;
            if (myMove == PAPER) return myMove + LOSS;
            break;
    }
    return -1;
}

unsigned int stringToMove(std::string character) {
    if (character.compare(std::string("A")) == 0 || character.compare(std::string("X")) == 0) return ROCK;
    else if (character.compare(std::string("B")) == 0 || character.compare(std::string("Y")) == 0) return PAPER;
    else if (character.compare(std::string("C")) == 0 || character.compare(std::string("Z")) == 0) return SCISSORS;
    return -1;
}
