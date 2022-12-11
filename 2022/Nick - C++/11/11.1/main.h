#pragma once
#include <string>
#include <vector>

class Operation {
    public:
        enum Type {
            multiplication, addition
        } operationType;
        int operand2;
};

class Test {
    public:
        int divisibleBy;
        int monkeyIndexIfTrue;
        int monkeyIndexIfFalse;
};

class Monkey {
    public:
        int index;
        std::vector<int>* startingItems;
        Operation* operation;
        Test* test;

        int numberOfInspections;

        void runTurn(std::vector<Monkey *> *monkeys);
    
    private:
        ~Monkey() {
            free(operation);
            free(test);
        }
        int inspect();
};

Monkey* readMonkey(std::ifstream* file);
void runRound(std::vector<Monkey *> *monkeys);