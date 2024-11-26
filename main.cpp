// Programmer Name: Kylen Cheung
// Purpose: CS 219 PA2, a program which reads a file and calculates a resultant based on the operator and hex values

#define READFILE "Programming-Project-3.txt"
// #define READFILE "test.txt"
#include <fstream> // needed for file stream
// #include <cctype>
#include <string>
#include <iostream>
#include "helpers.h"

int main(){
    // open file stream
    ifstream fin(READFILE);
    if(fin.is_open() == true){
        Register<uint32_t> destinationRegister, registerN, registerM;
        // int destinationRegister, registerN, registerM;
        // Register<uint32_t> register0, register1, register2, register3, register4, register5, register6, register7; // create registers
        Register <uint32_t> generalRegisters[8];
        string operation, destination, operand1, operand2; // OPCODE, Rd, Rn, Rm
        bool N, Z, C, V; // n - negative, z - zero, c - carry, v - overflow
        while(fin.good() == true){
            string junk;
            // getline(fin, junk, '\n');
            // getline(fin, operation, ' ');
            fin >> operation;
            cout << operation;

            // make operation uppercase
            for(int i = 0; i < operation.length(); i++){
                operation[i] = toupper(operation[i]);
            }
            getline(fin, junk, ' ');
            getline(fin, destination, ',');
            // cout << destination;

            // MOV operations
            if(operation == "MOV"){
                getline(fin, junk, '#'); // remove # from MOV operation
                getline(fin, operand1, '\r');
                setRegisterArray(destination, operand1, generalRegisters);
                destinationRegister = getRegisterValue(destination, generalRegisters);
                cout << destinationRegister.getNumber() << endl;
            }

            // Operations with two hex numbers
            if(operation == "ADD" || operation == "ADDS" || operation == "AND" || operation == "ANDS" || operation == "ORR" || operation == "ORRS" || operation == "SUB" || operation == "SUBS" || operation == "XOR" || operation == "XORS"){
                getline(fin, operand1, ',');
                getline(fin, junk, ' '); // remove space from operand2
                getline(fin, operand2, '\n');
                registerN.setNumber(convert(operand1));
                registerM.setNumber(convert(operand2));
                if(operation == "ADD" || operation == "ADDS"){
                    destinationRegister.setNumber(destinationRegister.getNumber() + registerN.getNumber());
                    if(operation == "ADDS"){
                        N = negative(registerM);
                        Z = zero(registerM);
                    }
                }



                if(operation == "AND" || operation == "ANDS"){
                    registerM.setNumber(destinationRegister.getNumber() & registerN.getNumber());
                    if(operation == "ANDS"){
                        N = negative(registerM); // will redo how overflow is calculated
                        Z = zero(registerM);
                    }
                }
                if(operation == "ORR" || operation == "ORRS"){
                    registerM.setNumber(destinationRegister.getNumber() | registerN.getNumber());
                    if(operation == "ORRS"){
                        N = negative(registerM); // will redo how overflow is calculated
                        Z = zero(registerM);
                    }
                }
                if(operation == "SUB" || operation == "SUBS"){
                    registerM.setNumber(destinationRegister.getNumber() - registerN.getNumber());
                    if(operation == "SUBS"){
                        N = negative(registerM); // will redo how overflow is calculated
                        Z = zero(registerM);
                    }
                }
                if(operation == "XOR" || operation == "XORS"){
                    registerM.setNumber(destinationRegister.getNumber() ^ registerN.getNumber());
                    if(operation == "XORS"){
                        N = negative(registerM); // will redo how overflow is calculated
                        Z = zero(registerM);
                    }
                }                
                cout << operation << " " << destinationRegister << " " << registerN << " : " << registerM << endl;
                cout << "N: " << N << " Z: " << Z << endl;
            }

            // Operation with single hex number
            // ASR -> Arithemetic Shift Right, LSR -> Logical Shift Right, LSL -> Logical Shift Left
            if(operation == "ASR" || operation == "ASRS" || operation == "LSR" || operation == "LSRS" || operation == "LSL" || operation == "LSLS"){
                fin >> operand1 >> operand2;
                
                destinationRegister.setNumber(convert(operand1));
                // ASR -> Arithemetic Shift Right (maintains first bit to keep sign)
                if(operation == "ASR" || operation == "ASRS"){
                    registerM.setNumber(destinationRegister.getNumber() >> stoi(operand2));
                    // Shift and insert 1 into MSB
                    if(negative(destinationRegister)){ // insert 1 into Most Significant bit
                        int msbShift = 0;
                        for(int i = 0; i < stoi(operand2); i++){ // Creates bit value for number of 1s to add based off shift
                            if(i == 0){
                                msbShift = 1;
                            }else{
                                msbShift = msbShift + 10;
                            }
                        }
                        registerM.setNumber(registerM.getNumber() | (msbShift << 32 - stoi(operand2))); // applies shift
                    }
                    if(operation == "ASRS"){
                        N = negative(registerM);
                        Z = zero(registerM);
                    }
                }
                if(operation == "LSR" || operation == "LSRS"){
                    registerM.setNumber(destinationRegister.getNumber() >> stoi(operand2));
                    if(operation == "LSRS"){
                        N = negative(registerM);
                        Z = zero(registerM);
                    }
                }
                if(operation == "LSL" || operation == "LSLS"){
                    registerM.setNumber(destinationRegister.getNumber() << stoi(operand2));
                    if(operation == "LSLS"){
                        N = negative(registerM);
                        Z = zero(registerM);
                    }
                }
                cout << operation << " " << destinationRegister << " " << operand2 << " : " << registerM << endl;
                cout << "N: " << N << " Z: " << Z << endl;
            }

            // Operation with only 1 hex value
            if(operation == "NOT" || operation == "NOTS"){
                fin >> operand1;

                destinationRegister.setNumber(convert(operand1));
                registerM.setNumber(~destinationRegister.getNumber());
                if(operation == "NOTS"){
                    N = negative(registerM);
                    Z = zero(registerM);
                }

                cout << operation << " " << destinationRegister << ": " << registerM << endl;
                cout << "N: " << N << " Z: " << Z << endl;
            }

            // move switch statement to end (rn it is not setting anything since destination is still default)
            // switch(destination[1]){
            //     case 0:
            //         register0 = destinationRegister;
            //     case 1:
            //         register1 = destinationRegister;
            //     case 2:
            //         register2 = destinationRegister;
            //     case 3:
            //         register3 = destinationRegister;
            //     case 4:
            //         register4 = destinationRegister;
            //     case 5:
            //         register5 = destinationRegister;
            //     case 6:
            //         register6 = destinationRegister;
            //     case 7:
            //         register7 = destinationRegister;
            // }


        }
    }else{
        cout << "File not found!" << endl;
    }
return 0;
}

template <class T>
ostream& operator<<(ostream& out, Register<T>& r){
    out << "0x" << setw(8) << setfill('0') << hex << uppercase << r.getNumber();
    return out;
}