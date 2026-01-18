#include "..\Headers\readASM.h"
#include "..\Headers\instruction.h"

//*FUNCIONES VISIBLES Y ESENCIALES PARA LA LECTURA DEL CÓDIGO .ASM.
//*-----------------------------------------------------------------------------------------------

///Función para leer archivo .asm
readASM::ArchvASM* readASM::readArchv(std::string rut){
    std::ifstream a(rut);
    
    if(a.is_open()){
        readASM::ArchvASM* archv = new readASM::ArchvASM();
        std::string line = "", p, label = "";

        ///Contador de intrucciones del archivo .asm
        uint16_t pc = archv->pc_initial;

        ///Contador de líneas de código del archivo .asm
        unsigned int lineCount = 0;
        
        while(getline(a, line)){
            ///Remueve los comentarios de la línea de código.
            removeComments(line);
            
            std::stringstream ss(line);
            
            ///Verifica si la línea está vacía.
            if(!(ss >> p)){
                lineCount++;
                continue;
            }
            
            ///Verifica si es una etiqueta.
            if(p.back() == ':'){
                label = p.substr(0, p.length()-1);
                archv->addLabel(label, pc);
                if(!(ss >> p)){
                    lineCount++;
                    continue;
                }
            }
            
            ///Interpreta la línea de código y crea un struct de tipo Instruction.
            try{
                Instruction*Instruction = readLine(p, ss, pc, lineCount, label);
                
                //Verifica si se produjo un error al interpretar la línea de código.
                if(Instruction == nullptr)
                    return nullptr;
                
                archv->addInstruction(Instruction, pc);
                lineCount++;
                pc++;
            }
            catch(const std::runtime_error &e){
                std::cout << '\n' << e.what() << '\n' << '\n';
                delete archv;
                return nullptr;
            }
            
        }

        a.close();
        return archv;
    }

    return nullptr;
}

///Función para interpretar línea de un archivo .asm.
readASM::Instruction* readASM::readLine(
    std::string nemonic, std::stringstream &args,
    uint16_t pc, 
    unsigned int lineCount, 
    std::string &label
){
    uint8_t op_code = 0;
    readASM::Instruction* instruction;

    if(errors::isDirectiva(nemonic)){
        instruction = new Instruction;
        instruction->isDirective = true;
    }else{
        errors::verifyNemonic(nemonic, lineCount, op_code);
        instruction = new Instruction;
    }

    ///Validar registros correctos.
    instruction->args = splitArgs(args);
    ///Sorporte de nemónicos extra.
    if(nemonic == "MOV") {nemonic = 'ADD'; instruction->args.push_back("R0");}
    if(nemonic == "IMOV"){nemonic = "ADD"; instruction->args.push_back("R0");}
    if(nemonic == "NOP"){
        nemonic = "ADD"; 
        instruction->args.push_back("R0");
        instruction->args.push_back("R0");
        instruction->args.push_back("R0");
    }

    ///Validar si las línea de código son correctas, y si no captura el error.
    try{
       errors::isValidRegister(instruction->args, lineCount);
    }
    catch(const std::runtime_error& e){
        std::cout << '\n' << e.what() << '\n';
        delete instruction;
        return nullptr;
    }

    instruction->direction = pc;
    instruction->label = label;
    instruction->nemonic = nemonic;
    instruction->opCode = op_code;

    return instruction;
}

///Función para dividir los argumentos de las comas.
std::vector<std::string> readASM::splitArgs(std::stringstream &ss){
    std::vector<std::string> args;
    std::string p;

    while(ss >> p){
        if(p.back() == ',')
            p = p.substr(0, p.length()-1);
        args.push_back(p);
    }
    return args;
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
    int sLength = line.length();
    std::string result = "";

    for(int i = 0; i < sLength; i++){
        if(line[i] == ';')
            break;
        result += line[i];
    }

    line = result;
}

//*-----------------------------------------------------------------------------------------------

//*FUNCIONES EXTENDIDAS DE LA CLASE "ArchvASM".
//*-----------------------------------------------------------------------------------------------

/// Función de la clase ArchvASM.
/// Esta función sirve para añadir una nueva instrucción a la línea de código.
void readASM::ArchvASM::addInstruction(Instruction *instruction, uint16_t pc){
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
void readASM::ArchvASM::addLabel(std::string label, uint16_t pc){
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

///Función para ejecutar el programa
void readASM::ArchvASM::executeProgram(){
    Instruction *instruction = firstInstruction;
    int16_t *bankRegister = this->bankRegister;
    uint16_t *pc = &this->pc;
    bool *flag = this->flags;

    while(instruction != nullptr){

        instructionSet::executeInstruction(*instruction, flag, bankRegister, *pc);

        

        instruction = instruction->nextInstruction;
    }
}

///Función para eliminar memoria reservada dinámicamente.
readASM::ArchvASM::~ArchvASM(){
    for(auto a : instructions){
        delete a.second;
    }
}

//*-----------------------------------------------------------------------------------------------