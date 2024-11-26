#include "register.h"

template <class T>
Register<T>::Register(){
    number = 0;
}

template <class T>
Register<T>::Register(T n){
    number = n;
}

template <class T>
Register<T>::Register(const T& rhs){
    number = rhs.number;
}

template <class T>
T Register<T>::getNumber(){
    return number;
}

template <class T>
void Register<T>::setNumber(T n){
    number = n;
}