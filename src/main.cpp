#include <iostream>
#include <fstream>
#include "definitions.h"
#include "instructionSet.h"
#include "CPU.h"
#include "registerPair.h"
 
int main() {

    initializeInstructionSet();
    CPU test;
    auto a = unprefixedInstructions;
    auto b = cbprefixedInstructions;
    test.loadRom("../resources/roms/dmg_boot.bin");


}


