#include <vector>
#include <fstream>
#include <format>
#include "instructionSet.h"
#include "definitions.h"

#include <iostream>

void from_json(const Json& json, Operand& operand) {
    operand.name = json.value("name", "");        
    operand.bytes = json.value("bytes", 0);       
    operand.immediate = json.value("immediate", false);
};

void from_json(const Json& json, Flags& flags) {
    json.at("Z").get_to(flags.Z);
    json.at("N").get_to(flags.N);
    json.at("H").get_to(flags.H);
    json.at("C").get_to(flags.C);
};

void initializeInstructionSet(){

    std::ifstream file("../resources/instructionSet.json");
    Json data = Json::parse(file);
    Json unprefixedJson = data["unprefixed"];
    Json cbprefixedJson = data["cbprefixed"];

    getInstructionsFromJson(unprefixedJson, unprefixedInstructions);
    getInstructionsFromJson(cbprefixedJson, cbprefixedInstructions);

};

void getInstructionsFromJson(const Json &json, std::vector<Instruction> &instructions){

    for(auto& [key, element]: json.items()){

        Instruction instruction = {
            element.value("mnemonic", "Invalid opcode"),
            element.value("bytes", 0),
            element["cycles"].at(0),
            element["operands"],
            element["immediate"],
            element["flags"]
        };

        instructions.push_back(instruction);
    };

};

