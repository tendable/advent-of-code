#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;

    std::vector<Monkey *> monkeys;
    
    while(!file.eof()) {
        Monkey* monkey = readMonkey(&file);
        monkeys.insert(monkeys.end(), monkey);
    }

    for(int i = 0; i < 20; i++) {
        runRound(&monkeys);
    }

    std::vector<int> topMonkeyInspections;
    for(Monkey* monkey : monkeys) {
        topMonkeyInspections.insert(topMonkeyInspections.end(), monkey->numberOfInspections);
    }
    std::sort(topMonkeyInspections.begin(), topMonkeyInspections.end());

    std::cout << "Monkey business: " << topMonkeyInspections[topMonkeyInspections.size() - 1] * topMonkeyInspections[topMonkeyInspections.size() - 2] << std::endl;

    file.close();

    return 0;
}

int getMonkeyIndex(std::string line) {
    std::stringstream ss(line);
    std::string index;
    std::getline(ss, index, ' ');
    std::getline(ss, index, ':');
    return std::stoi(index);
}

std::vector<int>* getMonkeyItems(std::string line) {
    std::vector<int>* monkeyItems = new std::vector<int>();
    std::stringstream ss(line);
    std::string current;
    while(current.compare("items:") != 0) { // keep reading words until encounterinig "items:"
        std::getline(ss, current, ' ');
    }
    while(std::getline(ss, current, ',')) { // read each number
        current.erase(std::remove(current.begin(), current.end(), ' '), current.end()); // remove any spaces
        monkeyItems->insert(monkeyItems->end(), std::stoi(current));
    }
    return monkeyItems;
}

Operation* getMonkeyOperation(std::string line) {
    Operation* operation = (Operation *) std::malloc(sizeof(Operation));
    std::stringstream ss(line);
    std::string current;
    while(current.compare("old") != 0) { // keep reading words until encounterinig "old"
        std::getline(ss, current, ' ');
    }
    std::getline(ss, current, ' '); // current now contains the operation type
    if (current.compare("+") == 0) {
        operation->operationType = Operation::addition;
    } else if(current.compare("*") == 0) {
        operation->operationType = Operation::multiplication;
    }
    std::getline(ss, current, ' '); // current now contains operand 2 ("old" or number)
    if(current.compare("old") == 0) {
        operation->operand2 = -1;
    } else {
        operation->operand2 = std::stoi(current);
    }
    return operation;
}

int getLastInteger(std::string line) {
    std::stringstream ss(line);
    std::string current;
    while(std::getline(ss, current, ' ')); // Read until the very end
    return std::stoi(current);
}

Monkey* readMonkey(std::ifstream* file) {
    std::string line;

    Monkey* monkey = (Monkey *) std::malloc(sizeof(Monkey));
    monkey->numberOfInspections = 0;

    // Monkey Index
    std::getline(*file, line, '\n');
    monkey->index = getMonkeyIndex(line);

    // Starting Items
    std::getline(*file, line, '\n');
    monkey->startingItems = getMonkeyItems(line);
    // Operation
    std::getline(*file, line, '\n');
    monkey->operation = getMonkeyOperation(line);

    // Test
    monkey->test = (Test* ) std::malloc(sizeof(Test));
    std::getline(*file, line, '\n');
    monkey->test->divisibleBy = getLastInteger(line);
    std::getline(*file, line, '\n');
    monkey->test->monkeyIndexIfTrue = getLastInteger(line);
    std::getline(*file, line, '\n');
    monkey->test->monkeyIndexIfFalse = getLastInteger(line);

    // Empty separator line
    std::getline(*file, line, '\n');

    return monkey;
}

int Monkey::inspect() {
    int item = (*startingItems)[0];
    startingItems->erase(startingItems->begin());

    int operand2 = operation->operand2 == -1 ? item : operation->operand2;
    switch(operation->operationType) {
        case Operation::Type::multiplication:
            item *= operand2;
            break;

        case Operation::Type::addition:
            item += operand2;
            break;
    }

    numberOfInspections++;

    return item / 3;
}

void Monkey::runTurn(std::vector<Monkey *> *monkeys) {
    while(!startingItems->empty()) {
        int itemToThrow = inspect();
        int monkeyIndexToThrowTo = itemToThrow % test->divisibleBy == 0 ? test->monkeyIndexIfTrue : test->monkeyIndexIfFalse;
        auto otherMonkey = (*monkeys)[monkeyIndexToThrowTo];
        otherMonkey->startingItems->insert(otherMonkey->startingItems->end(), itemToThrow);
    }
}

void runRound(std::vector<Monkey *> *monkeys) {
    for(size_t monkeyIndex = 0; monkeyIndex < monkeys->size(); monkeyIndex++) {
        (*monkeys)[monkeyIndex]->runTurn(monkeys);
    }
}