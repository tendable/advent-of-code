#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include "main.h"

int main() {

    std::ifstream file("input");
    std::string line;
    Directory* currentDirectory = nullptr;
    unsigned long maxDirectorySize = 0;

    while (std::getline(file, line, '\n')) {
        std::vector<std::string> commandArguments = splitCommand(line);
        if (commandArguments[0].compare("$") == 0) {
            runCommand(commandArguments, &currentDirectory);
        } else {
            processOutput(commandArguments, &currentDirectory);
        }
    }

    while(currentDirectory->parentDirectory) {
        currentDirectory = currentDirectory->parentDirectory;
    }

    std::cout << "Size: " << findTotalSize(currentDirectory) << std::endl;

    file.close();

    return 0;
}

unsigned long findTotalSize(Directory* currentDirectory) {
    unsigned long runningTotal = 0;
    for(int i = 0; i < currentDirectory->entries.size(); i++) {
        Entry* entry = currentDirectory->entries[i];
        if (dynamic_cast<Directory*>(entry) == nullptr) { continue; } // not a directory
        unsigned long directorySize = entry->size();
        if (directorySize <= 100000) {
            runningTotal += directorySize;
        }
        runningTotal += findTotalSize((Directory*)entry);
    }
    return runningTotal;
}

std::vector<std::string> splitCommand(std::string command) {
    std::vector<std::string> result;
    std::stringstream ss(command);
    std::string current;

    while(std::getline(ss, current, ' ')) {
        result.insert(result.end(), current);
    }

    return result;
}

void runCommand(std::vector<std::string> command, Directory** currentDirectory) {

    if (command[1].compare("cd") == 0) {
        cd(command[2], currentDirectory);
    } else if(command[1].compare("ls") == 0) {
        ls();
    }
}

void processOutput(std::vector<std::string> output, Directory** currentDirectory) {
    if (output[0].compare("dir") == 0) {
        Directory* newDirectory = new Directory(output[1], *currentDirectory);
        (*currentDirectory)->entries.insert(((*currentDirectory)->entries).end(), newDirectory);
    } else {
        unsigned long fileSize = std::stoul(output[0]);
        File* newFile = new File(output[1], fileSize);
        (*currentDirectory)->entries.insert(((*currentDirectory)->entries).end(), newFile);
    }

}

void cd(std::string directoryName, Directory** currentDirectory) {
    if (*currentDirectory == nullptr) {
        *currentDirectory = new Directory(directoryName, NULL);
        return;
    }

    if (directoryName.compare("..") == 0) {
        *currentDirectory = (*currentDirectory)->parentDirectory;
    }

    for (int i = 0; i < (*currentDirectory)->entries.size(); i++) {
        if ((*currentDirectory)->entries[i]->name.compare(directoryName) == 0) {

            *currentDirectory = (Directory *) ((*currentDirectory)->entries[i]);
            return;
        }
    }
}

void ls() {

}