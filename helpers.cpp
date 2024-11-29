#include "helpers.h"

uint32_t convert(string number){
    uint32_t converted;
    converted = stoul(number, nullptr, 16);
    return converted;
}

int32_t convertSigned(string number){
    int32_t converted;
    converted = stoul(number, nullptr, 16);
    return converted;
}

int convertRegister(string stringRegister){
    return stringRegister[1] - 48; // get only number from stringRegister
}

void setRegisterArray(string stringDestination, uint32_t setValue, Register<uint32_t>* arrayRegisters){
    int destination = convertRegister(stringDestination);
    // uint32_t setValue = convert(setValueString);
    switch(destination){
        case 0:
            arrayRegisters[0].setNumber(setValue);
            break;
        case 1:
            arrayRegisters[1].setNumber(setValue);
            break;
        case 2:
            arrayRegisters[2].setNumber(setValue);
            break;
        case 3:
            arrayRegisters[3].setNumber(setValue);
            break;
        case 4:
            arrayRegisters[4].setNumber(setValue);
            break;
        case 5:
            arrayRegisters[5].setNumber(setValue);
            break;
        case 6:
            arrayRegisters[6].setNumber(setValue);
            break;
        case 7:
            arrayRegisters[7].setNumber(setValue);
            break;
    }
}

uint32_t getRegisterValue(string stringDestination, Register<uint32_t>* arrayRegisters){
    int destination = convertRegister(stringDestination);
    switch(destination){
        case 0:
            return arrayRegisters[0].getNumber();
        case 1:
            return arrayRegisters[1].getNumber();
        case 2:
            return arrayRegisters[2].getNumber();
        case 3:
            return arrayRegisters[3].getNumber();
        case 4:
            return arrayRegisters[4].getNumber();
        case 5:
            return arrayRegisters[5].getNumber();
        case 6:
            return arrayRegisters[6].getNumber();
        case 7:
            return arrayRegisters[7].getNumber();                                                                                    
    }
}

// Operator overload error when placed here (linking error?)
// void displayRegisters(Register<uint32_t>* arrayRegisters){
//     for(int i = 0; i < 8; i++){
//         string registerNumber = "R" + to_string(i);
//         cout << registerNumber << ":" << arrayRegisters[i] << "   "; // USE OPERATOR OVERLOAD TO DISPLAY CORRECT VALUE
//     }
//     cout << endl;
// }

// N
bool negative(uint32_t checkValue){
    // shift RIGHT 31 times to get remaining bit, and check if 1
    // if((checkValue >> 31) == 1){
    //     return true;
    // }else{
    //     return false;
    // }
    return checkValue >> 31;
}

// Z
bool zero(uint32_t checkValue){
    if(checkValue == 0){
        return true;
    }
    return false;
}

// C
bool carry(uint32_t val1, uint32_t val2, string operation){
    if(operation == "ADDS"){
        if(val1 + val2 < val1 || val1 + val2 < val2){
            return true;
        }
        else{
            return false;
        }
    }
    if(operation == "SUBS" || operation == "CMP"){ // CMP is same as SUB without setting register
        uint32_t result = val1 - val2;
        if(result < val1){
            return true;
        }
        return false;
    }
}

bool carryShift(uint32_t val1, int shiftNum, string operation){
    uint32_t checkValue;
    if(operation == "LSRS"){
        checkValue = val1 >> (shiftNum - 1); // subtract 1 to check front bit (number that is getting shifted out)
        checkValue = checkValue & 1; // mask with 1 to check if right bit is 1 
        return checkValue;
    }
    if(operation == "LSLS"){
        checkValue = val1 << (shiftNum - 1);
        checkValue = checkValue & 2147483648; // mask with 2147483648 to check if left bit is 1
        return checkValue;
    }
}

// V
bool overflow(uint32_t val1, uint32_t val2, string operation){
    if(operation == "ADDS"){
        uint32_t result = val1 + val2 + 4294967295; // 4294967295 is 0xFFFFFFFF, max of uint32_t
        return (result < 4294967295);
    }
    if(operation == "SUBS"){
        uint32_t result = val1 - val2;
        return (result > val2);

        // uint32_t a = 100;
        // uint32_t b = 200;
        // uint32_t result = a - b;
        // bool borrow = (result > a);

        // return (val2 < 0) && (val1 > 4294967295 + val2);
    }
    // return (val2 >= 0) && (val1 > 4294967295 - val1);
    // if(val2 > 4294967295 - val1){ // 4294967295 is maximum value
    //     return true;
    // }
    // return false;
}