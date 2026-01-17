#pragma once
#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <sstream>
#include "binaryOps.h"
#include "errors.h"
#include <vector>
#include <map>

namespace readASM {
    //*Estructura que contiene una línea de cada instrucción y que además, cada
    //*estrutura apunta a la siguiente y a la anterior.
    struct Instruction{
        uint8_t opCode;
        uint16_t direction;
        uint16_t rds[3] = {};
        std::string nemonico;
        std::vector<std::string> args;
        char typeInstruction;

        Instruction *nextInstruction;
        Instruction *previousInstruction;
    };

    //*Clase para crear objeto c 
    class ArchvASM {
        private:
        uint16_t bankRegister[8] = {0};
        uint16_t pc_initial;
        uint16_t pc;
        
        std::map<uint16_t, Instruction*> instructions;
        std::map<std::string, uint16_t> symbolTable;
        
        Instruction *firstInstruction;
        Instruction *lastInstruction;
        
        public:
            const uint16_t MEMORY_MAX = 0xffff;
            //*Función para agregar una nueva instrucción a la línea de código.
            void addInstruction(Instruction *instruction);

            //*Función para agregar una nuevo etiqueta.
            void addLabel(std::string label);

            //*Función para hacer un salto a una instrucción.
            Instruction* jumpToDirection(uint16_t direction);

            //*Función para localizar la memoria mediante el .org
            void seLocationPC(uint16_t pc);

            //*Función para eliminar memoria una vez terminado el programa.
            ~ArchvASM();
    };

    //*Función para obtener todas las líneas de código del archivo .asm.
    ArchvASM* readArchv(std::string rut);

    //*Función para interpretar línea escrita en archivo .asm
    Instruction* readInstruction(uint8_t opcode, std::stringstream& args, uint16_t lineCode);

    //*Función para dividir argumentos por coma.
    std::vector<std::string> splitArgs(std::stringstream &ss);

    //*Función MLC (Maching lenguage code) para generar el archivo de salida en lenguaje máquina.
    void MLC(std::string code);

    //*Función para eliminar los comentarios de una línea de un archivo .asm.
    void removeComments(std::string &line);

}