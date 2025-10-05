#pragma once
#include "definitions.h"




class RegisterPair{

public:

RegisterPair(u8&, u8&);

u8 getLowValue();
u8 getHighValue();
u16 getValue();
void setValue(u16);

private:

u8& highByte;
u8& lowByte;

};