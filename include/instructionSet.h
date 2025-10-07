#pragma once
#include <string>
#include <vector>
#include "definitions.h"

struct Flags {
    std::string Z, N, H, C; 
};

class CPU;

struct Instruction {
    u8 opcode;
    std::string mnemonic;
    int bytes;
    int cycles;
    bool immediate;
    Flags flags;
    void (CPU::*execute)();
};

inline std::vector<Instruction> unprefixedInstructions;
inline std::vector<Instruction> cbprefixedInstructions;

void initializeInstructionSet();
void getInstructionDataFromJson(const Json&, std::vector<Instruction> &);

