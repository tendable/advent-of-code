#pragma once
#include <string>
#include <vector>

void getNumbersFromLine(std::string line, std::vector<std::vector<char> >* stacks);
void printVector(std::vector<std::vector<char> >* vector);
void move(int count, int fromStack, int toStack, std::vector<std::vector<char> >* stacks);