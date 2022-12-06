#include <iostream>
#include <fstream>
#include <string>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;

    long *topCalories = (long *) std::malloc(sizeof(long) * TOP_N);
    long currentCalories = 0;

    while(std::getline(file, line, '\n')) {
        try {
            currentCalories += stol(line);
        } catch(...) {
            insertCalories(currentCalories, topCalories, TOP_N);
            currentCalories = 0;
        }
    }
    insertCalories(currentCalories, topCalories, TOP_N);

    printResult(topCalories, TOP_N);

    free(topCalories);
    file.close();

    return 0;
}

void insertCalories(long calories, long* topCalories, size_t numberOfItems) {
    for (size_t index = 0; index < numberOfItems; index++) {
        if (calories > topCalories[index]) {
            shift(topCalories, index, numberOfItems);
            topCalories[index] = calories;
            break;
        }
    }
}

void shift(long* array, size_t fromIndex, size_t untilIndex) {
    for (size_t indexToPush = untilIndex - 1; indexToPush > fromIndex; indexToPush--) {
        array[indexToPush] = array[indexToPush - 1];
    }
}

void printResult(long* topCalories, size_t numberOfItems) {
    long sum = 0;

    for (size_t index = 0; index < numberOfItems; index++) {
        sum += topCalories[index];
        std::cout << "Top " << index << ": " << topCalories[index] << std::endl;
    }

    std::cout << "Total: " << sum << std::endl;
}