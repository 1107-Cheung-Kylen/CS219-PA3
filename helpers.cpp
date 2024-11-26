#include "helpers.h"

uint32_t convert(string number){
    uint32_t converted;
    converted = stoul(number, nullptr, 16);
    return converted;
}

int convertRegister(string stringRegister){
    return stringRegister[1] - 48; // get only number from stringRegister
}

bool overflow(Register<uint32_t> reg1, Register<uint32_t> reg2){
    if(reg2.getNumber() > 4294967295 - reg1.getNumber()){ // 4294967295 is maximum value
        return true;
    }
    return false;
}

void setRegisterArray(string stringDestination, string setValueString, Register<uint32_t>* arrayRegisters){
    int destination = convertRegister(stringDestination);
    uint32_t setValue = convert(setValueString);
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

Register<uint32_t> getRegisterValue(string stringDestination, Register<uint32_t>* arrayRegisters){
    int destination = convertRegister(stringDestination);
    switch(destination){
        case 0:
            return arrayRegisters[0];
        case 1:
            return arrayRegisters[1];
        case 2:
            return arrayRegisters[2];
        case 3:
            return arrayRegisters[3];
        case 4:
            return arrayRegisters[4];
        case 5:
            return arrayRegisters[5];
        case 6:
            return arrayRegisters[6];
        case 7:
            return arrayRegisters[7];                                                                                    
    }
}


bool negative(Register<uint32_t> checkValue){
    // shift RIGHT 31 times to get remaining bit, and check if 1
    if((checkValue.getNumber()>>31) == 1){
        return true;
    }else{
        return false;
    }
}

bool zero(Register<uint32_t> checkValue){
    if(checkValue.getNumber() == 0){
        return true;
        cout << "ZERO" << endl;
    }
    return false;
}