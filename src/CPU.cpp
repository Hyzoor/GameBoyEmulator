#include "CPU.h"
#include "definitions.h"

CPU::CPU():
    // A(0),B(0),C(0),D(0),E(0),F(0),H(0),L(0),
    AF(A,F),
    BC(B,C),
    DE(D,E),
    HL(H,L)
{
    A=B=C=D=E=F=H=L=0;
    SP = 0x00;
    PC = 0x00;
    opcode = 0x0;
};


