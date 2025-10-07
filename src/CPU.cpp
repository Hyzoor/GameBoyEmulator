#include <fstream>
#include "CPU.h"
#include "definitions.h"
#include "instructionSet.h"

CPU::CPU(): AF(A,F), BC(B,C), DE(D,E), HL(H,L){
    A=B=C=D=E=F=H=L=0;
    SP = 0x00;
    PC = 0x00;

    initializePointerTables();
    mapPointerTables();
};

// Creo que esto no es responsabilidad de la cpu si no de la memoria. Class Memory
void CPU::loadRom(const std::string& romPath){
    
    std::ifstream inputFile(romPath, std::ios::binary);

    if (!inputFile.is_open()){throw std::runtime_error("Couldnt open ROM file");}

    char byteRead;
    for (int i = 0x00; inputFile.get(byteRead); i++){
        memoryArray[i] = static_cast<uint8_t>(byteRead);
    }
}

void CPU::mainLoop(){
    fetchInstruction();
    exec(instruction);

    // Add PC + instruction length
    PC += instruction.bytes;
}

void CPU::fetchInstruction(){
    u8 opcode = memoryArray[PC++];

    if(opcode == 0xCB) {
        opcode = memoryArray[PC++];
        instruction = cbprefixedInstructions[opcode];}
    else {
        instruction = unprefixedInstructions[opcode];}
}

void CPU::exec(const Instruction &instruction){

    
}

void CPU::load(u8& destination, u8 data){
    destination = data;
}

void CPU::load(u16& destination, u16 data){
    destination = data;
}

// Each opcode function
void CPU::opcode_00() {}
void CPU::opcode_01() {
    u8 low = memoryArray[PC++];
    u8 high = memoryArray[PC++];
    BC.setValue((high << 8) | low);
}
void CPU::opcode_02() {load(memoryArray[BC.getValue()], A);}
void CPU::opcode_03() {}
void CPU::opcode_04() {}
void CPU::opcode_05() {}
void CPU::opcode_06() {load(B, memoryArray[PC++]);}
void CPU::opcode_07() {}
void CPU::opcode_08() {}
void CPU::opcode_09() {}
void CPU::opcode_0A() {load(A, memoryArray[BC.getValue()]);}
void CPU::opcode_0B() {}
void CPU::opcode_0C() {}
void CPU::opcode_0D() {}
void CPU::opcode_0E() {load(C, memoryArray[PC++]);}
void CPU::opcode_0F() {}
void CPU::opcode_10() {}
void CPU::opcode_11() {    
    u8 low = memoryArray[PC++];
    u8 high = memoryArray[PC++];
    DE.setValue((high << 8) | low);}
void CPU::opcode_12() {load(memoryArray[DE.getValue()], A);}
void CPU::opcode_13() {}
void CPU::opcode_14() {}
void CPU::opcode_15() {}
void CPU::opcode_16() {load(D, memoryArray[PC++]);}
void CPU::opcode_17() {}
void CPU::opcode_18() {}
void CPU::opcode_19() {}
void CPU::opcode_1A() {load(A, memoryArray[DE.getValue()]);}
void CPU::opcode_1B() {}
void CPU::opcode_1C() {}
void CPU::opcode_1D() {}
void CPU::opcode_1E() {load(E, memoryArray[PC++]);}
void CPU::opcode_1F() {}
void CPU::opcode_20() {}
void CPU::opcode_21() {    
    u8 low = memoryArray[PC++];
    u8 high = memoryArray[PC++];
    HL.setValue((high << 8) | low);}
