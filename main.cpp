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
            getline(fin, junk, ' ');
            getline(fin, destination, ',');

            // MOV operations
            if(operation == "MOV"){
                getline(fin, junk, '#'); // remove # from MOV operation
                getline(fin, operand1, '\r');
                setRegisterArray(destination, convert(operand1), generalRegisters);
                cout << operation << " " << destination << ", #" << operand1 << endl;
            }

            // Operations with two hex numbers
            if(operation == "ADD" || operation == "ADDS" || operation == "AND" || operation == "ANDS" || operation == "ORR" || operation == "ORRS" || operation == "SUB" || operation == "SUBS" || operation == "XOR" || operation == "XORS"){
                getline(fin, junk, ' '); // remove space from operand2                
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
                        V = overflow(value1, value2);
                    }
                }

                if(operation == "AND" || operation == "ANDS"){
                    setRegisterArray(destination, value1 & value2, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "ANDS"){
                        // N = negative(registerM); // will redo how overflow is calculated
                        // Z = zero(registerM);
                    }
                }
                if(operation == "ORR" || operation == "ORRS"){
                    setRegisterArray(destination, value1 | value2, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "ORRS"){
                        // N = negative(registerM); // will redo how overflow is calculated
                        // Z = zero(registerM);
                    }
                }
                if(operation == "SUB" || operation == "SUBS"){
                    setRegisterArray(destination, value1 - value2, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "SUBS"){
                        // N = negative(registerM); // will redo how overflow is calculated
                        // Z = zero(registerM);
                    }
                }
                if(operation == "XOR" || operation == "XORS"){
                    setRegisterArray(destination, value1 ^ value2, generalRegisters);
                    uint32_t result = getRegisterValue(destination, generalRegisters);
                    if(operation == "XORS"){
                        // N = negative(registerM); // will redo how overflow is calculated
                        // Z = zero(registerM);
                    }
                }                
                cout << operation << " " << destination << ", " << operand1 << ", " << operand2 << endl;
            }

            // Operation with single hex number
            // ASR -> Arithemetic Shift Right, LSR -> Logical Shift Right, LSL -> Logical Shift Left
            if(operation == "ASR" || operation == "ASRS" || operation == "LSR" || operation == "LSRS" || operation == "LSL" || operation == "LSLS"){
                getline(fin, junk, ' '); // remove space from operand2                
                getline(fin, operand1, ',');
                getline(fin, junk, ' '); // remove space from operand2
                getline(fin, operand2, '\r');

                int shiftValue = convertRegister(operand2);

                // ASR -> Arithemetic Shift Right (maintains first bit to keep sign)
                if(operation == "ASR" || operation == "ASRS"){
                    int32_t value1; // int32_t for ASR only
                    setRegisterArray(destination, value1 >> shiftValue, generalRegisters);
                    if(operation == "ASRS"){
                        // set flags
                    }
                }

                // use uint32_t for the rest
                uint32_t value1 = getRegisterValue(operand1, generalRegisters);
                if(operation == "LSR" || operation == "LSRS"){
                    setRegisterArray(destination, value1 >> shiftValue, generalRegisters);
                    if(operation == "LSRS"){
                        // set flags
                    }
                }
                if(operation == "LSL" || operation == "LSLS"){
                    setRegisterArray(destination, value1 << shiftValue, generalRegisters);
                    if(operation == "LSLS"){
                        // set flags
                    }
                }
                cout << operation << " " << destination << ", " << operand1 << ", " << operand2 << endl;
            }

            // Not needed in PA3
            // // Operation with only 1 hex value
            // if(operation == "NOT" || operation == "NOTS"){
            //     fin >> operand1;

            //     destinationRegister.setNumber(convert(operand1));
            //     registerM.setNumber(~destinationRegister.getNumber());
            //     if(operation == "NOTS"){
            //         // N = negative(registerM);
            //         // Z = zero(registerM);
            //     }

            //     cout << operation << " " << destinationRegister << ": " << registerM << endl;
            //     cout << "N: " << N << " Z: " << Z << endl;
            // }

            if(operation == "CMP" || "TST"){

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