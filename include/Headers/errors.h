#pragma once
#include "readASM.h"

namespace errors {
    //*Función para verificar si un nemónico de una instrucción existe,
    //*y si no existe lanza una exceptio.
    void verifyNemonico(std::string nemonico, uint8_t &opcode, uint16_t lineNum);

    //*Función para verificar si 
}