void CPU::opcode_22() {load(memoryArray[HL.getValue()], A); HL.increment();}
void CPU::opcode_23() {}
void CPU::opcode_24() {}
void CPU::opcode_25() {}
void CPU::opcode_26() {load(H, memoryArray[PC++]);}
void CPU::opcode_27() {}
void CPU::opcode_28() {}
void CPU::opcode_29() {}
void CPU::opcode_2A() {load(A, memoryArray[HL.getValue()]); HL.increment();}
void CPU::opcode_2B() {}
void CPU::opcode_2C() {}
void CPU::opcode_2D() {}
void CPU::opcode_2E() {load(L, memoryArray[PC++]);}
void CPU::opcode_2F() {}
void CPU::opcode_30() {}
void CPU::opcode_31() {
    u8 low = memoryArray[PC++];
    u8 high = memoryArray[PC++];
    load(SP, (high << 8) | low);
}
void CPU::opcode_32() {load(memoryArray[HL.getValue()], A); HL.decrement();}
void CPU::opcode_33() {}
void CPU::opcode_34() {}
void CPU::opcode_35() {}
void CPU::opcode_36() {load(memoryArray[HL.getValue()], memoryArray[PC++]);}
void CPU::opcode_37() {}
void CPU::opcode_38() {}
void CPU::opcode_39() {}
void CPU::opcode_3A() {}
void CPU::opcode_3B() {}
void CPU::opcode_3C() {}
void CPU::opcode_3D() {}
void CPU::opcode_3E() {load(A, memoryArray[PC++]);}
void CPU::opcode_3F() {}
void CPU::opcode_40() {load(B, B);}
void CPU::opcode_41() {load(B, C);}
void CPU::opcode_42() {load(B, D);}
void CPU::opcode_43() {load(B, E);}
void CPU::opcode_44() {load(B, H);}
void CPU::opcode_45() {load(B, L);}
void CPU::opcode_46() {load(B, memoryArray[HL.getValue()]);}
void CPU::opcode_47() {load(B, A);}
void CPU::opcode_48() {load(C, B);}
void CPU::opcode_49() {load(C, C);}
void CPU::opcode_4A() {load(C, D);}
void CPU::opcode_4B() {load(C, E);}
void CPU::opcode_4C() {load(C, H);}
void CPU::opcode_4D() {load(C, L);}
void CPU::opcode_4E() {load(C, memoryArray[HL.getValue()]);}
void CPU::opcode_4F() {load(C, A);}
void CPU::opcode_50() {load(D, B);}
void CPU::opcode_51() {load(D, C);}
void CPU::opcode_52() {load(D, D);}
void CPU::opcode_53() {load(D, E);}
void CPU::opcode_54() {load(D, H);}
void CPU::opcode_55() {load(D, L);}
void CPU::opcode_56() {load(D, memoryArray[HL.getValue()]);}
void CPU::opcode_57() {load(D, A);}
void CPU::opcode_58() {load(E, B);}
void CPU::opcode_59() {load(E, C);}
void CPU::opcode_5A() {load(E, D);}
void CPU::opcode_5B() {load(E, E);}
void CPU::opcode_5C() {load(E, H);}
void CPU::opcode_5D() {load(E, L);}
void CPU::opcode_5E() {load(E, memoryArray[HL.getValue()]);}
void CPU::opcode_5F() {load(E, A);}
void CPU::opcode_60() {load(H, B);}
void CPU::opcode_61() {load(H, C);}
void CPU::opcode_62() {load(H, D);}
void CPU::opcode_63() {load(H, E);}
void CPU::opcode_64() {load(H, H);}
void CPU::opcode_65() {load(H, L);}
void CPU::opcode_66() {load(H, memoryArray[HL.getValue()]);}
void CPU::opcode_67() {load(H, A);}
void CPU::opcode_68() {load(L, B);}
void CPU::opcode_69() {load(L, C);}
void CPU::opcode_6A() {load(L, D);}
void CPU::opcode_6B() {load(L, E);}
void CPU::opcode_6C() {load(L, H);}
void CPU::opcode_6D() {load(L, L);}
void CPU::opcode_6E() {load(L,memoryArray[HL.getValue()]);}
void CPU::opcode_6F() {load(L, A);}
void CPU::opcode_70() {load(memoryArray[HL.getValue()], B);}
void CPU::opcode_71() {load(memoryArray[HL.getValue()], C);}
void CPU::opcode_72() {load(memoryArray[HL.getValue()], D);}
void CPU::opcode_73() {load(memoryArray[HL.getValue()], E);}
void CPU::opcode_74() {load(memoryArray[HL.getValue()], H);}
void CPU::opcode_75() {load(memoryArray[HL.getValue()], L);}
void CPU::opcode_76() {}
void CPU::opcode_77() {load(memoryArray[HL.getValue()], A);}
void CPU::opcode_78() {load(A, B);}
void CPU::opcode_79() {load(A, C);}
void CPU::opcode_7A() {load(A, D);}
void CPU::opcode_7B() {load(A, E);}
void CPU::opcode_7C() {load(A, H);}
void CPU::opcode_7D() {load(A, L);}
void CPU::opcode_7E() {load(A, memoryArray[HL.getValue()]);}
void CPU::opcode_7F() {load(A, A);}
void CPU::opcode_80() {}
void CPU::opcode_81() {}
void CPU::opcode_82() {}
void CPU::opcode_83() {}
void CPU::opcode_84() {}
void CPU::opcode_85() {}
void CPU::opcode_86() {}
void CPU::opcode_87() {}
void CPU::opcode_88() {}
void CPU::opcode_89() {}
void CPU::opcode_8A() {}
void CPU::opcode_8B() {}
void CPU::opcode_8C() {}
void CPU::opcode_8D() {}
void CPU::opcode_8E() {}
void CPU::opcode_8F() {}
void CPU::opcode_90() {}
void CPU::opcode_91() {}
void CPU::opcode_92() {}
void CPU::opcode_93() {}
void CPU::opcode_94() {}
void CPU::opcode_95() {}
void CPU::opcode_96() {}
void CPU::opcode_97() {}
void CPU::opcode_98() {}
void CPU::opcode_99() {}
void CPU::opcode_9A() {}
void CPU::opcode_9B() {}
void CPU::opcode_9C() {}
void CPU::opcode_9D() {}
void CPU::opcode_9E() {}
void CPU::opcode_9F() {}
void CPU::opcode_A0() {}
void CPU::opcode_A1() {}
void CPU::opcode_A2() {}
void CPU::opcode_A3() {}
void CPU::opcode_A4() {}
void CPU::opcode_A5() {}
void CPU::opcode_A6() {}
void CPU::opcode_A7() {}
void CPU::opcode_A8() {}
void CPU::opcode_A9() {}
void CPU::opcode_AA() {}
void CPU::opcode_AB() {}
void CPU::opcode_AC() {}
void CPU::opcode_AD() {}
void CPU::opcode_AE() {}
void CPU::opcode_AF() {}
void CPU::opcode_B0() {}
void CPU::opcode_B1() {}
void CPU::opcode_B2() {}
void CPU::opcode_B3() {}
void CPU::opcode_B4() {}
void CPU::opcode_B5() {}
void CPU::opcode_B6() {}
void CPU::opcode_B7() {}
void CPU::opcode_B8() {}
void CPU::opcode_B9() {}
void CPU::opcode_BA() {}
void CPU::opcode_BB() {}
void CPU::opcode_BC() {}
void CPU::opcode_BD() {}
void CPU::opcode_BE() {}
void CPU::opcode_BF() {}
void CPU::opcode_C0() {}
void CPU::opcode_C1() {}
void CPU::opcode_C2() {}
void CPU::opcode_C3() {}
void CPU::opcode_C4() {}
void CPU::opcode_C5() {}
void CPU::opcode_C6() {}
void CPU::opcode_C7() {}
void CPU::opcode_C8() {}
void CPU::opcode_C9() {}
void CPU::opcode_CA() {}
void CPU::opcode_CB() {}
void CPU::opcode_CC() {}
void CPU::opcode_CD() {}
void CPU::opcode_CE() {}
void CPU::opcode_CF() {}
void CPU::opcode_D0() {}
void CPU::opcode_D1() {}
void CPU::opcode_D2() {}
void CPU::opcode_D3() {}
void CPU::opcode_D4() {}
void CPU::opcode_D5() {}
void CPU::opcode_D6() {}
void CPU::opcode_D7() {}
void CPU::opcode_D8() {}
void CPU::opcode_D9() {}
void CPU::opcode_DA() {}
void CPU::opcode_DB() {}
void CPU::opcode_DC() {}
void CPU::opcode_DD() {}
void CPU::opcode_DE() {}
void CPU::opcode_DF() {}
void CPU::opcode_E0() {u8 n = memoryArray[PC++]; load(memoryArray[0xFF00 + n], A);}
void CPU::opcode_E1() {}
void CPU::opcode_E2() {load(memoryArray[0xFF00 + C], A);}
void CPU::opcode_E3() {}
void CPU::opcode_E4() {}
void CPU::opcode_E5() {}
void CPU::opcode_E6() {}
void CPU::opcode_E7() {}
void CPU::opcode_E8() {}
void CPU::opcode_E9() {}
void CPU::opcode_EA() {
    u8 low = memoryArray[PC++];
    u8 high = memoryArray[PC++];
    load(memoryArray[(high << 8) | low], A);
}
void CPU::opcode_EB() {}
void CPU::opcode_EC() {}
void CPU::opcode_ED() {}
void CPU::opcode_EE() {}
void CPU::opcode_EF() {}
void CPU::opcode_F0() {u8 n = memoryArray[PC++]; load(A, memoryArray[0xFF00 + n]);}
void CPU::opcode_F1() {}
void CPU::opcode_F2() {load(A, memoryArray[0xFF00 + C]);}
void CPU::opcode_F3() {}
void CPU::opcode_F4() {}
void CPU::opcode_F5() {}
void CPU::opcode_F6() {}
void CPU::opcode_F7() {}
void CPU::opcode_F8() {}
void CPU::opcode_F9() {load(SP, HL.getValue());}
void CPU::opcode_FA() {
    u8 low = memoryArray[PC++];
    u8 high = memoryArray[PC++];
    u16 nn = (high << 8) | low;
    load(A, memoryArray[nn]);
}
void CPU::opcode_FB() {}
void CPU::opcode_FC() {}
void CPU::opcode_FD() {}
void CPU::opcode_FE() {}
void CPU::opcode_FF() {} 


