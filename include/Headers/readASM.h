#ifndef READASM_H
#define READASM_H
#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "binaryOps.h"
#include "errors.h"

namespace readASM {
    //*Estructura que contiene una línea de cada instrucción y que además, cada
    //*estrutura apunta a la siguiente y a la anterior.
    struct Instruction{
        uint16_t direction;
        uint8_t opCode;
        std::string label;
        std::string nemonic;
        std::vector<std::string> args = {};
        
        uint16_t machineCode;
        std::string originalCode;
        bool isDirective = false; 

        Instruction *nextInstruction = nullptr;
        Instruction *previousInstruction = nullptr;
};

    //*Clase para crear objeto c
    class ArchvASM {
        private:
            bool flags[4] = {false};
            int16_t bankRegister[8] = {0};
            uint16_t pc = 0;
            uint16_t pcMax = 0;
            
            std::map<uint16_t, Instruction*> instructions;
            std::map<std::string, uint16_t> symbolTable;
            
            Instruction *firstInstruction = nullptr;
            Instruction *lastInstruction = nullptr;
        
        public:
            const uint16_t pc_initial = 0;
            const uint16_t MEMORY_MAX = 0xffff;

            //*Constructor de la clase Archv.
            ArchvASM(){};

            //*Función para agregar una nueva instrucción a la línea de código.
            void addInstruction(Instruction *instruction, uint16_t pc);

            //*Función para agregar una nuevo etiqueta.
            void addLabel(std::string label, uint16_t pc);

            //*Función para hacer un salto a una instrucción.
            Instruction* jumpToDirection(uint16_t direction);

            //*Función para localizar la memoria mediante el .org
            void seLocationPC(uint16_t pc);

            //*Función para ejecutar el programa.
            void executeProgram();

            //*Función para eliminar memoria una vez terminado el programa.
            ~ArchvASM();
    };

    //*Función para obtener todas las líneas de código del archivo .asm.
    ArchvASM* readArchv(std::string rut);

    //*Función para interpretar línea escrita en archivo .asm
    Instruction* readLine(
        std::string nemonic, 
        std::stringstream &args, 
        uint16_t pc, 
        unsigned int lineCount, 
        std::string &label
    );

    //*Función para dividir argumentos por coma.
    std::vector<std::string> splitArgs(std::stringstream &ss);

    //*Función MLC (Maching lenguage code) para generar el archivo de salida en lenguaje máquina.
    void MLC(std::string code);

    //*Función para eliminar los comentarios de una línea de un archivo .asm.
    void removeComments(std::string &line);

}

#endif