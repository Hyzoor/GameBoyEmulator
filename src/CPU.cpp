#include "CPU.h"
#include "definitions.h"
#include <fstream>

CPU::CPU(): AF(A,F), BC(B,C), DE(D,E), HL(H,L){
    A=B=C=D=E=F=H=L=0;
    SP = 0x00;
    PC = 0x00;
    opcode = 0x0;
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
    fetchOpcode();
    execInstruction(opcode);
}

void CPU::fetchOpcode(){
    opcode = memoryArray[PC];
    PC++;
}

// Instructions

void CPU::load(u8& destination, u8 data){
    destination = data;
}


// Opcodes mapping with functions
void CPU::opcode_00() {}
void CPU::opcode_01() {}
void CPU::opcode_02() {}
void CPU::opcode_03() {}
void CPU::opcode_04() {}
void CPU::opcode_05() {}
void CPU::opcode_06() {load(B, memoryArray[PC++]);}
void CPU::opcode_07() {}
void CPU::opcode_08() {}
void CPU::opcode_09() {}
void CPU::opcode_0A() {}
void CPU::opcode_0B() {}
void CPU::opcode_0C() {}
void CPU::opcode_0D() {}
void CPU::opcode_0E() {load(C, memoryArray[PC++]);}
void CPU::opcode_0F() {}
void CPU::opcode_10() {}
void CPU::opcode_11() {}
void CPU::opcode_12() {}
void CPU::opcode_13() {}
void CPU::opcode_14() {}
void CPU::opcode_15() {}
void CPU::opcode_16() {load(D, memoryArray[PC++]);}
void CPU::opcode_17() {}
void CPU::opcode_18() {}
void CPU::opcode_19() {}
void CPU::opcode_1A() {}
void CPU::opcode_1B() {}
void CPU::opcode_1C() {}
void CPU::opcode_1D() {}
void CPU::opcode_1E() {load(E, memoryArray[PC++]);}
void CPU::opcode_1F() {}
void CPU::opcode_20() {}
void CPU::opcode_21() {}
void CPU::opcode_22() {}
void CPU::opcode_23() {}
void CPU::opcode_24() {}
void CPU::opcode_25() {}
void CPU::opcode_26() {load(H, memoryArray[PC++]);}
void CPU::opcode_27() {}
void CPU::opcode_28() {}
void CPU::opcode_29() {}
void CPU::opcode_2A() {}
void CPU::opcode_2B() {}
void CPU::opcode_2C() {}
void CPU::opcode_2D() {}
void CPU::opcode_2E() {load(L, memoryArray[PC++]);}
void CPU::opcode_2F() {}
void CPU::opcode_30() {}
void CPU::opcode_31() {}
void CPU::opcode_32() {}
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
void CPU::opcode_3E() {}
void CPU::opcode_3F() {}
void CPU::opcode_40() {load(B, B);}
void CPU::opcode_41() {load(B, C);}
void CPU::opcode_42() {load(B, D);}
void CPU::opcode_43() {load(B, E);}
void CPU::opcode_44() {load(B, H);}
void CPU::opcode_45() {load(B, L);}
void CPU::opcode_46() {load(B, memoryArray[HL.getValue()]);}
void CPU::opcode_47() {}
void CPU::opcode_48() {load(C, B);}
void CPU::opcode_49() {load(C, C);}
void CPU::opcode_4A() {load(C, D);}
void CPU::opcode_4B() {load(C, E);}
void CPU::opcode_4C() {load(C, H);}
void CPU::opcode_4D() {load(C, L);}
void CPU::opcode_4E() {load(C, memoryArray[HL.getValue()]);}
void CPU::opcode_4F() {}
void CPU::opcode_50() {load(D, B);}
void CPU::opcode_51() {load(D, C);}
void CPU::opcode_52() {load(D, D);}
void CPU::opcode_53() {load(D, E);}
void CPU::opcode_54() {load(D, H);}
void CPU::opcode_55() {load(D, L);}
void CPU::opcode_56() {load(D, memoryArray[HL.getValue()]);}
void CPU::opcode_57() {}
void CPU::opcode_58() {load(E, B);}
void CPU::opcode_59() {load(E, C);}
void CPU::opcode_5A() {load(E, D);}
void CPU::opcode_5B() {load(E, E);}
void CPU::opcode_5C() {load(E, H);}
void CPU::opcode_5D() {load(E, L);}
void CPU::opcode_5E() {load(E, memoryArray[HL.getValue()]);}
void CPU::opcode_5F() {}
void CPU::opcode_60() {load(H, B);}
void CPU::opcode_61() {load(H, C);}
void CPU::opcode_62() {load(H, D);}
void CPU::opcode_63() {load(H, E);}
void CPU::opcode_64() {load(H, H);}
void CPU::opcode_65() {load(H, L);}
void CPU::opcode_66() {load(H, memoryArray[HL.getValue()]);}
void CPU::opcode_67() {}
void CPU::opcode_68() {load(L, B);}
void CPU::opcode_69() {load(L, C);}
void CPU::opcode_6A() {load(L, D);}
void CPU::opcode_6B() {load(L, E);}
void CPU::opcode_6C() {load(L, H);}
void CPU::opcode_6D() {load(L, L);}
void CPU::opcode_6E() {load(L,memoryArray[HL.getValue()]);}
void CPU::opcode_6F() {}
void CPU::opcode_70() {load(memoryArray[HL.getValue()], B);}
void CPU::opcode_71() {load(memoryArray[HL.getValue()], C);}
void CPU::opcode_72() {load(memoryArray[HL.getValue()], D);}
void CPU::opcode_73() {load(memoryArray[HL.getValue()], E);}
void CPU::opcode_74() {load(memoryArray[HL.getValue()], H);}
void CPU::opcode_75() {load(memoryArray[HL.getValue()], L);}
void CPU::opcode_76() {}
void CPU::opcode_77() {}
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
void CPU::opcode_E0() {}
void CPU::opcode_E1() {}
void CPU::opcode_E2() {}
void CPU::opcode_E3() {}
void CPU::opcode_E4() {}
void CPU::opcode_E5() {}
void CPU::opcode_E6() {}
void CPU::opcode_E7() {}
void CPU::opcode_E8() {}
void CPU::opcode_E9() {}
void CPU::opcode_EA() {}
void CPU::opcode_EB() {}
void CPU::opcode_EC() {}
void CPU::opcode_ED() {}
void CPU::opcode_EE() {}
void CPU::opcode_EF() {}
void CPU::opcode_F0() {}
void CPU::opcode_F1() {}
void CPU::opcode_F2() {}
void CPU::opcode_F3() {}
void CPU::opcode_F4() {}
void CPU::opcode_F5() {}
void CPU::opcode_F6() {}
void CPU::opcode_F7() {}
void CPU::opcode_F8() {}
void CPU::opcode_F9() {}
void CPU::opcode_FA() {}
void CPU::opcode_FB() {}
void CPU::opcode_FC() {}
void CPU::opcode_FD() {}
void CPU::opcode_FE() {}
void CPU::opcode_FF() {} 


