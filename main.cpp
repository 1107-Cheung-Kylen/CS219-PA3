// Programmer Name: Kylen Cheung
// Purpose: CS 219 PA2, a program which reads a file and calculates a resultant based on the operator and hex values

#define READFILE "Programming-Project-3.txt"
// #define READFILE "test.txt"
#include <fstream> // needed for file stream
#include <iostream> // includes <string> library
#include "helpers.h"

// for some reason gave errors in helpers file (related to linking?)
void displayRegisters(Register<uint32_t>* arrayRegisters);

int main(){
    // open file stream
    ifstream fin(READFILE);
    if(fin.is_open() == true){
        Register<uint32_t> destinationRegister, registerN, registerM;
        Register <uint32_t> generalRegisters[8];
        string operation, destination, operand1, operand2; // OPCODE, Rd, Rn, Rm
        bool N, Z, C, V; // n - negative, z - zero, c - carry, v - overflow
        while(fin.good() == true){
            string junk;
            fin >> operation;

            // make operation uppercase
            for(int i = 0; i < operation.length(); i++){
                operation[i] = toupper(operation[i]);
            }
            // getline(fin, junk, ' ');
            // getline(fin, destination, ',');

            // MOV operations
            if(operation == "MOV"){
                getline(fin, junk, ' ');
                getline(fin, destination, ',');

                getline(fin, junk, '#'); // remove # from MOV operation
                getline(fin, operand1, '\r');
                setRegisterArray(destination, convert(operand1), generalRegisters);
                cout << operation << " " << destination << ", #" << operand1 << endl;
            }

            // Operations with destination and two registers
            if(operation == "ADD" || operation == "ADDS" || operation == "AND" || operation == "ANDS" || operation == "ORR" || operation == "ORRS" || operation == "SUB" || operation == "SUBS" || operation == "XOR" || operation == "XORS"){
                getline(fin, junk, ' ');
                getline(fin, destination, ',');                
                
                getline(fin, junk, ' '); // remove space from operand1
                getline(fin, operand1, ',');
                getline(fin, junk, ' '); // remove space from operand2
                getline(fin, operand2, '\r');

                // retrieve value from register array set in previous MOV operation
                uint32_t value1 = getRegisterValue(operand1, generalRegisters);
                uint32_t value2 = getRegisterValue(operand2, generalRegisters);

                if(operation == "ADD" || operation == "ADDS"){
                    setRegisterArray(destination, value1 + value2, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    // prototype for rest of them
                    if(operation == "ADDS"){
                        N = negative(result);
                        Z = zero(result);
                        C = carry(value1, value2, operation);
                        V = overflow(value1, value2, operation);
                    }
                }

                if(operation == "AND" || operation == "ANDS"){
                    setRegisterArray(destination, value1 & value2, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "ANDS"){
                        N = negative(result);
                        Z = zero(result);
                    }
                }
                if(operation == "ORR" || operation == "ORRS"){
                    setRegisterArray(destination, value1 | value2, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "ORRS"){
                        N = negative(result);
                        Z = zero(result);
                    }
                }
                if(operation == "SUB" || operation == "SUBS"){
                    setRegisterArray(destination, value1 - value2, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "SUBS"){
                        N = negative(result);
                        Z = zero(result);
                        C = carry(value1, value2, operation);
                        V = overflow(value1, value2, operation);
                    }
                }
                if(operation == "XOR" || operation == "XORS"){
                    setRegisterArray(destination, value1 ^ value2, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "XORS"){
                        N = negative(result);
                        Z = zero(result);
                    }
                }                
                cout << operation << " " << destination << ", " << operand1 << ", " << operand2 << endl;
            }

            // Operation with destination, register, and numerical value
            // ASR -> Arithemetic Shift Right, LSR -> Logical Shift Right, LSL -> Logical Shift Left
            if(operation == "ASR" || operation == "ASRS" || operation == "LSR" || operation == "LSRS" || operation == "LSL" || operation == "LSLS"){
                getline(fin, junk, ' ');
                getline(fin, destination, ',');

                getline(fin, junk, ' '); // remove space from operand1
                getline(fin, operand1, ',');
                getline(fin, junk, ' '); // remove space from operand2
                getline(fin, operand2, '\r');

                int shiftValue = convertRegister(operand2);

                // ASR -> Arithemetic Shift Right (maintains first bit to keep sign)
                // use int32_t for ASR

                // use uint32_t for the rest
                uint32_t value1 = getRegisterValue(operand1, generalRegisters);
                if(operation == "LSR" || operation == "LSRS"){
                    setRegisterArray(destination, value1 >> shiftValue, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "LSRS"){
                        N = negative(result);
                        Z = zero(result);
                        C = carryShift(value1, shiftValue, operation);
                    }
                }
                if(operation == "LSL" || operation == "LSLS"){
                    setRegisterArray(destination, value1 << shiftValue, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "LSLS"){
                        N = negative(result);
                        Z = zero(result);
                        C = carryShift(value1, shiftValue, operation);
                    }
                }
                cout << operation << " " << destination << ", " << operand1 << ", " << operand2 << endl;
            }

            // NOT & NOTS

            // Operation with no destination register
            if(operation == "CMP" || operation == "TST"){
                // NO DESTINATION REGISTERS
                
                getline(fin, junk, ' '); // remove space from operand1
                getline(fin, operand1, ',');
                getline(fin, junk, ' '); // remove space from operand2
                getline(fin, operand2, ' ');
                getline(fin, junk, '\r'); // remove <this is for extra credit> line

                uint32_t value1 = getRegisterValue(operand1, generalRegisters);
                uint32_t value2 = getRegisterValue(operand2, generalRegisters);

                if(operation == "CMP"){
                    // for CMP, if second operand is larger than first, then negative is set
                    uint32_t result = value2 - value1;
                    // if(value2 > value1){
                    //     N = true;
                    // }else{
                    //     N = false;
                    // }
                    N = (value2 > value1);
                    Z = zero(result);
                    C = carry(value1, value2, operation);
                    V = overflow(value1, value2, operation);
                }
                if(operation == "TST"){
                    uint32_t result = value1 & value2;
                    N = negative(result);
                    Z = zero(result);

                }
                cout << operation << " " << operand1 << ", " << operand2 << endl;
            }
            displayRegisters(generalRegisters);
            cout << "N: " << N << " Z: " << Z << " C: "<< C << " V: " << V << endl;
        }
    }else{
        cout << "File not found!" << endl;
    }
return 0;
}

void displayRegisters(Register<uint32_t>* arrayRegisters){
    for(int i = 0; i < 8; i++){
        string registerNumber = "R" + to_string(i);
        cout << registerNumber << ":" << arrayRegisters[i] << "   "; // USE OPERATOR OVERLOAD TO DISPLAY CORRECT VALUE
    }
    cout << endl;
}

template <class T>
ostream& operator<<(ostream& out, Register<T>& r){
    out << "0x" << setw(8) << setfill('0') << hex << uppercase << r.getNumber();
    return out;
}