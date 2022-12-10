#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;
    std::vector<Instruction*> instructions;

    while(std::getline(file, line, '\n')) {
        std::stringstream ss(line);
        std::string command, argument;

        std::getline(ss, command, ' ');
        std::getline(ss, argument, ' ');

        Instruction* instruction = stringToInstruction(command, argument);
        instructions.insert(instructions.begin(), instruction);
    }

    CPU* cpu = new CPU(&instructions);
    int arr[6] = {20, 60, 100, 140, 180, 220};
    std::vector<int> interestPoints(arr, arr+6);
    long sum = 0;
    while(!instructions.empty()) {
        cpu->tick();
        if (cpu->internalClock == interestPoints.front()) {
            sum += cpu->signalStrength();
            std::cout << cpu->internalClock << ": " << cpu->signalStrength() << std::endl;
            interestPoints.erase(interestPoints.begin());
        }
    }

    std::cout << "Sum of strengths: " << sum << std::endl;

    file.close();

    return 0;
}

Instruction* stringToInstruction(std::string command, std::string argument) {
    if(command.compare("noop") == 0) {
        return new Noop();
    } else if (command.compare("add")) {
        int value = std::stoi(argument);
        return new Add(value);
    }

    return nullptr;
}

void CPU::tick() {
    internalClock++;
    if(currentCommand->run(this)) {
        this->commandQueue->pop_back();
        this->currentCommand = this->commandQueue->back();
    }
}

long CPU::signalStrength() {
    return this->internalClock * this->registerX;
}

bool Add::run(CPU* cpu) {
    m_clockCycles--;
    if (m_clockCycles == 0) {
        cpu->registerX += valueToAdd;
        return true;
    }
    return false;
}

bool Noop::run(CPU* cpu) {
    m_clockCycles = 0;
    return true;
}