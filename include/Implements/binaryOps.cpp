#include "..\Headers\binaryOps.h"

///Función recursiva utilizada por decimalToBinary para convertir número entero
///sin signo a binario.
static int DTBR(int n){
    if(n <= 0) return 1;
    return DTBR(n / 2) * 10 + n % 10;
}

///Función para convertir número con signo a binario.
int binaryOps::decimalToBinary(int n){

    return n;
}

///Función para co
std::string binaryOps::hexTobinary(std::string hex){
    std::string resultado = "";

    // si el usuario puso el "0x" al principio, lo volamos para quedarnos solo con el número.
    if (hex.substr(0, 2) == "0x" || hex.substr(0, 2) == "0X") {
        hex = hex.substr(2);
    }

    // recorremos el string hex y convertimos cada letra/número en sus 4 bits correspondientes.
    for (int i = 0; i < hex.length(); i++) {
        char c = toupper(hex[i]); // Lo ponemos en mayúscula para no tener problemas con 'a' o 'A'.
        switch (c) {
        case '0': resultado += "0000"; break;
        case '1': resultado += "0001"; break;
        case '2': resultado += "0010"; break;
        case '3': resultado += "0011"; break;
        case '4': resultado += "0100"; break;
        case '5': resultado += "0101"; break;
        case '6': resultado += "0110"; break;
        case '7': resultado += "0111"; break;
        case '8': resultado += "1000"; break;
        case '9': resultado += "1001"; break;
        case 'A': resultado += "1010"; break;
        case 'B': resultado += "1011"; break;
        case 'C': resultado += "1100"; break;
        case 'D': resultado += "1101"; break;
        case 'E': resultado += "1110"; break;
        case 'F': resultado += "1111"; break;
        }
    }

    // el proyecto dice que el ancho de palabra es de 16 bits, así que rellenamos con ceros. 
    while (resultado.length() < 16) resultado = "0" + resultado;

    return resultado;
}

int16_t binaryOps::sum(int16_t a, int16_t b, bool &overflow){
    int16_t result = a + b;

    if((a < 0 && b < 0) && result > 0)
        overflow = true;
    else if((a > 0 && b > 0) && result < 0)
        overflow = true;
    else
        overflow = false;
        
    return result;
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
        if(instruction[i] >= 'a' && instruction[i] <= 'z'){
            instruction[i] = instruction[i] ^ 32;
        }
    }
}