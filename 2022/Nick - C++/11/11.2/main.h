#pragma once
#include <string>
#include <vector>

typedef long long unsigned int VeryLongNumber;

class Operation {
    public:
        enum Type {
            multiplication, addition
        } operationType;
        VeryLongNumber operand2;
};

class Test {
    public:
        VeryLongNumber divisibleBy;
        int monkeyIndexIfTrue;
        int monkeyIndexIfFalse;
};

class Monkey {
    public:
        int index;
        std::vector<VeryLongNumber>* startingItems;
        Operation* operation;
        Test* test;

        int numberOfInspections;


        void runTurn(std::vector<Monkey *> *monkeys, VeryLongNumber worryDivisionFactor);
    
    private:
        ~Monkey() {
            free(operation);
            free(test);
        }
        VeryLongNumber inspect(VeryLongNumber worryDivisionFactor);
};

Monkey* readMonkey(std::ifstream* file);
void runRound(std::vector<Monkey *> *monkeys, VeryLongNumber worryDivisionFactor);
std::string multiplyVeryLargeNumbers(VeryLongNumber a, VeryLongNumber b);