void CPU::mapPointerTables(){
    for(int i = 0; i < unprefixedInstructions.size(); i++){
        unprefixedInstructions[i].execute = opcodeFunctions[i];
        // cbprefixedInstructions[i].execute = opcodeCBFunctions[i];
    }
}

void CPU::initializePointerTables(){
    opcodeFunctions[0x00] = &CPU::opcode_00; opcodeFunctions[0x01] = &CPU::opcode_01; opcodeFunctions[0x02] = &CPU::opcode_02; opcodeFunctions[0x03] = &CPU::opcode_03; opcodeFunctions[0x04] = &CPU::opcode_04; opcodeFunctions[0x05] = &CPU::opcode_05; opcodeFunctions[0x06] = &CPU::opcode_06; opcodeFunctions[0x07] = &CPU::opcode_07;
    opcodeFunctions[0x08] = &CPU::opcode_08; opcodeFunctions[0x09] = &CPU::opcode_09; opcodeFunctions[0x0A] = &CPU::opcode_0A; opcodeFunctions[0x0B] = &CPU::opcode_0B; opcodeFunctions[0x0C] = &CPU::opcode_0C; opcodeFunctions[0x0D] = &CPU::opcode_0D; opcodeFunctions[0x0E] = &CPU::opcode_0E; opcodeFunctions[0x0F] = &CPU::opcode_0F;
    opcodeFunctions[0x10] = &CPU::opcode_10; opcodeFunctions[0x11] = &CPU::opcode_11; opcodeFunctions[0x12] = &CPU::opcode_12; opcodeFunctions[0x13] = &CPU::opcode_13; opcodeFunctions[0x14] = &CPU::opcode_14; opcodeFunctions[0x15] = &CPU::opcode_15; opcodeFunctions[0x16] = &CPU::opcode_16; opcodeFunctions[0x17] = &CPU::opcode_17;
    opcodeFunctions[0x18] = &CPU::opcode_18; opcodeFunctions[0x19] = &CPU::opcode_19; opcodeFunctions[0x1A] = &CPU::opcode_1A; opcodeFunctions[0x1B] = &CPU::opcode_1B; opcodeFunctions[0x1C] = &CPU::opcode_1C; opcodeFunctions[0x1D] = &CPU::opcode_1D; opcodeFunctions[0x1E] = &CPU::opcode_1E; opcodeFunctions[0x1F] = &CPU::opcode_1F;
    opcodeFunctions[0x20] = &CPU::opcode_20; opcodeFunctions[0x21] = &CPU::opcode_21; opcodeFunctions[0x22] = &CPU::opcode_22; opcodeFunctions[0x23] = &CPU::opcode_23; opcodeFunctions[0x24] = &CPU::opcode_24; opcodeFunctions[0x25] = &CPU::opcode_25; opcodeFunctions[0x26] = &CPU::opcode_26; opcodeFunctions[0x27] = &CPU::opcode_27;
    opcodeFunctions[0x28] = &CPU::opcode_28; opcodeFunctions[0x29] = &CPU::opcode_29; opcodeFunctions[0x2A] = &CPU::opcode_2A; opcodeFunctions[0x2B] = &CPU::opcode_2B; opcodeFunctions[0x2C] = &CPU::opcode_2C; opcodeFunctions[0x2D] = &CPU::opcode_2D; opcodeFunctions[0x2E] = &CPU::opcode_2E; opcodeFunctions[0x2F] = &CPU::opcode_2F;
    opcodeFunctions[0x30] = &CPU::opcode_30; opcodeFunctions[0x31] = &CPU::opcode_31; opcodeFunctions[0x32] = &CPU::opcode_32; opcodeFunctions[0x33] = &CPU::opcode_33; opcodeFunctions[0x34] = &CPU::opcode_34; opcodeFunctions[0x35] = &CPU::opcode_35; opcodeFunctions[0x36] = &CPU::opcode_36; opcodeFunctions[0x37] = &CPU::opcode_37;
    opcodeFunctions[0x38] = &CPU::opcode_38; opcodeFunctions[0x39] = &CPU::opcode_39; opcodeFunctions[0x3A] = &CPU::opcode_3A; opcodeFunctions[0x3B] = &CPU::opcode_3B; opcodeFunctions[0x3C] = &CPU::opcode_3C; opcodeFunctions[0x3D] = &CPU::opcode_3D; opcodeFunctions[0x3E] = &CPU::opcode_3E; opcodeFunctions[0x3F] = &CPU::opcode_3F;
    opcodeFunctions[0x40] = &CPU::opcode_40; opcodeFunctions[0x41] = &CPU::opcode_41; opcodeFunctions[0x42] = &CPU::opcode_42; opcodeFunctions[0x43] = &CPU::opcode_43; opcodeFunctions[0x44] = &CPU::opcode_44; opcodeFunctions[0x45] = &CPU::opcode_45; opcodeFunctions[0x46] = &CPU::opcode_46; opcodeFunctions[0x47] = &CPU::opcode_47;
    opcodeFunctions[0x48] = &CPU::opcode_48; opcodeFunctions[0x49] = &CPU::opcode_49; opcodeFunctions[0x4A] = &CPU::opcode_4A; opcodeFunctions[0x4B] = &CPU::opcode_4B; opcodeFunctions[0x4C] = &CPU::opcode_4C; opcodeFunctions[0x4D] = &CPU::opcode_4D; opcodeFunctions[0x4E] = &CPU::opcode_4E; opcodeFunctions[0x4F] = &CPU::opcode_4F;
    opcodeFunctions[0x50] = &CPU::opcode_50; opcodeFunctions[0x51] = &CPU::opcode_51; opcodeFunctions[0x52] = &CPU::opcode_52; opcodeFunctions[0x53] = &CPU::opcode_53; opcodeFunctions[0x54] = &CPU::opcode_54; opcodeFunctions[0x55] = &CPU::opcode_55; opcodeFunctions[0x56] = &CPU::opcode_56; opcodeFunctions[0x57] = &CPU::opcode_57;
    opcodeFunctions[0x58] = &CPU::opcode_58; opcodeFunctions[0x59] = &CPU::opcode_59; opcodeFunctions[0x5A] = &CPU::opcode_5A; opcodeFunctions[0x5B] = &CPU::opcode_5B; opcodeFunctions[0x5C] = &CPU::opcode_5C; opcodeFunctions[0x5D] = &CPU::opcode_5D; opcodeFunctions[0x5E] = &CPU::opcode_5E; opcodeFunctions[0x5F] = &CPU::opcode_5F;
    opcodeFunctions[0x60] = &CPU::opcode_60; opcodeFunctions[0x61] = &CPU::opcode_61; opcodeFunctions[0x62] = &CPU::opcode_62; opcodeFunctions[0x63] = &CPU::opcode_63; opcodeFunctions[0x64] = &CPU::opcode_64; opcodeFunctions[0x65] = &CPU::opcode_65; opcodeFunctions[0x66] = &CPU::opcode_66; opcodeFunctions[0x67] = &CPU::opcode_67;
    opcodeFunctions[0x68] = &CPU::opcode_68; opcodeFunctions[0x69] = &CPU::opcode_69; opcodeFunctions[0x6A] = &CPU::opcode_6A; opcodeFunctions[0x6B] = &CPU::opcode_6B; opcodeFunctions[0x6C] = &CPU::opcode_6C; opcodeFunctions[0x6D] = &CPU::opcode_6D; opcodeFunctions[0x6E] = &CPU::opcode_6E; opcodeFunctions[0x6F] = &CPU::opcode_6F;
    opcodeFunctions[0x70] = &CPU::opcode_70; opcodeFunctions[0x71] = &CPU::opcode_71; opcodeFunctions[0x72] = &CPU::opcode_72; opcodeFunctions[0x73] = &CPU::opcode_73; opcodeFunctions[0x74] = &CPU::opcode_74; opcodeFunctions[0x75] = &CPU::opcode_75; opcodeFunctions[0x76] = &CPU::opcode_76; opcodeFunctions[0x77] = &CPU::opcode_77;
    opcodeFunctions[0x78] = &CPU::opcode_78; opcodeFunctions[0x79] = &CPU::opcode_79; opcodeFunctions[0x7A] = &CPU::opcode_7A; opcodeFunctions[0x7B] = &CPU::opcode_7B; opcodeFunctions[0x7C] = &CPU::opcode_7C; opcodeFunctions[0x7D] = &CPU::opcode_7D; opcodeFunctions[0x7E] = &CPU::opcode_7E; opcodeFunctions[0x7F] = &CPU::opcode_7F;
    opcodeFunctions[0x80] = &CPU::opcode_80; opcodeFunctions[0x81] = &CPU::opcode_81; opcodeFunctions[0x82] = &CPU::opcode_82; opcodeFunctions[0x83] = &CPU::opcode_83; opcodeFunctions[0x84] = &CPU::opcode_84; opcodeFunctions[0x85] = &CPU::opcode_85; opcodeFunctions[0x86] = &CPU::opcode_86; opcodeFunctions[0x87] = &CPU::opcode_87;
    opcodeFunctions[0x88] = &CPU::opcode_88; opcodeFunctions[0x89] = &CPU::opcode_89; opcodeFunctions[0x8A] = &CPU::opcode_8A; opcodeFunctions[0x8B] = &CPU::opcode_8B; opcodeFunctions[0x8C] = &CPU::opcode_8C; opcodeFunctions[0x8D] = &CPU::opcode_8D; opcodeFunctions[0x8E] = &CPU::opcode_8E; opcodeFunctions[0x8F] = &CPU::opcode_8F;
    opcodeFunctions[0x90] = &CPU::opcode_90; opcodeFunctions[0x91] = &CPU::opcode_91; opcodeFunctions[0x92] = &CPU::opcode_92; opcodeFunctions[0x93] = &CPU::opcode_93; opcodeFunctions[0x94] = &CPU::opcode_94; opcodeFunctions[0x95] = &CPU::opcode_95; opcodeFunctions[0x96] = &CPU::opcode_96; opcodeFunctions[0x97] = &CPU::opcode_97;
    opcodeFunctions[0x98] = &CPU::opcode_98; opcodeFunctions[0x99] = &CPU::opcode_99; opcodeFunctions[0x9A] = &CPU::opcode_9A; opcodeFunctions[0x9B] = &CPU::opcode_9B; opcodeFunctions[0x9C] = &CPU::opcode_9C; opcodeFunctions[0x9D] = &CPU::opcode_9D; opcodeFunctions[0x9E] = &CPU::opcode_9E; opcodeFunctions[0x9F] = &CPU::opcode_9F;
    opcodeFunctions[0xA0] = &CPU::opcode_A0; opcodeFunctions[0xA1] = &CPU::opcode_A1; opcodeFunctions[0xA2] = &CPU::opcode_A2; opcodeFunctions[0xA3] = &CPU::opcode_A3; opcodeFunctions[0xA4] = &CPU::opcode_A4; opcodeFunctions[0xA5] = &CPU::opcode_A5; opcodeFunctions[0xA6] = &CPU::opcode_A6; opcodeFunctions[0xA7] = &CPU::opcode_A7;
    opcodeFunctions[0xA8] = &CPU::opcode_A8; opcodeFunctions[0xA9] = &CPU::opcode_A9; opcodeFunctions[0xAA] = &CPU::opcode_AA; opcodeFunctions[0xAB] = &CPU::opcode_AB; opcodeFunctions[0xAC] = &CPU::opcode_AC; opcodeFunctions[0xAD] = &CPU::opcode_AD; opcodeFunctions[0xAE] = &CPU::opcode_AE; opcodeFunctions[0xAF] = &CPU::opcode_AF;
    opcodeFunctions[0xB0] = &CPU::opcode_B0; opcodeFunctions[0xB1] = &CPU::opcode_B1; opcodeFunctions[0xB2] = &CPU::opcode_B2; opcodeFunctions[0xB3] = &CPU::opcode_B3; opcodeFunctions[0xB4] = &CPU::opcode_B4; opcodeFunctions[0xB5] = &CPU::opcode_B5; opcodeFunctions[0xB6] = &CPU::opcode_B6; opcodeFunctions[0xB7] = &CPU::opcode_B7;
    opcodeFunctions[0xB8] = &CPU::opcode_B8; opcodeFunctions[0xB9] = &CPU::opcode_B9; opcodeFunctions[0xBA] = &CPU::opcode_BA; opcodeFunctions[0xBB] = &CPU::opcode_BB; opcodeFunctions[0xBC] = &CPU::opcode_BC; opcodeFunctions[0xBD] = &CPU::opcode_BD; opcodeFunctions[0xBE] = &CPU::opcode_BE; opcodeFunctions[0xBF] = &CPU::opcode_BF;
    opcodeFunctions[0xC0] = &CPU::opcode_C0; opcodeFunctions[0xC1] = &CPU::opcode_C1; opcodeFunctions[0xC2] = &CPU::opcode_C2; opcodeFunctions[0xC3] = &CPU::opcode_C3; opcodeFunctions[0xC4] = &CPU::opcode_C4; opcodeFunctions[0xC5] = &CPU::opcode_C5; opcodeFunctions[0xC6] = &CPU::opcode_C6; opcodeFunctions[0xC7] = &CPU::opcode_C7;
    opcodeFunctions[0xC8] = &CPU::opcode_C8; opcodeFunctions[0xC9] = &CPU::opcode_C9; opcodeFunctions[0xCA] = &CPU::opcode_CA; opcodeFunctions[0xCB] = &CPU::opcode_CB; opcodeFunctions[0xCC] = &CPU::opcode_CC; opcodeFunctions[0xCD] = &CPU::opcode_CD; opcodeFunctions[0xCE] = &CPU::opcode_CE; opcodeFunctions[0xCF] = &CPU::opcode_CF;
    opcodeFunctions[0xD0] = &CPU::opcode_D0; opcodeFunctions[0xD1] = &CPU::opcode_D1; opcodeFunctions[0xD2] = &CPU::opcode_D2; opcodeFunctions[0xD3] = &CPU::opcode_D3; opcodeFunctions[0xD4] = &CPU::opcode_D4; opcodeFunctions[0xD5] = &CPU::opcode_D5; opcodeFunctions[0xD6] = &CPU::opcode_D6; opcodeFunctions[0xD7] = &CPU::opcode_D7;
    opcodeFunctions[0xD8] = &CPU::opcode_D8; opcodeFunctions[0xD9] = &CPU::opcode_D9; opcodeFunctions[0xDA] = &CPU::opcode_DA; opcodeFunctions[0xDB] = &CPU::opcode_DB; opcodeFunctions[0xDC] = &CPU::opcode_DC; opcodeFunctions[0xDD] = &CPU::opcode_DD; opcodeFunctions[0xDE] = &CPU::opcode_DE; opcodeFunctions[0xDF] = &CPU::opcode_DF;
    opcodeFunctions[0xE0] = &CPU::opcode_E0; opcodeFunctions[0xE1] = &CPU::opcode_E1; opcodeFunctions[0xE2] = &CPU::opcode_E2; opcodeFunctions[0xE3] = &CPU::opcode_E3; opcodeFunctions[0xE4] = &CPU::opcode_E4; opcodeFunctions[0xE5] = &CPU::opcode_E5; opcodeFunctions[0xE6] = &CPU::opcode_E6; opcodeFunctions[0xE7] = &CPU::opcode_E7;
    opcodeFunctions[0xE8] = &CPU::opcode_E8; opcodeFunctions[0xE9] = &CPU::opcode_E9; opcodeFunctions[0xEA] = &CPU::opcode_EA; opcodeFunctions[0xEB] = &CPU::opcode_EB; opcodeFunctions[0xEC] = &CPU::opcode_EC; opcodeFunctions[0xED] = &CPU::opcode_ED; opcodeFunctions[0xEE] = &CPU::opcode_EE; opcodeFunctions[0xEF] = &CPU::opcode_EF;
    opcodeFunctions[0xF0] = &CPU::opcode_F0; opcodeFunctions[0xF1] = &CPU::opcode_F1; opcodeFunctions[0xF2] = &CPU::opcode_F2; opcodeFunctions[0xF3] = &CPU::opcode_F3; opcodeFunctions[0xF4] = &CPU::opcode_F4; opcodeFunctions[0xF5] = &CPU::opcode_F5; opcodeFunctions[0xF6] = &CPU::opcode_F6; opcodeFunctions[0xF7] = &CPU::opcode_F7;
    opcodeFunctions[0xF8] = &CPU::opcode_F8; opcodeFunctions[0xF9] = &CPU::opcode_F9; opcodeFunctions[0xFA] = &CPU::opcode_FA; opcodeFunctions[0xFB] = &CPU::opcode_FB; opcodeFunctions[0xFC] = &CPU::opcode_FC; opcodeFunctions[0xFD] = &CPU::opcode_FD; opcodeFunctions[0xFE] = &CPU::opcode_FE; opcodeFunctions[0xFF] = &CPU::opcode_FF;

    //Mapping CB Opcodes
    // opcodeCBFunctions[0x00] = &CPU::opcode_CB_00; opcodeCBFunctions[0x01] = &CPU::opcode_CB_01; opcodeCBFunctions[0x02] = &CPU::opcode_CB_02; opcodeCBFunctions[0x03] = &CPU::opcode_CB_03; opcodeCBFunctions[0x04] = &CPU::opcode_CB_04; opcodeCBFunctions[0x05] = &CPU::opcode_CB_05; opcodeCBFunctions[0x06] = &CPU::opcode_CB_06; opcodeCBFunctions[0x07] = &CPU::opcode_CB_07;
    // opcodeCBFunctions[0x08] = &CPU::opcode_CB_08; opcodeCBFunctions[0x09] = &CPU::opcode_CB_09; opcodeCBFunctions[0x0A] = &CPU::opcode_CB_0A; opcodeCBFunctions[0x0B] = &CPU::opcode_CB_0B; opcodeCBFunctions[0x0C] = &CPU::opcode_CB_0C; opcodeCBFunctions[0x0D] = &CPU::opcode_CB_0D; opcodeCBFunctions[0x0E] = &CPU::opcode_CB_0E; opcodeCBFunctions[0x0F] = &CPU::opcode_CB_0F;
    // opcodeCBFunctions[0x10] = &CPU::opcode_CB_10; opcodeCBFunctions[0x11] = &CPU::opcode_CB_11; opcodeCBFunctions[0x12] = &CPU::opcode_CB_12; opcodeCBFunctions[0x13] = &CPU::opcode_CB_13; opcodeCBFunctions[0x14] = &CPU::opcode_CB_14; opcodeCBFunctions[0x15] = &CPU::opcode_CB_15; opcodeCBFunctions[0x16] = &CPU::opcode_CB_16; opcodeCBFunctions[0x17] = &CPU::opcode_CB_17;
    // opcodeCBFunctions[0x18] = &CPU::opcode_CB_18; opcodeCBFunctions[0x19] = &CPU::opcode_CB_19; opcodeCBFunctions[0x1A] = &CPU::opcode_CB_1A; opcodeCBFunctions[0x1B] = &CPU::opcode_CB_1B; opcodeCBFunctions[0x1C] = &CPU::opcode_CB_1C; opcodeCBFunctions[0x1D] = &CPU::opcode_CB_1D; opcodeCBFunctions[0x1E] = &CPU::opcode_CB_1E; opcodeCBFunctions[0x1F] = &CPU::opcode_CB_1F;
    // opcodeCBFunctions[0x20] = &CPU::opcode_CB_20; opcodeCBFunctions[0x21] = &CPU::opcode_CB_21; opcodeCBFunctions[0x22] = &CPU::opcode_CB_22; opcodeCBFunctions[0x23] = &CPU::opcode_CB_23; opcodeCBFunctions[0x24] = &CPU::opcode_CB_24; opcodeCBFunctions[0x25] = &CPU::opcode_CB_25; opcodeCBFunctions[0x26] = &CPU::opcode_CB_26; opcodeCBFunctions[0x27] = &CPU::opcode_CB_27;
    // opcodeCBFunctions[0x28] = &CPU::opcode_CB_28; opcodeCBFunctions[0x29] = &CPU::opcode_CB_29; opcodeCBFunctions[0x2A] = &CPU::opcode_CB_2A; opcodeCBFunctions[0x2B] = &CPU::opcode_CB_2B; opcodeCBFunctions[0x2C] = &CPU::opcode_CB_2C; opcodeCBFunctions[0x2D] = &CPU::opcode_CB_2D; opcodeCBFunctions[0x2E] = &CPU::opcode_CB_2E; opcodeCBFunctions[0x2F] = &CPU::opcode_CB_2F;
    // opcodeCBFunctions[0x30] = &CPU::opcode_CB_30; opcodeCBFunctions[0x31] = &CPU::opcode_CB_31; opcodeCBFunctions[0x32] = &CPU::opcode_CB_32; opcodeCBFunctions[0x33] = &CPU::opcode_CB_33; opcodeCBFunctions[0x34] = &CPU::opcode_CB_34; opcodeCBFunctions[0x35] = &CPU::opcode_CB_35; opcodeCBFunctions[0x36] = &CPU::opcode_CB_36; opcodeCBFunctions[0x37] = &CPU::opcode_CB_37;
    // opcodeCBFunctions[0x38] = &CPU::opcode_CB_38; opcodeCBFunctions[0x39] = &CPU::opcode_CB_39; opcodeCBFunctions[0x3A] = &CPU::opcode_CB_3A; opcodeCBFunctions[0x3B] = &CPU::opcode_CB_3B; opcodeCBFunctions[0x3C] = &CPU::opcode_CB_3C; opcodeCBFunctions[0x3D] = &CPU::opcode_CB_3D; opcodeCBFunctions[0x3E] = &CPU::opcode_CB_3E; opcodeCBFunctions[0x3F] = &CPU::opcode_CB_3F;
    // opcodeCBFunctions[0x40] = &CPU::opcode_CB_40; opcodeCBFunctions[0x41] = &CPU::opcode_CB_41; opcodeCBFunctions[0x42] = &CPU::opcode_CB_42; opcodeCBFunctions[0x43] = &CPU::opcode_CB_43; opcodeCBFunctions[0x44] = &CPU::opcode_CB_44; opcodeCBFunctions[0x45] = &CPU::opcode_CB_45; opcodeCBFunctions[0x46] = &CPU::opcode_CB_46; opcodeCBFunctions[0x47] = &CPU::opcode_CB_47;
    // opcodeCBFunctions[0x48] = &CPU::opcode_CB_48; opcodeCBFunctions[0x49] = &CPU::opcode_CB_49; opcodeCBFunctions[0x4A] = &CPU::opcode_CB_4A; opcodeCBFunctions[0x4B] = &CPU::opcode_CB_4B; opcodeCBFunctions[0x4C] = &CPU::opcode_CB_4C; opcodeCBFunctions[0x4D] = &CPU::opcode_CB_4D; opcodeCBFunctions[0x4E] = &CPU::opcode_CB_4E; opcodeCBFunctions[0x4F] = &CPU::opcode_CB_4F;
    // opcodeCBFunctions[0x50] = &CPU::opcode_CB_50; opcodeCBFunctions[0x51] = &CPU::opcode_CB_51; opcodeCBFunctions[0x52] = &CPU::opcode_CB_52; opcodeCBFunctions[0x53] = &CPU::opcode_CB_53; opcodeCBFunctions[0x54] = &CPU::opcode_CB_54; opcodeCBFunctions[0x55] = &CPU::opcode_CB_55; opcodeCBFunctions[0x56] = &CPU::opcode_CB_56; opcodeCBFunctions[0x57] = &CPU::opcode_CB_57;
    // opcodeCBFunctions[0x58] = &CPU::opcode_CB_58; opcodeCBFunctions[0x59] = &CPU::opcode_CB_59; opcodeCBFunctions[0x5A] = &CPU::opcode_CB_5A; opcodeCBFunctions[0x5B] = &CPU::opcode_CB_5B; opcodeCBFunctions[0x5C] = &CPU::opcode_CB_5C; opcodeCBFunctions[0x5D] = &CPU::opcode_CB_5D; opcodeCBFunctions[0x5E] = &CPU::opcode_CB_5E; opcodeCBFunctions[0x5F] = &CPU::opcode_CB_5F;
    // opcodeCBFunctions[0x60] = &CPU::opcode_CB_60; opcodeCBFunctions[0x61] = &CPU::opcode_CB_61; opcodeCBFunctions[0x62] = &CPU::opcode_CB_62; opcodeCBFunctions[0x63] = &CPU::opcode_CB_63; opcodeCBFunctions[0x64] = &CPU::opcode_CB_64; opcodeCBFunctions[0x65] = &CPU::opcode_CB_65; opcodeCBFunctions[0x66] = &CPU::opcode_CB_66; opcodeCBFunctions[0x67] = &CPU::opcode_CB_67;
    // opcodeCBFunctions[0x68] = &CPU::opcode_CB_68; opcodeCBFunctions[0x69] = &CPU::opcode_CB_69; opcodeCBFunctions[0x6A] = &CPU::opcode_CB_6A; opcodeCBFunctions[0x6B] = &CPU::opcode_CB_6B; opcodeCBFunctions[0x6C] = &CPU::opcode_CB_6C; opcodeCBFunctions[0x6D] = &CPU::opcode_CB_6D; opcodeCBFunctions[0x6E] = &CPU::opcode_CB_6E; opcodeCBFunctions[0x6F] = &CPU::opcode_CB_6F;
    // opcodeCBFunctions[0x70] = &CPU::opcode_CB_70; opcodeCBFunctions[0x71] = &CPU::opcode_CB_71; opcodeCBFunctions[0x72] = &CPU::opcode_CB_72; opcodeCBFunctions[0x73] = &CPU::opcode_CB_73; opcodeCBFunctions[0x74] = &CPU::opcode_CB_74; opcodeCBFunctions[0x75] = &CPU::opcode_CB_75; opcodeCBFunctions[0x76] = &CPU::opcode_CB_76; opcodeCBFunctions[0x77] = &CPU::opcode_CB_77;
    // opcodeCBFunctions[0x78] = &CPU::opcode_CB_78; opcodeCBFunctions[0x79] = &CPU::opcode_CB_79; opcodeCBFunctions[0x7A] = &CPU::opcode_CB_7A; opcodeCBFunctions[0x7B] = &CPU::opcode_CB_7B; opcodeCBFunctions[0x7C] = &CPU::opcode_CB_7C; opcodeCBFunctions[0x7D] = &CPU::opcode_CB_7D; opcodeCBFunctions[0x7E] = &CPU::opcode_CB_7E; opcodeCBFunctions[0x7F] = &CPU::opcode_CB_7F;
    // opcodeCBFunctions[0x80] = &CPU::opcode_CB_80; opcodeCBFunctions[0x81] = &CPU::opcode_CB_81; opcodeCBFunctions[0x82] = &CPU::opcode_CB_82; opcodeCBFunctions[0x83] = &CPU::opcode_CB_83; opcodeCBFunctions[0x84] = &CPU::opcode_CB_84; opcodeCBFunctions[0x85] = &CPU::opcode_CB_85; opcodeCBFunctions[0x86] = &CPU::opcode_CB_86; opcodeCBFunctions[0x87] = &CPU::opcode_CB_87;
    // opcodeCBFunctions[0x88] = &CPU::opcode_CB_88; opcodeCBFunctions[0x89] = &CPU::opcode_CB_89; opcodeCBFunctions[0x8A] = &CPU::opcode_CB_8A; opcodeCBFunctions[0x8B] = &CPU::opcode_CB_8B; opcodeCBFunctions[0x8C] = &CPU::opcode_CB_8C; opcodeCBFunctions[0x8D] = &CPU::opcode_CB_8D; opcodeCBFunctions[0x8E] = &CPU::opcode_CB_8E; opcodeCBFunctions[0x8F] = &CPU::opcode_CB_8F;
    // opcodeCBFunctions[0x90] = &CPU::opcode_CB_90; opcodeCBFunctions[0x91] = &CPU::opcode_CB_91; opcodeCBFunctions[0x92] = &CPU::opcode_CB_92; opcodeCBFunctions[0x93] = &CPU::opcode_CB_93; opcodeCBFunctions[0x94] = &CPU::opcode_CB_94; opcodeCBFunctions[0x95] = &CPU::opcode_CB_95; opcodeCBFunctions[0x96] = &CPU::opcode_CB_96; opcodeCBFunctions[0x97] = &CPU::opcode_CB_97;
    // opcodeCBFunctions[0x98] = &CPU::opcode_CB_98; opcodeCBFunctions[0x99] = &CPU::opcode_CB_99; opcodeCBFunctions[0x9A] = &CPU::opcode_CB_9A; opcodeCBFunctions[0x9B] = &CPU::opcode_CB_9B; opcodeCBFunctions[0x9C] = &CPU::opcode_CB_9C; opcodeCBFunctions[0x9D] = &CPU::opcode_CB_9D; opcodeCBFunctions[0x9E] = &CPU::opcode_CB_9E; opcodeCBFunctions[0x9F] = &CPU::opcode_CB_9F;
    // opcodeCBFunctions[0xA0] = &CPU::opcode_CB_A0; opcodeCBFunctions[0xA1] = &CPU::opcode_CB_A1; opcodeCBFunctions[0xA2] = &CPU::opcode_CB_A2; opcodeCBFunctions[0xA3] = &CPU::opcode_CB_A3; opcodeCBFunctions[0xA4] = &CPU::opcode_CB_A4; opcodeCBFunctions[0xA5] = &CPU::opcode_CB_A5; opcodeCBFunctions[0xA6] = &CPU::opcode_CB_A6; opcodeCBFunctions[0xA7] = &CPU::opcode_CB_A7;
    // opcodeCBFunctions[0xA8] = &CPU::opcode_CB_A8; opcodeCBFunctions[0xA9] = &CPU::opcode_CB_A9; opcodeCBFunctions[0xAA] = &CPU::opcode_CB_AA; opcodeCBFunctions[0xAB] = &CPU::opcode_CB_AB; opcodeCBFunctions[0xAC] = &CPU::opcode_CB_AC; opcodeCBFunctions[0xAD] = &CPU::opcode_CB_AD; opcodeCBFunctions[0xAE] = &CPU::opcode_CB_AE; opcodeCBFunctions[0xAF] = &CPU::opcode_CB_AF;
    // opcodeCBFunctions[0xB0] = &CPU::opcode_CB_B0; opcodeCBFunctions[0xB1] = &CPU::opcode_CB_B1; opcodeCBFunctions[0xB2] = &CPU::opcode_CB_B2; opcodeCBFunctions[0xB3] = &CPU::opcode_CB_B3; opcodeCBFunctions[0xB4] = &CPU::opcode_CB_B4; opcodeCBFunctions[0xB5] = &CPU::opcode_CB_B5; opcodeCBFunctions[0xB6] = &CPU::opcode_CB_B6; opcodeCBFunctions[0xB7] = &CPU::opcode_CB_B7;
    // opcodeCBFunctions[0xB8] = &CPU::opcode_CB_B8; opcodeCBFunctions[0xB9] = &CPU::opcode_CB_B9; opcodeCBFunctions[0xBA] = &CPU::opcode_CB_BA; opcodeCBFunctions[0xBB] = &CPU::opcode_CB_BB; opcodeCBFunctions[0xBC] = &CPU::opcode_CB_BC; opcodeCBFunctions[0xBD] = &CPU::opcode_CB_BD; opcodeCBFunctions[0xBE] = &CPU::opcode_CB_BE; opcodeCBFunctions[0xBF] = &CPU::opcode_CB_BF;
    // opcodeCBFunctions[0xC0] = &CPU::opcode_CB_C0; opcodeCBFunctions[0xC1] = &CPU::opcode_CB_C1; opcodeCBFunctions[0xC2] = &CPU::opcode_CB_C2; opcodeCBFunctions[0xC3] = &CPU::opcode_CB_C3; opcodeCBFunctions[0xC4] = &CPU::opcode_CB_C4; opcodeCBFunctions[0xC5] = &CPU::opcode_CB_C5; opcodeCBFunctions[0xC6] = &CPU::opcode_CB_C6; opcodeCBFunctions[0xC7] = &CPU::opcode_CB_C7;
    // opcodeCBFunctions[0xC8] = &CPU::opcode_CB_C8; opcodeCBFunctions[0xC9] = &CPU::opcode_CB_C9; opcodeCBFunctions[0xCA] = &CPU::opcode_CB_CA; opcodeCBFunctions[0xCB] = &CPU::opcode_CB_CB; opcodeCBFunctions[0xCC] = &CPU::opcode_CB_CC; opcodeCBFunctions[0xCD] = &CPU::opcode_CB_CD; opcodeCBFunctions[0xCE] = &CPU::opcode_CB_CE; opcodeCBFunctions[0xCF] = &CPU::opcode_CB_CF;
    // opcodeCBFunctions[0xD0] = &CPU::opcode_CB_D0; opcodeCBFunctions[0xD1] = &CPU::opcode_CB_D1; opcodeCBFunctions[0xD2] = &CPU::opcode_CB_D2; opcodeCBFunctions[0xD3] = &CPU::opcode_CB_D3; opcodeCBFunctions[0xD4] = &CPU::opcode_CB_D4; opcodeCBFunctions[0xD5] = &CPU::opcode_CB_D5; opcodeCBFunctions[0xD6] = &CPU::opcode_CB_D6; opcodeCBFunctions[0xD7] = &CPU::opcode_CB_D7;
    // opcodeCBFunctions[0xD8] = &CPU::opcode_CB_D8; opcodeCBFunctions[0xD9] = &CPU::opcode_CB_D9; opcodeCBFunctions[0xDA] = &CPU::opcode_CB_DA; opcodeCBFunctions[0xDB] = &CPU::opcode_CB_DB; opcodeCBFunctions[0xDC] = &CPU::opcode_CB_DC; opcodeCBFunctions[0xDD] = &CPU::opcode_CB_DD; opcodeCBFunctions[0xDE] = &CPU::opcode_CB_DE; opcodeCBFunctions[0xDF] = &CPU::opcode_CB_DF;
    // opcodeCBFunctions[0xE0] = &CPU::opcode_CB_E0; opcodeCBFunctions[0xE1] = &CPU::opcode_CB_E1; opcodeCBFunctions[0xE2] = &CPU::opcode_CB_E2; opcodeCBFunctions[0xE3] = &CPU::opcode_CB_E3; opcodeCBFunctions[0xE4] = &CPU::opcode_CB_E4; opcodeCBFunctions[0xE5] = &CPU::opcode_CB_E5; opcodeCBFunctions[0xE6] = &CPU::opcode_CB_E6; opcodeCBFunctions[0xE7] = &CPU::opcode_CB_E7;
    // opcodeCBFunctions[0xE8] = &CPU::opcode_CB_E8; opcodeCBFunctions[0xE9] = &CPU::opcode_CB_E9; opcodeCBFunctions[0xEA] = &CPU::opcode_CB_EA; opcodeCBFunctions[0xEB] = &CPU::opcode_CB_EB; opcodeCBFunctions[0xEC] = &CPU::opcode_CB_EC; opcodeCBFunctions[0xED] = &CPU::opcode_CB_ED; opcodeCBFunctions[0xEE] = &CPU::opcode_CB_EE; opcodeCBFunctions[0xEF] = &CPU::opcode_CB_EF;
    // opcodeCBFunctions[0xF0] = &CPU::opcode_CB_F0; opcodeCBFunctions[0xF1] = &CPU::opcode_CB_F1; opcodeCBFunctions[0xF2] = &CPU::opcode_CB_F2; opcodeCBFunctions[0xF3] = &CPU::opcode_CB_F3; opcodeCBFunctions[0xF4] = &CPU::opcode_CB_F4; opcodeCBFunctions[0xF5] = &CPU::opcode_CB_F5; opcodeCBFunctions[0xF6] = &CPU::opcode_CB_F6; opcodeCBFunctions[0xF7] = &CPU::opcode_CB_F7;
    // opcodeCBFunctions[0xF8] = &CPU::opcode_CB_F8; opcodeCBFunctions[0xF9] = &CPU::opcode_CB_F9; opcodeCBFunctions[0xFA] = &CPU::opcode_CB_FA; opcodeCBFunctions[0xFB] = &CPU::opcode_CB_FB; opcodeCBFunctions[0xFC] = &CPU::opcode_CB_FC; opcodeCBFunctions[0xFD] = &CPU::opcode_CB_FD; opcodeCBFunctions[0xFE] = &CPU::opcode_CB_FE; opcodeCBFunctions[0xFF] = &CPU::opcode_CB_FF;
}