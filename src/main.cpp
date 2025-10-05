#include <iostream>
#include <fstream>
#include "definitions.h"
#include "instructionSet.h"
#include "CPU.h"
#include "registerPair.h"

int main() {

    initializeInstructionSet();

    CPU prueba;
    u16 u = 0xF0F1;
    prueba.AF.setValue(u);

    std::cout <<(int)prueba.A << " " << (int)prueba.F << std::endl;
}


