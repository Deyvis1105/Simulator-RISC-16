#include "..\Headers\readASM.h"

///Función para leer archivo .asm
void readASM::readArchv(std::string rut){
    std::ifstream a(rut);

    if(a.is_open()){
        std::string line = "", code = "", p;
        int count = 0;
        while(getline(a, line)){
            std::stringstream ss(line);
            while(ss >> p){
                
            }
            count = 0;
        }
        a.close();
    }
}

///Función para interpretar línea de un archivo .asm
void readASM::readInstruction(std::string line){
    std::stringstream ss(line);
    std::string p;

    while(ss >> p){

    }
}

///Función para generar el archivo de salida en lenguaje máquina.
void readASM::MLC(std::string code){
    std::ofstream archv("output.txt");

    if(archv.is_open()){
        int lengthCode = code.length();
        for(int i = 0; i < lengthCode; i++){
            archv << code[i];
        }
    }else{
        std::cout << "Error en la generacion del archivo de salida." << std::endl << std::endl;
    }
}

///Lista enumerada de instrucciones tipo R (Registro-Registro).
int instructionR(std::string instruction){
    std::string iR[8] = {"ADD", "SUB", "AND", "ORR", "CMP", "LSL", "LSR", "ASR"};
    for(int i = 0; i < 8; i++){
        if(instruction == iR[i])
            return i;
    }
    return -1;
}

///Lista enumerada de instrucciones tipo I (inmediato y memoria).
int instructionI(std::string instruction){
    std::string iI[6] = {"ADDI", "SUBI", "ANDI", "ORI", "LW", "SW"};
    for(int i = 0; i < 6; i++){
        if(iI[i] == instruction)
            return i;
    }
    return -1;
}

///Lista enumerada de intrucciones tipo j (control de flujos y saltos).
int instructionJ(std::string instruction){
    std::string iJ[8] = {"JMP", "BEQ", "BNE", "BGT", "JAL", "RET", "RETI", "HALT"};
    for(int i = 0; i < 8; i++){
        if(iJ[i] == instruction)
            return i;
    }
    return -1;
}