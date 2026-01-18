#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
#include <string>
#include <cstdint>

// Forward declarations to avoid circular include with readASM.h
namespace readASM {
    struct Instruction;
    class ArchvASM;
}

// Removed direct include of readASM.h

namespace instructionSet {
    //*Función para verificar que instrucción ejecutar mediante el nemónico.
    void executeInstruction(readASM::Instruction &i, bool flags[4], int16_t registers[8], uint16_t &pc);

    //*Función para sumar dos enteros.
    void add(readASM::Instruction &inst, int16_t registers[8], bool flags[4]);

    //*Función para restar dos enteros.
    void sub(readASM::Instruction &inst, int16_t registers[8], bool flags[4]);
    
    //*Función para aplicar el operador lógico and a nivel de bits.
    void andd(readASM::Instruction &inst, int16_t registers[8], bool flags[4]);
    
    //*Función para aplicar el operador lógico or a nivel de bits.
    void orr(readASM::Instruction &inst, int16_t registers[8]);
    
    //*Función para aplicar una operación lógica de comparación y así poder verificar si
    //*un número es igual al otro. Se hace una resta entre dos enteros.
    void cmp(readASM::Instruction &inst, int16_t registers[8], bool flags[4]);

    //*Función para hacer un desplazamiento lógico a nivel de bit hacia la izquierda.
    void lsl(readASM::Instruction &inst, int16_t registers[8], bool flags[4]);
    
    //*Función para hacer un desplazamiento lógico a nivel de bit hacia la derecha.
    void lsr(readASM::Instruction &inst, int16_t registers[8], bool flags[4]);
    
    //*Función para hacer un desplazamiento aritmetico a nivel de bit hacia la derecha conservando el signo.
    void asr(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void addi(readASM::Instruction* i, readASM::ArchvASM &archv);
    
    //*
    void subi(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void andi(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void ori(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void lw(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void sw(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*Función para hacer un salto hacia una línea mediante el nombre de la etiqueta.
    void jmp(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void beq(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void bne(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void bgt(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void jal(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void ret(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void RETI(readASM::Instruction* i, readASM::ArchvASM &archv);

    //*
    void HALT(readASM::Instruction* i, readASM::ArchvASM &archv);
}

#endif