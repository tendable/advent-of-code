#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string group[3], line;
    size_t groupNumber = 0;

    long sumOfPriorities = 0;
    while(std::getline(file, line, '\n')) {
        if(groupNumber == 3) {
            groupNumber = 0;
            sumOfPriorities += commonPriority(group);
        }
        group[groupNumber++] = line;
    }
    sumOfPriorities += commonPriority(group);

    std::cout << "Sum of priorities: " << sumOfPriorities << std::endl;
    
    file.close();

    return 0;
}

unsigned int priority(char character) {
    if (character <= 90) {
        // std::cout << character << ": " << character - 38 << std::endl;
        return character - 38;
    } else {
        // std::cout << character << ": " << character - 96 << std::endl;
        return character - 96;
    }
}

unsigned int commonPriority(std::string* group) {

    std::vector<char> elf1(group[0].begin(), group[0].end());
    std::sort(elf1.begin(), elf1.end());
    std::vector<char> elf2(group[1].begin(), group[1].end());
    std::sort(elf2.begin(), elf2.end());
    std::vector<char> elf3(group[2].begin(), group[2].end());
    std::sort(elf3.begin(), elf3.end());
    std::vector<char> intersection1;
    std::vector<char> intersection2;
 
    std::set_intersection(elf1.begin(), elf1.end(), elf2.begin(), elf2.end(), std::inserter(intersection1, intersection1.begin()));
    std::set_intersection(intersection1.begin(), intersection1.end(), elf3.begin(), elf3.end(), std::inserter(intersection2, intersection2.begin()));

    return priority(intersection2[0]);
}