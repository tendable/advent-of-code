#pragma once
#include <string>
#include <vector>

#define WIDTH 40
#define HEIGHT 6
#define SPRITE_WIDTH 3
#define LIT '#'
#define DARK '.'

class CPU;

class Instruction {
    public:
        virtual bool run(CPU* cpu) { return true; };
    protected:
        int m_clockCycles;
};

class CPU {
    public:
        int internalClock;
        int registerX;

        CPU(std::vector<Instruction *>* commandQueue) { 
            this->internalClock = 1;
            this->registerX = 1;
            this->commandQueue = commandQueue;
            this->currentCommand = commandQueue->back();
        }
        
        void tick();
        long signalStrength();

    private:
        std::vector<Instruction *>* commandQueue;
        Instruction* currentCommand;
};

class Add: public Instruction {
    public:
        bool run(CPU* cpu);
        Add(int value) { m_clockCycles = 2; valueToAdd = value; }

    private:
        int valueToAdd;

};

class Noop: public Instruction {
    public:
        bool run(CPU* cpu);
        Noop() { m_clockCycles = 1; }
};

class CRT {
    public:
        char pixels[HEIGHT][WIDTH];
        void draw(CPU* cpu);
        void display();
        CRT() {
            memset(pixels, 0, WIDTH*HEIGHT*sizeof(char));
        }
};

Instruction* stringToInstruction(std::string command, std::string argument);