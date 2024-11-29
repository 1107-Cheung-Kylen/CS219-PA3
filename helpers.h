// Programmer Name: Kylen Cheung
// Purpose: Helper class stores functions used within the program

#ifndef HELPERS_H
#define HELPERS_H

#include "register.h"

uint32_t convert(string number);
int32_t convertSigned(string number);
int convertRegister(string stringRegister);
void setRegisterArray(string destination, uint32_t setValue, Register<uint32_t>* arrayRegisters);
uint32_t getRegisterValue(string destination, Register<uint32_t>* arrayRegisters);
void displayRegisters(Register<uint32_t>* arrayRegisters);

// create bool function for each flag (nzcv)
bool negative(uint32_t);
bool zero(uint32_t);
bool carry(uint32_t reg1, uint32_t reg2, string operation);
bool carryShift(uint32_t val1, int shiftNum, string operation);
bool overflow(uint32_t reg1, uint32_t reg2, string operation);


#endif