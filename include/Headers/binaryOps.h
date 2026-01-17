#pragma once
#include <iostream>
#include <string>


namespace binaryOps {
    //*Función para convertir número con signo a binario.
    int decimalToBinary(int n);

    //*Función para convertir número binario con signo a hexadecimal.
    std::string binaryToHexadecimal(int n);
    
    //*Función para poner en minusculas cada caracter de un texto.
    void toLowerText(std::string &instruction);

    //*Función para poner en mayúsculas cada caracter de un text.
    void toUpperText(std::string &instruccion);
}