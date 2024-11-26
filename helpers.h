// Programmer Name: Kylen Cheung
// Purpose: Helper class stores functions used within the program

#ifndef HELPERS_H
#define HELPERS_H

#include "register.h"

uint32_t convert(string number);
int convertRegister(string stringRegister);
void setRegisterArray(string destination, string setValueString, Register<uint32_t>* arrayRegisters);
Register<uint32_t> getRegisterValue(string destination, Register<uint32_t>* arrayRegisters);

// new overflow function (unused)
bool overflow(Register<uint32_t> register1, Register<uint32_t> register2);

// create bool function for each flag (nzcv)
bool negative(Register<uint32_t>);
bool zero(Register<uint32_t>);

#endif