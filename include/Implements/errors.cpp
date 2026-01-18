#include "..\Headers\errors.h"

///Función para verificar errores en el nemónico de la instrucción.
void errors::verifyNemonic(std::string nemonico, unsigned int lineCount, uint8_t &opCode){
    if(isInstructionR(nemonico, opCode) || 
        isInstructionI(nemonico, opCode) || 
        isInstructionJ(nemonico, opCode)
        ){
            return;
        }
    
    throw std::runtime_error("Instruccion desconocida en la linea: " + std::to_string(lineCount) + ".");
}

///Función para verificar si es una directiva.
bool errors::isDirectiva(std::string &directiva){
    std::string directivas[4] = {".org", ".word", ".space", ".string"};
    for(int i = 0; i < 4; i++){
        if(directiva == directivas[i]){
            directiva = directiva.substr(1, directiva.length());
            return true;
        }
    }
    return false;
}

///Función que verifica si una instrucción es de tipo R (Registro).
void errors::isValidRegister(std::vector<std::string> & args, unsigned int lineCode){
    size_t length = args.size();
    for(size_t i = 0; i < length; i++){
        if(args[i][0] == 'R')
            if(!(args[i][1] >= '0' && args[i][1] <= '7'))
                throw std::runtime_error("Error en la linea " + std::to_string(lineCode) + ". Registro no existente.");
    }
}

bool errors::isInstructionR(std::string nemonic, uint8_t &opCode){

    std::string iR[8] = {"ADD", "SUB", "AND", "ORR", "CMP", "LSL", "LSR", "ASR"};

    ///Verifica nemónicos incorporados.
    if(nemonic == "MOV" || nemonic == "IMOV" || nemonic == "NOP"){
        opCode = 0;
        return true;
    }

    for(int i = 0; i < 8; i++){
        if(nemonic == iR[i]){
            opCode = i;
            return true;
        }
    }
    return false;
}

///Función que verifica si una instrucción es de tipo I (inmediato y memoria)
bool errors::isInstructionI(std::string nemonic, uint8_t &opCode){
    std::string iI[6] = {"ADDI", "SUBI", "ANDI", "ORI", "LW", "SW"};
    for(int i = 0; i < 6; i++){
        if(iI[i] == nemonic){
            opCode = i + 8;
            return true;
        }
    }
    return false;
}

///Función que verifica si una instrucción es de tipo J (control de flujos y saltos).
bool errors::isInstructionJ(std::string nemonic, uint8_t &opCode){
    std::string iJ[8] = {"JMP", "BEQ", "BNE", "BGT", "JAL", "RET", "RETI", "HALT"};
    for(int i = 0; i < 8; i++){
        if(iJ[i] == nemonic){
            opCode = i + 6;
            return true;
        }
    }
    return false;
}
