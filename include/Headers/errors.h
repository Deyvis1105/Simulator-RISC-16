#ifndef ERRORS_H
#define ERRORS_H
#include "readASM.h"
#include <iostream>
#include <vector>
#include <string>

namespace errors {
    //*Función para verificar si un nemónico de una instrucción existe,
    //*y si no existe lanza una exceptio.
    void verifyNemonic(std::string nemonico, unsigned int lineCount, uint8_t &opCode);

    //*Función para verificar si es válida una directiva.
    bool isDirectiva(std::string &directiva);

    //*Función para varificar si los registros de proposito general son correctos.
    //*Si no son correctos se lanzará una exception.
    void isValidRegister(std::vector<std::string> &args, unsigned int lineCode);

    //*Función que verifica si un nemónico es de tipo R (Registro).
    bool isInstructionR(std::string nemonic, uint8_t &opCode);

    //*Función que verifica si un nemónico es de tipo I (inmediato y memoria)
    bool isInstructionI(std::string nemonic, uint8_t &opCode);

    //*Función que verifica si un nemónico es de tipo J (control de flujos y saltos).
    bool isInstructionJ(std::string nemonic, uint8_t &opCode);
}

#endif