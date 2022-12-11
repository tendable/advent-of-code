#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <cmath>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;

    std::vector<Monkey *> monkeys;
    VeryLongNumber worryDivisionFactor = 1;
    while(!file.eof()) {
        Monkey* monkey = readMonkey(&file);
        monkeys.insert(monkeys.end(), monkey);
        worryDivisionFactor *= monkey->test->divisibleBy;
    }

    for(int i = 0; i < 10000; i++) {
        runRound(&monkeys, worryDivisionFactor);
    }

    std::vector<VeryLongNumber> topMonkeyInspections;
    for(Monkey* monkey : monkeys) {
        topMonkeyInspections.insert(topMonkeyInspections.end(), monkey->numberOfInspections);
    }
    std::sort(topMonkeyInspections.begin(), topMonkeyInspections.end());

    std::string result = multiplyVeryLargeNumbers(topMonkeyInspections[topMonkeyInspections.size()-1], topMonkeyInspections[topMonkeyInspections.size()-2]);
    std::cout << "Monkey business: " << result << std::endl;
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

std::vector<VeryLongNumber>* getMonkeyItems(std::string line) {
    std::vector<VeryLongNumber>* monkeyItems = new std::vector<VeryLongNumber>();
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
    monkey->test->divisibleBy = (VeryLongNumber) getLastInteger(line);
    std::getline(*file, line, '\n');
    monkey->test->monkeyIndexIfTrue = getLastInteger(line);
    std::getline(*file, line, '\n');
    monkey->test->monkeyIndexIfFalse = getLastInteger(line);

    // Empty separator line
    std::getline(*file, line, '\n');

    return monkey;
}

VeryLongNumber Monkey::inspect(VeryLongNumber worryDivisionFactor) {
    VeryLongNumber item = (*startingItems)[0];
    startingItems->erase(startingItems->begin());

    VeryLongNumber operand2 = operation->operand2 == -1 ? item : operation->operand2;
    switch(operation->operationType) {
        case Operation::multiplication:
            item *= operand2;
            break;

        case Operation::addition:
            item += operand2;
            break;
    }

    numberOfInspections++;

    return item % worryDivisionFactor;
}

void Monkey::runTurn(std::vector<Monkey *> *monkeys, VeryLongNumber worryDivisionFactor) {
    while(!startingItems->empty()) {
        VeryLongNumber itemToThrow = inspect(worryDivisionFactor);
        int monkeyIndexToThrowTo = std::fmod(itemToThrow, test->divisibleBy) == 0 ? test->monkeyIndexIfTrue : test->monkeyIndexIfFalse;
        auto otherMonkey = (*monkeys)[monkeyIndexToThrowTo];
        otherMonkey->startingItems->insert(otherMonkey->startingItems->end(), itemToThrow);
    }
}

void runRound(std::vector<Monkey *> *monkeys, VeryLongNumber worryDivisionFactor) {
    for(size_t monkeyIndex = 0; monkeyIndex < monkeys->size(); monkeyIndex++) {
        (*monkeys)[monkeyIndex]->runTurn(monkeys, worryDivisionFactor);
    }
}

std::vector<unsigned int> convertVeryLongNumber(VeryLongNumber number) {
    std::vector<unsigned int> result;
    while(number > 0) {
        result.insert(result.end(), (number % 10));
        number /= 10;
    }
    return result;
}

std::string multiplyVeryLargeNumbers(VeryLongNumber a, VeryLongNumber b) {
    auto number1 = convertVeryLongNumber(a);
    auto number2 = convertVeryLongNumber(b);
    std::vector<unsigned int> result(number1.size() + number1.size() + 1);
    for(size_t i = 0; i < number1.size(); i++) {
        for(size_t j = 0; j < number2.size(); j++) {
            result[i+j] += number1[i] * number2[j];
            result[i+j+1] = result[i+j+1] + result[i+j] / 10;
            result[i+j] %= 10;
        }
    }
    std::string resultString;
    for(size_t i = 0; i < result.size(); i++) {
        resultString.insert(resultString.begin(), result[i] + '0');
    }
    resultString.erase(0, resultString.find_first_not_of('0')); // remove leading zeros
    return resultString;
}