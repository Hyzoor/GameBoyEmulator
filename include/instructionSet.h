#pragma once
#include <string>
#include <vector>
#include "definitions.h"

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

inline std::vector<Instruction> unprefixedInstructions;
inline std::vector<Instruction> cbprefixedInstructions;

void initializeInstructionSet();
void getInstructionsFromJson(const Json&, std::vector<Instruction> &);

