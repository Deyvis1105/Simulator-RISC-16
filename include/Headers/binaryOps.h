#ifndef BINARYOPS_H
#define BINARYOPS_H
#include <iostream>
#include <string>
#include <cstdint>


namespace binaryOps {
    //*Función para convertir número con signo a binario.
    int decimalToBinary(int n);

    //*Función para convertir número binario con signo a hexadecimal.
    std::string binaryToHexadecimal(int n);
    
    //*Función para poner en minusculas cada caracter de un texto.
    void toLowerText(std::string &instruction);

    //*Función para poner en mayúsculas cada caracter de un text.
    void toUpperText(std::string &instruccion);

    //*Función para convertir de hexadecimal a binario.
    std::string hexTobinary(std::string hex);

    //*Función para sumar dos enteros con signo con un tamaño de 16 bits.
    int16_t sum(int16_t a, int16_t b, bool &overflow);
}

#endif