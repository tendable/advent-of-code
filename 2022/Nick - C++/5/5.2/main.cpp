#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;
    std::vector<std::vector<char> > stacks;
    while(std::getline(file, line, '\n')) {
        if(line[1] == '1' || line.empty()) continue;
        if (line[0] == 'm') {
            std::stringstream ss(line);
            std::string command[6];
            for (size_t index = 0; index < 6; index++) {
                std::getline(ss, command[index], ' ');
            }
            move(std::stoi(command[1]), std::stoi(command[3]), std::stoi(command[5]), &stacks);
            continue;
        }
        getNumbersFromLine(line, &stacks);
    }
    printVector(&stacks);
    std::cout << "Result: ";
    for (size_t index = 0; index < stacks.size(); index++) {
        std::cout << stacks[index][stacks[index].size()-1];
    }
    std::cout << std::endl;

    file.close();

    return 0;
}

void move(int count, int fromStack, int toStack, std::vector<std::vector<char> >* stacks) {
    for (size_t index = 0; index < count; index++) {
        char lastElement = (*stacks)[fromStack-1][(*stacks)[fromStack-1].size() - 1];
        (*stacks)[fromStack-1].pop_back();
        (*stacks)[toStack-1].insert((*stacks)[toStack-1].end() - index, lastElement);
    }
}

void getNumbersFromLine(std::string line, std::vector<std::vector<char> >* stacks) {
    for(int i = 1; i < line.length(); i+=4) {
        int stackIndex = (i-1) / 4;
        if (stackIndex >= stacks->size()) {
            stacks->insert(stacks->end(), std::vector<char>());
        }
        if (line[i] != ' ') (*stacks)[stackIndex].insert((*stacks)[stackIndex].begin(), line[i]);
    }


}

void printVector(std::vector<std::vector<char> >* vector) {
    for(size_t i = 0; i < vector->size(); i++) {
        std::cout << i << ": ";
        for(size_t j = 0; j < (*vector)[i].size(); j++) {
            std::cout << (*vector)[i][j] << " ";
        }
        std::cout << std::endl;
    }
}