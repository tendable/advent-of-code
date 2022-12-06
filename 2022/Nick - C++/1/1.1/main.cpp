#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::ifstream file("input");
    std::string line;

    int maxCalories = 0;
    int currentCalories = 0;

    while(std::getline(file, line, '\n')) {
        try {
            currentCalories += stoi(line);
        } catch(...) {
            maxCalories = std::max(currentCalories, maxCalories);
            currentCalories = 0;
        }
    }
    maxCalories = std::max(currentCalories, maxCalories);
    
    std::cout << "Maximum Calories: " << maxCalories << std::endl;

    return 0;
}