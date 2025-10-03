#include <vector>
#include <fstream>
#include "instructionSet.h"
#include "definitions.h"

#include <iostream>

void initializeInstructionSet(){

    std::ifstream file("../resources/instructionSet.json");
    json data = json::parse(file);
    
    std::cout << data["unprefixed"]["0x00"]["mnemonic"];

};