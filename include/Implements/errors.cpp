#include "..\Headers\errors.h"

///Función para verificar errores en el nemónico de la instrucción.
void errors::verifyNemonico(std::string nemonico, uint8_t &opcode, uint16_t lineNum){
    if(isInstructionR(nemonico, opcode) || 
        isInstructionI(nemonico, opcode) || 
        isInstructionJ(nemonico, opcode)
        ){
            return;
        }
    
    std::string error = "Error en la linea: " + std::to_string(lineNum) + ". Error nemonico.";
    throw std::runtime_error(error);
}

///Función que verifica si una instrucción es de tipo R (Registro).
static bool isInstructionR(std::string instruction, uint8_t &opcode){
    std::string iR[8] = {"ADD", "SUB", "AND", "ORR", "CMP", "LSL", "LSR", "ASR"};

    ///Verifica nemónicos incorporados.
    if(instruction == "MOV" || instruction == "IMOV" || instruction == "NOP"){
        opcode = 0;
        return true;
    }

    for(int i = 0; i < 8; i++){
        if(instruction == iR[i]){
            opcode = i;
            return true;
        }
    }
    return false;
}

///Función que verifica si una instrucción es de tipo I (inmediato y memoria)
static bool isInstructionI(std::string instruction, uint8_t &opcode){
    std::string iI[6] = {"ADDI", "SUBI", "ANDI", "ORI", "LW", "SW"};
    for(int i = 0; i < 6; i++){
        if(iI[i] == instruction)
            opcode = i;
            return true;
    }
    return false;
}

///Función que verifica si una instrucción es de tipo J (control de flujos y saltos).
static bool isInstructionJ(std::string instruction, uint8_t &opcode){
    std::string iJ[8] = {"JMP", "BEQ", "BNE", "BGT", "JAL", "RET", "RETI", "HALT"};
    for(int i = 0; i < 8; i++){
        if(iJ[i] == instruction)
            opcode = i;
            return true;
    }
    return false;
}
