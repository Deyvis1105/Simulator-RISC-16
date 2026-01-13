#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <sstream>
#include "..\Headers\binaryOps.h"

namespace readASM {

    //*Clase para crear objeto c 
    class ArchvASM {
        private:
            uint16_t memory[65536];
            uint8_t psr[4] = {0};
    };

    //*Función para obtener todas las líneas de código del archivo .asm.
    void readArchv(std::string rut);

    //*Función para interpretar línea escrita en archivo .asm
    void readInstruction(std::string line);

    //*Función MLC (Maching lenguage code) para generar el archivo de salida en lenguaje máquina.
    void MLC(std::string code);
}