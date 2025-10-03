#pragma once
#include <string>
#include <vector>

struct Operand {
    std::string name;
    int bytes;
    bool immediate;
};

struct Flags {
    std::string Z, N, H, C; 
};

struct Instruction {
    std::string mnemonic;
    int bytes;
    int cycles;
    std::vector<Operand> operands;
    bool immediate;
    Flags flags;
};

static const std::vector<Instruction> instructionSet;

void initializeInstructionSet();

