#include "..\Headers\binaryOps.h"
#include "binaryOps.h"

//*------------------------------------------------------------------------------

///Función recursiva utilizada por decimalToBinary para convertir número entero
///sin signo a binario.
int DTBR(int n){
    if(n <= 0) return 1;
    return DTBR(n / 2) * 10 + n % 10;
}

///Función para convertir número con signo a binario.
int binaryOps::decimalToBinary(int n){

    return n;
}
//*------------------------------------------------------------------------------

std::string binaryOps::binaryToHexadecimal(int n){
    return "" + (n - '0');
}

///Función para poner en minusculas cada caracter de un texto.
void binaryOps::toLowerText(std::string &instruction){
    int lengthInstruction = instruction.length();
    for(int i = 0; i < lengthInstruction; i++){
        instruction[i] = instruction[i] | 32;
    }
}

///Función para poner en mayúsculas cada caracter de un text.
void binaryOps::toUpperText(std::string &instruction){
    int lengthInstruction = instruction.length();
    for(int i = 0; i < lengthInstruction; i++){
        instruction[i] = instruction[i] & 32;
    }
}