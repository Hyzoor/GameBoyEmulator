#include <iostream>
#include <fstream>
#include "definitions.h"
#include "instructionSet.h"
#include "CPU.h"
#include "registerPair.h"

int main() {

    initializeInstructionSet();

    CPU prueba;
    prueba.loadRom("../resources/roms/dmg_boot.bin");
    
}


