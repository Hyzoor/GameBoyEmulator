#include "definitions.h"
#include "registerPair.h"

RegisterPair::RegisterPair(u8& high, u8& low) : highByte(high), lowByte(low){};

u8 RegisterPair::getLowValue(){
    return lowByte;
};

u8 RegisterPair::getHighValue(){
    return highByte;
};

u16 RegisterPair::getValue(){
    u16 value = (highByte << 8) | lowByte;
    return value;
};


void RegisterPair::setValue(u16 word){

    u8 high = (word & 0xFF00) >> 8;
    u8 low = (word & 0x00FF);

    lowByte = low;
    highByte = high;

};

void RegisterPair::decrement(){

    u16 actual = getValue();
    actual--;
    setValue(actual);

};

void RegisterPair::increment(){
    
    u16 actual = getValue();
    actual++;
    setValue(actual);
};