#include <vector>
#include <fstream>
#include <format>
#include "instructionSet.h"
#include "definitions.h"
#include "CPU.h"

#include <iostream>

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

    getInstructionDataFromJson(unprefixedJson, unprefixedInstructions);
    getInstructionDataFromJson(cbprefixedJson, cbprefixedInstructions);

};

void getInstructionDataFromJson(const Json &json, std::vector<Instruction> &instructions){
    for(auto& [key, element]: json.items()){

        u8 opcode = static_cast<u8>(std::stoul(key, nullptr, 16));

        Instruction instruction = {
            opcode,
            element.value("mnemonic", "Invalid opcode"),
            element.value("bytes", 0),
            element["cycles"].at(0),
            element["immediate"],
            element["flags"],
            nullptr
        };

        instructions.push_back(instruction);
    };

};

