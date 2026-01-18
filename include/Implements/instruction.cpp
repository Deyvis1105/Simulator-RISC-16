#include "..\Headers\readASM.h"
#include "..\Headers\instruction.h"

//*FUNCIONES VISIBLES Y ESENCIALES PARA LA EJECUCIÓN DE INSTRUCCIONES.
//*-----------------------------------------------------------------------------------------------

///Función para ejecutar una instrucción y convierte la instrucción el lenguaje máquina.
void instructionSet::executeInstruction(
    readASM::Instruction &inst, 
    bool flags[4], 
    int16_t registers[8], 
    uint16_t &pc){

    switch (inst.opCode){
    case 0:
        add(inst, registers, flags);
        break;
    
    default:
        break;
    }
}

///Función para sumar dos enteros.
void instructionSet::add(readASM::Instruction &inst, int16_t registers[8], bool flags[4]){
    int32_t result = 0;
    unsigned int rd = inst.args.back()[1] - '0';
    int16_t r1 = registers[inst.args[0][1] - '0'];
    int16_t r2 = registers[inst.args[1][1] - '0'];
    
    
    ///Verifica si el resultado de la operación es 0 o se está almacenando el valor en R0.
    if(rd == 0 || result == 0)
        flags[0] = true;
    else
        flags[0] = true;
    
    ///Vefifica si el resultado es negativo
    if(result < 0)
        flags[1] = true;
    else
        flags[1] = false;
    
    ///Verifica si la suma produjo un acarreo.
    if(((uint16_t)r1 + (uint16_t)r2) > 0xFFFF)
        flags[2] = true;
    else
        flags[2] = false;

    registers[rd] = binaryOps::sum(r1, r2, flags[4]);
}

///Función para restar dos enteros.
void instructionSet::sub(readASM::Instruction &inst, int16_t registers[8], bool flags[4]){
    int32_t result = 0;
    unsigned int rd = inst.args.back()[1] - '0';
    int16_t r1 = registers[inst.args[0][1] - '0'];
    int16_t r2 = registers[inst.args[1][1] - '0'];
    
    
    ///Verifica si el resultado de la operación es 0 o se está almacenando el valor en R0.
    if(rd == 0 || result == 0)
        flags[0] = true;
    else
        flags[0] = true;
    
    ///Vefifica si el resultado es negativo
    if(result < 0)
        flags[1] = true;
    else
        flags[1] = false;
    
    ///Verifica si la suma produjo un acarreo.
    if((uint16_t)r1 < (uint16_t)r2)
        flags[2] = true;
    else
        flags[2] = false;

    registers[rd] = binaryOps::sum(r1, r2, flags[4]);
}

///Función para aplicar el and lógico a nivel de bit.
void instructionSet::andd(readASM::Instruction &inst, int16_t registers[8], bool flags[4]){
    unsigned int rd = inst.args.back()[1] - '0';
    int16_t result = registers[inst.args[0][1] - '0'] & registers[inst.args[1][1] - '0'];

    ///Verifica si el resultado de la operación es 0 o se está almacenando el valor en R0.
    if(rd == 0 && result == 0)
        flags[0] = true;
    else
        flags[0] = false;

    ///Verifica si el resultado es 0.
    if(result < 0)
        flags[1] = true;
    else
        flags[1] = false;
    
}

///Función para aplicar el operador or lógico a nivel. 
void instructionSet::orr(readASM::Instruction &inst, int16_t registers[8]){
    unsigned int rd = inst.args.back()[1] - '0';
    int16_t result = registers[inst.args[0][1] - '0'] | registers[inst.args[1][1] - '0'];
}

///Función para comparar
void instructionSet::cmp(readASM::Instruction &inst, int16_t registers[8], bool flags[4]){
    int32_t result = 0;
    unsigned int rd = inst.args.back()[1] - '0';
    int16_t r1 = registers[inst.args[0][1] - '0'];
    int16_t r2 = registers[inst.args[1][1] - '0'];
    
    
    ///Verifica si el resultado de la operación es 0 o se está almacenando el valor en R0.
    if(rd == 0 || result == 0)
        flags[0] = true;
    else
        flags[0] = true;
    
    ///Vefifica si el resultado es negativo
    if(result < 0)
        flags[1] = true;
    else
        flags[1] = false;
    
    ///Verifica si la suma produjo un acarreo.
    if((uint16_t)r1 < (uint16_t)r2)
        flags[2] = true;
    else
        flags[2] = false;
}

///Función para desplazar logicamente bits hacia la derecha.
void instructionSet::lsl(readASM::Instruction &inst, int16_t registers[8], bool flags[4]){
    // uint resultado
}
///Función para desplazar logicamente bits hacia la izquierda.
void instructionSet::lsr(readASM::Instruction &inst, int16_t registers[8], bool flags[4]){

}

///Función para desplazar aritmeticamente los bits hacia la derecha conservando el signo.
void instructionSet::asr(readASM::Instruction* i, readASM::ArchvASM &archv){

}

void instructionSet::addi(readASM::Instruction* i, readASM::ArchvASM &archv){

}

void instructionSet::subi(readASM::Instruction* i, readASM::ArchvASM &archv){

}

void instructionSet::andi(readASM::Instruction* i, readASM::ArchvASM &archv){

}

void instructionSet::ori(readASM::Instruction* i, readASM::ArchvASM &archv){

}

void instructionSet::lw(readASM::Instruction* i, readASM::ArchvASM &archv){

}

void instructionSet::sw(readASM::Instruction* i, readASM::ArchvASM &archv){

}

void instructionSet::jmp(readASM::Instruction* i, readASM::ArchvASM &archv){
    
}

//*-----------------------------------------------------------------------------------------------

//*FUNCIONES ESTATICAS NO VISIBLES AFUERA DEL ARCHIVO.
//*-----------------------------------------------------------------------------------------------
static const std::string iR[8] = {"ADD", "SUB", "AND", "ORR", "CMP", "LSL", "LSR", "ASR"};
static const std::string iI[6] = {"ADDI", "SUBI", "ANDI", "ORI", "LW", "SW"};
static const std::string iJ[8] = {"JMP", "BEQ", "BNE", "BGT", "JAL", "RET", "RETI", "HALT"};

///Obtener el cógio binario de un registro.
static std::string binaryRegisters(bool flags[4]){
    return "";
}

///Obtener código de operación mediante el nemónico.
///Se le concatenará tambien el tipo.
static std::string binaryCopAndType(std::string nemonic, char type){
    if(type == 'R'){
        for(int i = 0; i < 8; i++)
        if(nemonic == iR[i])
        return iR[i] + "00";
    } else if(type == 'I'){
        for(int i = 0; i < 8; i++)
            if(nemonic == iI[i])
                return iI[i] + "01";
    }else if(type == 'J'){
        for(int i = 0; i < 8; i++)
            if(nemonic == iJ[i])
                return iJ[i] + "10";
    }
}

//*-----------------------------------------------------------------------------------------------