#pragma once
#include <string>
#include <vector>

#define DISK_SIZE 70000000
#define REQUIRED_SPACE 30000000

class Entry {
    public:
        std::string name;
        virtual unsigned long size() { return -1; };
};

class Directory: public Entry {
    public:
        std::vector<Entry*> entries;
        Directory* parentDirectory;

        Directory(std::string name, Directory* parentDirectory) {
            this->name = name;
            this->parentDirectory = parentDirectory;
        }

        unsigned long size() {
            unsigned long total = 0;
            for(int i = 0; i < entries.size(); i++) {
                total += entries[i]->size();
            }
            return total;
        }

};

class File: public Entry {
    public:
        unsigned long size() {
            return m_Size;
        }
        File(std::string name, unsigned long size) {
            this->name = name;
            this->m_Size = size;
        }
    private:
        unsigned long m_Size;
};

std::vector<std::string> splitCommand(std::string command);
void runCommand(std::vector<std::string> command, Directory** currentDirectory);
void processOutput(std::vector<std::string> output, Directory** currentDirectory);
void cd(std::string directoryName, Directory** currentDirectory);
void ls();
Directory* findMinimumDirectory(Directory* currentDirectory, unsigned long neededSpace);