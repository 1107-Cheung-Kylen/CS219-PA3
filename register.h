// Programmer Name: Kylen Cheung
// Purpose: Creates register objects, which are templated and can store different types of values

#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <iomanip> // used for uint32_t stream overflow
using namespace std;

template <class T>
class Register{
    T number;

    public:
        Register();
        Register(T n);
        Register(const T& rhs);

        T getNumber();
        void setNumber(T n);
};

template <class T>
ostream& operator<<(ostream&, Register<T>&);


#include "register.cpp"
#endif