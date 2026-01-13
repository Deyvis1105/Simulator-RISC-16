#include "..\Headers\readASM.h"

///Lista enumerada de instrucciones tipo R (Registro-Registro).
enum instrucctionR {
    ADD, SUB, AND, ORR, CMP, LSL, LSR, ASR
};

///Lista enumerada de instrucciones tipo I (inmediato y memoria).
enum instructionI {
    ADDI, SUBI, ANDI, ORI, LW, SW
};

///Lista enumerada de intrucciones tipo j (control de flujos y saltos).
enum instructionJ {
    JMP, BEQ, BNE, BGT, JAL, RET, RETI, HALT
};

///Función para leer archivo .asm
void readASM::readArchv(std::string rut){
    std::ifstream a(rut);

    if(a.is_open()){
        std::string line = "";
        while(getline(a, line)){
            
        }
        a.close();
    }
}

///Función para interpretar línea de un archivo .asn
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