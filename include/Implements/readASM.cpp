#include "..\Headers\readASM.h"

//*FUNCIONES VISIBLES Y ESENCIALES PARA LA LECTURA DEL CÓDIGO .ASM.
//*-----------------------------------------------------------------------------------------------

///Función para leer archivo .asm
readASM::ArchvASM* readASM::readArchv(std::string rut){
    readASM::ArchvASM *archv = new readASM::ArchvASM();
    std::ifstream a(rut);
    uint16_t pc;
    
    if(a.is_open()){
        readASM::ArchvASM* archv = new readASM::ArchvASM();
        std::string line = "", codeMCL = "";
        
        while(getline(a, line)){
            try{
                removeComments(line);
                readLine(line, pc);
            }catch(std::runtime_error e){
                delete[] archv;
            }
            //...
        }

        a.close();
        return archv;
    }

    return nullptr;
}

///Función para interpretar línea de un archivo .asmDime
readASM::Instruction* readASM::readLine(std::string line, uint16_t lineCode){
    readASM::Instruction* instruction;
    std::stringstream ss(line);
    std::string p;
    uint8_t opcode = 0;
    ss >> p;

    if(p[0] != '.' && p[p.length() - 1] != ':'){
        errors::verifyNemonico(p, opcode, lineCode);
    }

    //... validar los argumentos (valores y rangos).
}

///Función para generar el archivo de salida en lenguaje máquina.
void readASM::MLC(std::string code){
    std::ofstream archv("output.txt");

    // if(archv.is_open()){
    //     int lengthCode = code.length();
    //     for(int i = 0; i < lengthCode; i++){
    //         archv << code[i];
    //     }
    // }else{
    //     std::cout << "Error en la generacion del archivo de salida." << std::endl << std::endl;
    // }
}

///Función para eliminar comentarios # o ;.
void readASM::removeComments(std::string &line){
    std::stringstream ss(line);
    std::string result = "", p;

    while(ss >> p){
        if(p[0] == '#' || p[0] == ';')
            break;
    }

    line = result;
}

//*-----------------------------------------------------------------------------------------------

//*FUNCIONES EXTENDIDAS DE LA CLASE "ArchvASM".
//*-----------------------------------------------------------------------------------------------

///Función de la clase ArchvASM.
///Esta función sirve para añadir una nueva instrucción a la línea de código. 
void readASM::ArchvASM::addInstruction(Instruction *instruction){
    instruction->direction = pc;

    instructions[pc] = instruction;

    if(firstInstruction == nullptr){
        firstInstruction = instruction;
        lastInstruction = instruction;
    }else{
        lastInstruction->nextInstruction = instruction;
        instruction->previousInstruction = lastInstruction;
        lastInstruction = instruction;
    }

    pc++;
}

///Función de la clase ArchvASM
///Está función sirve par aañadir una nueva etiqueta a la tabla de símbolos.
void readASM::ArchvASM::addLabel(std::string label){
    symbolTable[label] = pc;
}

///Función de la clase ArchvASM.
///Esta función sirve para obtener una instrucción con la dirección de memoria de la misma.
readASM::Instruction* readASM::ArchvASM::jumpToDirection(uint16_t direction){
    if(instructions.find(direction) != instructions.end()){
        return instructions[direction];
    }
    return nullptr;
}

///Función de la clase ArchvASM.
///Función para manejar el .org.
void readASM::ArchvASM::seLocationPC(uint16_t pc){
    this->pc = pc;
}

///Función para eliminar memoria reservada dinámicamente.
readASM::ArchvASM::~ArchvASM(){
    for(auto a : instructions){
        delete[]a.second;
    }
}

//*-----------------------------------------------------------------------------------------------