void CPU::execInstruction(u8 opcode){
    switch (opcode) {
        case 0x00: opcode_00(); break; case 0x01: opcode_01(); break; case 0x02: opcode_02(); break; case 0x03: opcode_03(); break; case 0x04: opcode_04(); break; case 0x05: opcode_05(); break; case 0x06: opcode_06(); break; case 0x07: opcode_07(); break; case 0x08: opcode_08(); break; case 0x09: opcode_09(); break; case 0x0A: opcode_0A(); break; case 0x0B: opcode_0B(); break; case 0x0C: opcode_0C(); break; case 0x0D: opcode_0D(); break; case 0x0E: opcode_0E(); break; case 0x0F: opcode_0F(); break;
        case 0x10: opcode_10(); break; case 0x11: opcode_11(); break; case 0x12: opcode_12(); break; case 0x13: opcode_13(); break; case 0x14: opcode_14(); break; case 0x15: opcode_15(); break; case 0x16: opcode_16(); break; case 0x17: opcode_17(); break; case 0x18: opcode_18(); break; case 0x19: opcode_19(); break; case 0x1A: opcode_1A(); break; case 0x1B: opcode_1B(); break; case 0x1C: opcode_1C(); break; case 0x1D: opcode_1D(); break; case 0x1E: opcode_1E(); break; case 0x1F: opcode_1F(); break;
        case 0x20: opcode_20(); break; case 0x21: opcode_21(); break; case 0x22: opcode_22(); break; case 0x23: opcode_23(); break; case 0x24: opcode_24(); break; case 0x25: opcode_25(); break; case 0x26: opcode_26(); break; case 0x27: opcode_27(); break; case 0x28: opcode_28(); break; case 0x29: opcode_29(); break; case 0x2A: opcode_2A(); break; case 0x2B: opcode_2B(); break; case 0x2C: opcode_2C(); break; case 0x2D: opcode_2D(); break; case 0x2E: opcode_2E(); break; case 0x2F: opcode_2F(); break;
        case 0x30: opcode_30(); break; case 0x31: opcode_31(); break; case 0x32: opcode_32(); break; case 0x33: opcode_33(); break; case 0x34: opcode_34(); break; case 0x35: opcode_35(); break; case 0x36: opcode_36(); break; case 0x37: opcode_37(); break; case 0x38: opcode_38(); break; case 0x39: opcode_39(); break; case 0x3A: opcode_3A(); break; case 0x3B: opcode_3B(); break; case 0x3C: opcode_3C(); break; case 0x3D: opcode_3D(); break; case 0x3E: opcode_3E(); break; case 0x3F: opcode_3F(); break;
        case 0x40: opcode_40(); break; case 0x41: opcode_41(); break; case 0x42: opcode_42(); break; case 0x43: opcode_43(); break; case 0x44: opcode_44(); break; case 0x45: opcode_45(); break; case 0x46: opcode_46(); break; case 0x47: opcode_47(); break; case 0x48: opcode_48(); break; case 0x49: opcode_49(); break; case 0x4A: opcode_4A(); break; case 0x4B: opcode_4B(); break; case 0x4C: opcode_4C(); break; case 0x4D: opcode_4D(); break; case 0x4E: opcode_4E(); break; case 0x4F: opcode_4F(); break;
        case 0x50: opcode_50(); break; case 0x51: opcode_51(); break; case 0x52: opcode_52(); break; case 0x53: opcode_53(); break; case 0x54: opcode_54(); break; case 0x55: opcode_55(); break; case 0x56: opcode_56(); break; case 0x57: opcode_57(); break; case 0x58: opcode_58(); break; case 0x59: opcode_59(); break; case 0x5A: opcode_5A(); break; case 0x5B: opcode_5B(); break; case 0x5C: opcode_5C(); break; case 0x5D: opcode_5D(); break; case 0x5E: opcode_5E(); break; case 0x5F: opcode_5F(); break;
        case 0x60: opcode_60(); break; case 0x61: opcode_61(); break; case 0x62: opcode_62(); break; case 0x63: opcode_63(); break; case 0x64: opcode_64(); break; case 0x65: opcode_65(); break; case 0x66: opcode_66(); break; case 0x67: opcode_67(); break; case 0x68: opcode_68(); break; case 0x69: opcode_69(); break; case 0x6A: opcode_6A(); break; case 0x6B: opcode_6B(); break; case 0x6C: opcode_6C(); break; case 0x6D: opcode_6D(); break; case 0x6E: opcode_6E(); break; case 0x6F: opcode_6F(); break;
        case 0x70: opcode_70(); break; case 0x71: opcode_71(); break; case 0x72: opcode_72(); break; case 0x73: opcode_73(); break; case 0x74: opcode_74(); break; case 0x75: opcode_75(); break; case 0x76: opcode_76(); break; case 0x77: opcode_77(); break; case 0x78: opcode_78(); break; case 0x79: opcode_79(); break; case 0x7A: opcode_7A(); break; case 0x7B: opcode_7B(); break; case 0x7C: opcode_7C(); break; case 0x7D: opcode_7D(); break; case 0x7E: opcode_7E(); break; case 0x7F: opcode_7F(); break;
        case 0x80: opcode_80(); break; case 0x81: opcode_81(); break; case 0x82: opcode_82(); break; case 0x83: opcode_83(); break; case 0x84: opcode_84(); break; case 0x85: opcode_85(); break; case 0x86: opcode_86(); break; case 0x87: opcode_87(); break; case 0x88: opcode_88(); break; case 0x89: opcode_89(); break; case 0x8A: opcode_8A(); break; case 0x8B: opcode_8B(); break; case 0x8C: opcode_8C(); break; case 0x8D: opcode_8D(); break; case 0x8E: opcode_8E(); break; case 0x8F: opcode_8F(); break;
        case 0x90: opcode_90(); break; case 0x91: opcode_91(); break; case 0x92: opcode_92(); break; case 0x93: opcode_93(); break; case 0x94: opcode_94(); break; case 0x95: opcode_95(); break; case 0x96: opcode_96(); break; case 0x97: opcode_97(); break; case 0x98: opcode_98(); break; case 0x99: opcode_99(); break; case 0x9A: opcode_9A(); break; case 0x9B: opcode_9B(); break; case 0x9C: opcode_9C(); break; case 0x9D: opcode_9D(); break; case 0x9E: opcode_9E(); break; case 0x9F: opcode_9F(); break;
        case 0xA0: opcode_A0(); break; case 0xA1: opcode_A1(); break; case 0xA2: opcode_A2(); break; case 0xA3: opcode_A3(); break; case 0xA4: opcode_A4(); break; case 0xA5: opcode_A5(); break; case 0xA6: opcode_A6(); break; case 0xA7: opcode_A7(); break; case 0xA8: opcode_A8(); break; case 0xA9: opcode_A9(); break; case 0xAA: opcode_AA(); break; case 0xAB: opcode_AB(); break; case 0xAC: opcode_AC(); break; case 0xAD: opcode_AD(); break; case 0xAE: opcode_AE(); break; case 0xAF: opcode_AF(); break;
        case 0xB0: opcode_B0(); break; case 0xB1: opcode_B1(); break; case 0xB2: opcode_B2(); break; case 0xB3: opcode_B3(); break; case 0xB4: opcode_B4(); break; case 0xB5: opcode_B5(); break; case 0xB6: opcode_B6(); break; case 0xB7: opcode_B7(); break; case 0xB8: opcode_B8(); break; case 0xB9: opcode_B9(); break; case 0xBA: opcode_BA(); break; case 0xBB: opcode_BB(); break; case 0xBC: opcode_BC(); break; case 0xBD: opcode_BD(); break; case 0xBE: opcode_BE(); break; case 0xBF: opcode_BF(); break;
        case 0xC0: opcode_C0(); break; case 0xC1: opcode_C1(); break; case 0xC2: opcode_C2(); break; case 0xC3: opcode_C3(); break; case 0xC4: opcode_C4(); break; case 0xC5: opcode_C5(); break; case 0xC6: opcode_C6(); break; case 0xC7: opcode_C7(); break; case 0xC8: opcode_C8(); break; case 0xC9: opcode_C9(); break; case 0xCA: opcode_CA(); break; case 0xCB: opcode_CB(); break; case 0xCC: opcode_CC(); break; case 0xCD: opcode_CD(); break; case 0xCE: opcode_CE(); break; case 0xCF: opcode_CF(); break;
        case 0xD0: opcode_D0(); break; case 0xD1: opcode_D1(); break; case 0xD2: opcode_D2(); break; case 0xD3: opcode_D3(); break; case 0xD4: opcode_D4(); break; case 0xD5: opcode_D5(); break; case 0xD6: opcode_D6(); break; case 0xD7: opcode_D7(); break; case 0xD8: opcode_D8(); break; case 0xD9: opcode_D9(); break; case 0xDA: opcode_DA(); break; case 0xDB: opcode_DB(); break; case 0xDC: opcode_DC(); break; case 0xDD: opcode_DD(); break; case 0xDE: opcode_DE(); break; case 0xDF: opcode_DF(); break;
        case 0xE0: opcode_E0(); break; case 0xE1: opcode_E1(); break; case 0xE2: opcode_E2(); break; case 0xE3: opcode_E3(); break; case 0xE4: opcode_E4(); break; case 0xE5: opcode_E5(); break; case 0xE6: opcode_E6(); break; case 0xE7: opcode_E7(); break; case 0xE8: opcode_E8(); break; case 0xE9: opcode_E9(); break; case 0xEA: opcode_EA(); break; case 0xEB: opcode_EB(); break; case 0xEC: opcode_EC(); break; case 0xED: opcode_ED(); break; case 0xEE: opcode_EE(); break; case 0xEF: opcode_EF(); break;
        case 0xF0: opcode_F0(); break; case 0xF1: opcode_F1(); break; case 0xF2: opcode_F2(); break; case 0xF3: opcode_F3(); break; case 0xF4: opcode_F4(); break; case 0xF5: opcode_F5(); break; case 0xF6: opcode_F6(); break; case 0xF7: opcode_F7(); break; case 0xF8: opcode_F8(); break; case 0xF9: opcode_F9(); break; case 0xFA: opcode_FA(); break; case 0xFB: opcode_FB(); break; case 0xFC: opcode_FC(); break; case 0xFD: opcode_FD(); break; case 0xFE: opcode_FE(); break; case 0xFF: opcode_FF(); break;
    }
}