#pragma once
#include "readASM.h"

namespace errors {
    //*Función para verificar si un nemónico de una instrucción existe,
    //*y si no existe lanza una exceptio.
    bool verifyNemonic(std::string nemonico, uint8_t &opcode, uint16_t lineNum);

    //*Función para verificar si es válida una directiva.
    bool isDirectiva(std::string directiva, uint8_t &opcode);

    //*Función para varificar si los registros de proposito general son correctos.
    bool isValidRegister(){
        
    }
}