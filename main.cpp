#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <vector>
#include <map>
using namespace std;

//*Estructura que contiene una línea de cada instrucción y que además, cada
//*estrutura apunta a la siguiente y a la anterior.
struct Instruction{
    uint16_t direction;
    uint8_t opCode;
    string label;
    string nemonic;
    vector<uint16_t> args;
    char typeRegister;
    int lineCode;
    
    uint16_t machineCode;
    string originalCode;
    bool isDirective = false; 

    //*Variable única para agurmento de tipo instrucción string.
    string value;

    Instruction *nextInstruction = nullptr;
    Instruction *previousInstruction = nullptr;
};

//*FUNCIONES PARA REALIZAR OPERACIONES BINARIAS.
namespace binaryOps {
    //*Función para convertir número con signo a binario.
    int decimalToBinary(int n);

    //*Función para convertir de hexadecimal a decimal con un tamaño de palabra de 16bits
    int16_t hexToDecimal(string hex);
    
    //*Función para poner en minusculas cada caracter de un texto.
    void toLowerText(std::string &instruction);

    //*Función para poner en mayúsculas cada caracter de un text.
    void toUpperText(std::string &instruccion);

    //*Función para convertir un string en un número.
    uint16_t stgToNum(string n);

    //*Función para convertir de hexadecimal a binario.
    string hexTobinary(std::string hex);

    //*Función para truncar un número con un tamaño de palabra w.
    void truncN(int16_t &n, uint16_t w);

    //*Función para sumar dos enteros con signo con un tamaño de 16 bits.
    int16_t sum(int16_t a, int16_t b, bool &overflow);
}

//*IMPLEMENTACIÓN DE FUNCIONES PARA LEER EL ARCHIVO.
//*---------------------------------------------------------------------------------------------------
//*Clase para crear objeto que contendrá todo lo leído en el archivo de manera estructurada.
class ArchvASM {
    private:
        bool flags[4] = {false};
        int16_t bankRegister[8] = {0};
        uint16_t pc = 0;
        uint16_t pcMax = 0;
        
        Instruction *memory[0xffff] = {nullptr};
        std::map<std::string, uint16_t> symbolTable;
        
        
        public:
        Instruction *firstInstruction = nullptr;
        Instruction *lastInstruction = nullptr;
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

        //*Función para verificar si una instrucción existe.
        bool existIntruction(uint16_t direction);

        //*Función para localizar la memoria mediante el .org
        void seLocationPC(uint16_t pc);

        //*Función para verificar si una etiqueta existe.
        bool existsLabel(string label);

        //*Función para obtener la posición de una etiqueta con el nombre de la misma.
        uint16_t getLabel(string label);

        //*Función para ejecutar el programa.
        void executeProgram();

        //*Función para sumar dos enteros.
        void add(Instruction &inst);

        //*Función para restar dos enteros.
        void sub(Instruction &inst);
        
        //*Función para aplicar el operador lógico and a nivel de bits.
        void andd(Instruction &inst);
        
        //*Función para aplicar el operador lógico or a nivel de bits.
        void orr(Instruction &inst);
        
        //*Función para aplicar una operación lógica de comparación y así poder verificar si
        //*un número es igual al otro. Se hace una resta entre dos enteros.
        void cmp(Instruction &inst);

        //*Función para hacer un desplazamiento lógico a nivel de bit hacia la izquierda.
        void lsl(Instruction &inst);
        
        //*Función para hacer un desplazamiento lógico a nivel de bit hacia la derecha.
        void lsr(Instruction &inst);
        
        //*Función para hacer un desplazamiento aritmetico a nivel de bit hacia la derecha conservando el signo.
        void asr(Instruction &inst);

        //*Función para sumar con un inmediato
        void addi(Instruction &inst);
        
        //*
        void subi(Instruction &inst);

        //*
        void andi(Instruction &inst);

        //*
        void ori(Instruction &inst);

        //*
        void lw(Instruction &inst);

        //*
        void sw(Instruction &inst);

        //*Función para hacer un salto hacia una línea mediante el nombre de la etiqueta.
        void jmp(Instruction &inst);

        //*
        void beq(Instruction &inst);

        //*
        void bne(Instruction &inst);

        //*
        void bgt(Instruction &inst);

        //*
        void jal(Instruction &inst);

        //*
        void ret(Instruction &inst);

        //*
        void RETI(Instruction &inst);

        //*
        void HALT(Instruction &inst);

        //*Función para eliminar memoria una vez terminado el programa.
        ~ArchvASM();
};
//*---------------------------------------------------------------------------------------------------

namespace readASM {
//*Función para obtener todas las líneas de código del archivo .asm.
    ArchvASM* readArchv(string rut);

    //*Función para interpretar línea escrita en archivo .asm
    Instruction* readLine(
        string nemonic, 
        stringstream &args, 
        uint16_t pc, 
        unsigned int lineCount, 
        string label,
        ArchvASM &archv
    );

    //*Función para dividir argumentos por coma.
    std::vector<std::string> splitArgs(std::stringstream &ss);

    //*Función MLC (Maching lenguage code) para generar el archivo de salida en lenguaje máquina.
    void MLC(std::string code);

    //*Función para eliminar los comentarios de una línea de un archivo .asm.
    void removeComments(std::string &line);

}

//*FUNCIONES PARA VERIFICAR ERRORES.
//*---------------------------------------------------------------------------------------------------
namespace errors {
    //*Función para verificar si un nemónico de una instrucción existe,
    //*y si no existe lanza una exceptio.
    void verifyNemonic(std::string nemonico, unsigned int lineCount, uint8_t &opCode, char &typeRegister);

    //*Función para verificar si es válida una directiva.
    bool isDirectiva(std::string &directiva);

    //*Función para varificar si los registros de proposito general son correctos.
    //*Si no son correctos se lanzará una exception.
    void isValidArguments(
        string nemonic,
        vector<std::string> &aux,
        vector<uint16_t> &args,
        unsigned int lineCode,
        ArchvASM &archv,
        char typeRegister,
        uint16_t pc,
        uint8_t &bits
    );

    //*Función para verificar si string es un número,
    bool isNum(string num);

    //*Función que verifica si un nemónico es de tipo R (Registro).
    bool isInstructionR(string nemonic, uint8_t &opCode, char &typeRegister);

    //*Función que verifica si un nemónico es de tipo I (inmediato y memoria)
    bool isInstructionI(string nemonic, uint8_t &opCode, char &typeRegister);

    //*Función que verifica si un nemónico es de tipo J (control de flujos y saltos).
    bool isInstructionJ(string nemonic, uint8_t &opCode, char &typeRegister);

    //*Función para verificar que un número inmediato excede un tamaño de palabra establecido w.
    //*Y si excede el tamaño de palabra lanzará una exception.
    void immOverflow(int n, uint16_t w);
}
//*---------------------------------------------------------------------------------------------------

//*FUNCIÓN PRINCIPAL.
int main(){
    int operation = 0;

    while(operation != 3){

        ///Menú para elegir que opción la entrada a elegir.
        cout << "1.Leer archivo .asm" << endl;
        cout << "2.Leer instrucciones linea por linea" << endl;
        cout << "3.Salir" << endl << endl;
        cout << "opcion: "; cin >> operation;

        ///Leerá el archivo .asm mediante la ruta exacta donde esté ubicado.
        if(operation == 1){
            string rut;
            cout << "Ingrese la ruta del archivo: "; cin >> rut;

            ArchvASM* archv = readASM::readArchv(rut);

            if(archv == nullptr)
                continue;

            Instruction *instruction = archv->firstInstruction;
            while(instruction != nullptr){
                cout << instruction->nemonic << " ";
                for(unsigned int i = 0; i < instruction->args.size(); i++){
                    cout << instruction->args[i] << " ";
                }
                cout << "| " << instruction->direction << '\n';
                instruction = instruction->nextInstruction;
            }

            delete archv;
        }

        ///Leerá línea por línea introducida por la terminal
        if(operation == 2){
            string code;
            string line;
            
            //Falta por implementar aquí
            //...
        }
    }
    
    system("pause");
    return 0;
}

//*--------------------------------------------------------------//
//*          IMPLEMENTACIÓN DE TODAS LAS FUNCIONES              //
//*                     /     /                                //
//*                    /     /                                //
//*                   /     /                                //
//*             ------     ------                           //
//*              \           /                             //
//*               \        /                              //
//*                \     /                               //
//*                 \  /                                //
//*                  V                                 //
//*---------------------------------------------------//

//*IMPLEMENTACIÓN DE FUNCIONES DE LA CLASE "ArchvASM".
//*---------------------------------------------------------------------------------------------------

//*Función de la clase ArchvASM.
//*Esta función sirve para añadir una nueva instrucción a la línea de código.
void ArchvASM::addInstruction(Instruction *instruction, uint16_t pc){
    instruction->direction = pc;

    memory[pc] = instruction;

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

//*Función de la clase ArchvASM
//*Está función sirve par aañadir una nueva etiqueta a la tabla de símbolos.
void ArchvASM::addLabel(std::string label, uint16_t pc){
    symbolTable[label] = pc;
}

//*Función de la clase ArchvASM.
//*Esta función sirve para obtener una instrucción con la dirección de memoria de la misma.
Instruction* ArchvASM::jumpToDirection(uint16_t direction){
    return this->memory[(direction - this->pc) - pc_initial];
}

//*Función para verificar si una instrucción existe.
bool ArchvASM::existIntruction(uint16_t direction){
    if(this->memory[direction] != nullptr)
        return true;
    return false;
}

//*Función de la clase ArchvASM.
//*Función para manejar el .org.
void ArchvASM::seLocationPC(uint16_t pc){
    this->pc = pc;
}

//*Función de la clase ArchvASM.
//*Función para verificar si una etiqueta existe.
bool ArchvASM::existsLabel(string label){
    return this->symbolTable.find(label) != this->symbolTable.end();
}

//*Función de la clase ArchvASM.
//*Función para obtener la dirección de una etiqueta.
uint16_t ArchvASM::getLabel(string label){
    return this->symbolTable[label];
}

//*Función de la clase ArchvASM.
//*Función para ejecutar el programa
void ArchvASM::executeProgram(){
    Instruction *instruction = this->memory[pc_initial];
    uint16_t *pc = &this->pc;

    while(instruction != nullptr){

        switch (instruction->opCode){
        //*INSTRUCCIONES DE TIPO R
        //*--------------------------------------------------------------------------
            case 0:
            ArchvASM::add(*instruction);
            break;
        case 1:
            ArchvASM::sub(*instruction);
            break;
        case 2:
            ArchvASM::andd(*instruction);
            break;
        case 3:
            ArchvASM::orr(*instruction);
        case 4:
            ArchvASM::cmp(*instruction);
            break;
        case 5:
            ArchvASM::lsl(*instruction);
            break;
        case 6:
            ArchvASM::lsl(*instruction);
            break;
        case 7:
            ArchvASM::asr(*instruction);
            break;
        //*--------------------------------------------------------------------------

        //*INSTRUCCIONES DE TIPO I
        //*--------------------------------------------------------------------------
        case 8:
            ArchvASM::addi(*instruction);
            break;
        //*--------------------------------------------------------------------------
        default:
            break;
        }

        instruction = instruction->nextInstruction;
    }
}

//*Función de la clase ArchvASM.
//*Función para eliminar memoria reservada dinámicamente.
ArchvASM::~ArchvASM(){
    for(int i = 0; i < 0xffff; i++){
        if(memory[i] != nullptr)
            delete memory[i];
    }
}
//*---------------------------------------------------------------------------------------------------

//*IMPLEMENTACIÓN DE FUNCIONES DE LECTURA DEL ARCHIVO .ASM
//*---------------------------------------------------------------------------------------------------
//*Función para leer archivo .asm
ArchvASM* readASM::readArchv(std::string rut){
    ifstream a(rut);
    
    if(a.is_open()){
        ArchvASM* archv = new ArchvASM();
       string line = "", p, label = "";

        ///Contador de intrucciones del archivo .asm
        uint16_t pc = archv->pc_initial;

        ///Contador de líneas de código del archivo .asm
        unsigned int lineCount = 0;

        ///Hace una primera pasada para encontrar las etiquetas del código.
        while(getline(a, line)){
            ///Remueve los comentarios de la línea de código.
            removeComments(line);
            
            binaryOps::toUpperText(line);
            stringstream ss(line);

            ///Verifica si la línea está vacía.
            if(!(ss >> p))
                continue;

            if(p.back() == ':'){
                archv->addLabel(p.substr(0,p.length()-1), pc);
                if(!(ss >> p))
                    continue;
            }

            pc++;
        } 
        
        a.clear();
        a.seekg(0, std::ios::beg);
        pc = 0;
        ///Hace una segunda pasada para evaluar lo demás.
        while(getline(a, line)){
            ///Remueve los comentarios de la línea de código.
            removeComments(line);
            
            binaryOps::toUpperText(line);
            stringstream ss(line);
            
            ///Verifica si la línea está vacía.
            if(!(ss >> p)){
                lineCount++;
                continue;
            }
            
            ///Verifica si es una etiqueta.
            if(p.back() == ':'){
                label = p.substr(0, p.length()-1);
                if(!(ss >> p)){
                    lineCount++;
                    continue;
                }
            }
            
            ///Interpreta la línea de código y crea un struct de tipo Instruction.
            try{
                Instruction*instruction = readLine(p, ss, pc, lineCount, label, *archv);
                
                //Verifica si se produjo un error al interpretar la línea de código.
                if(instruction == nullptr)
                    return nullptr;
                
                archv->addInstruction(instruction, pc);
                lineCount++;
                if(instruction->nemonic == "STRING"){
                    p += instruction->value.size();
                }
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

//*Función para interpretar línea de un archivo .asm.
Instruction* readASM::readLine(
    string nemonic, 
    stringstream &args,
    uint16_t pc, 
    unsigned int lineCount, 
    string label,
    ArchvASM &archv
){
    uint8_t op_code = 0;
    Instruction* instruction;
    uint8_t bits;
    char typeRegister;

    if(errors::isDirectiva(nemonic)){
        instruction = new Instruction;
        instruction->isDirective = true;
    }else{
        errors::verifyNemonic(nemonic, lineCount, op_code, typeRegister);
        instruction = new Instruction;
    }
    
    vector<string> aux = splitArgs(args);
    ///Sorporte de nemónicos extra.
    if(nemonic == "MOV" || nemonic == "IMOV"){
        aux.push_back("R0");
        aux[0].swap(aux.back());
        nemonic = (nemonic == "MOV") ? "MOV" : "IMOV";
    }else if(nemonic == "NOP"){
        for(int i = 0; i < 3; i++) aux.push_back("R0");
    }else if(nemonic == "CMP"){
        aux.push_back("R0");
        aux[0].swap(aux.back());
    }

    ///Validar si las línea de código son correctas, y si no captura el error.
    try{
        if(nemonic == "STRING"){
            getline(args, instruction->value);
        }
        else if(nemonic != "HALT")
            errors::isValidArguments(
                nemonic,
                aux,
                instruction->args,
                lineCount,
                archv,
                typeRegister,
                pc,
                bits
            );
    }
    catch(const std::runtime_error& e){
        cout << '\n' << e.what() << '\n';
        delete instruction;
        return nullptr;
    }

    instruction->typeRegister = typeRegister;
    instruction->direction = pc;
    instruction->label = label;
    instruction->nemonic = nemonic;
    instruction->opCode = op_code;

    return instruction;
}

//*Función para dividir los argumentos de las comas.
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

//*Función para generar el archivo de salida en lenguaje máquina.
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

//*Función para eliminar comentarios # o ;.
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
//*---------------------------------------------------------------------------------------------------

//*IMPLEMENTACIÓN DE FUNCIONES DE INSTRUCCIONES.
//*---------------------------------------------------------------------------------------------------

//*Función para sumar dos enteros.
void ArchvASM::add(Instruction &inst){
    int32_t result = 0;
    unsigned int rd = inst.args.back();
    int16_t r1 = this->bankRegister[inst.args[0]];
    int16_t r2 = this->bankRegister[inst.args[1]];
    
    
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

    this->bankRegister[rd] = binaryOps::sum(r1, r2, flags[4]);
}

//*Función para restar dos enteros.
void ArchvASM::sub(Instruction &inst){
    int32_t result = 0;
    unsigned int rd = inst.args.back();
    int16_t r1 = this->bankRegister[inst.args[0]];
    int16_t r2 = this->bankRegister[inst.args[1]];
    
    
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

    this->bankRegister[rd] = binaryOps::sum(r1, r2, flags[4]);
}

//*Función para aplicar el and lógico a nivel de bit.
void ArchvASM::andd(Instruction &inst){
    unsigned int rd = inst.args.back();
    int16_t result = this->bankRegister[inst.args[0]] & this->bankRegister[inst.args[1]];

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

//*Función para aplicar el operador or lógico a nivel. 
void ArchvASM::orr(Instruction &inst){
    unsigned int rd = inst.args.back();
    int16_t result = this->bankRegister[inst.args[0]] | this->bankRegister[inst.args[1]];
}

//*Función para comparar
void ArchvASM::cmp(Instruction &inst){
    int32_t result = 0;
    unsigned int rd = inst.args.back();
    int16_t r1 = this->bankRegister[inst.args[0]];
    int16_t r2 = this->bankRegister[inst.args[1]];
    
    
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

//*Función para desplazar logicamente bits hacia la derecha.
void ArchvASM::lsl(Instruction &inst){}
//*Función para desplazar logicamente bits hacia la izquierda.
void ArchvASM::lsr(Instruction &inst){}

//*Función para desplazar aritmeticamente los bits hacia la derecha conservando el signo.
void ArchvASM::asr(Instruction &inst){}

//*Función para sumar con un inmediato
void ArchvASM::addi(Instruction &inst){
    this->bankRegister[inst.args[0]] += inst.args[0] + inst.args[1];
}

void ArchvASM::subi(Instruction &inst){
    this->bankRegister[inst.args[0]] += inst.args[0] + inst.args[1];
}

void ArchvASM::andi(Instruction &inst){}
void ArchvASM::ori(Instruction &inst){}
void ArchvASM::lw(Instruction &inst){}
void ArchvASM::sw(Instruction &inst){}
void ArchvASM::jmp(Instruction &inst){}
void ArchvASM::beq(Instruction &inst){}
void ArchvASM::bne(Instruction &inst){}
void ArchvASM::bgt(Instruction &inst){}
void ArchvASM::jal(Instruction &inst){}
void ArchvASM::ret(Instruction &inst){}
void ArchvASM::RETI(Instruction &inst){}
void ArchvASM::HALT(Instruction &inst){}
//*---------------------------------------------------------------------------------------------------

//*IMPLEMENTACIÓN DE FUNCIONES DE OPERACIONES BINARIAS.
//*---------------------------------------------------------------------------------------------------

//*Función recursiva utilizada por decimalToBinary para convertir número entero
//*sin signo a binario.
static int DTBR(int n){
    if(n <= 0) return 1;
    return DTBR(n / 2) * 10 + n % 10;
}

//*Función para convertir número con signo a binario.
int binaryOps::decimalToBinary(int n){

    return n;
}

//*Función para co
std::string binaryOps::hexTobinary(std::string hex){
    std::string resultado = "";

    // si el usuario puso el "0x" al principio, lo volamos para quedarnos solo con el número.
    if (hex.substr(0, 2) == "0x" || hex.substr(0, 2) == "0X") {
        hex = hex.substr(2);
    }

    // recorremos el string hex y convertimos cada letra/número en sus 4 bits correspondientes.
    for (int i = 0; i < hex.length(); i++) {
        char c = toupper(hex[i]); // Lo ponemos en mayúscula para no tener problemas con 'a' o 'A'.
        switch (c) {
        case '0': resultado += "0000"; break;
        case '1': resultado += "0001"; break;
        case '2': resultado += "0010"; break;
        case '3': resultado += "0011"; break;
        case '4': resultado += "0100"; break;
        case '5': resultado += "0101"; break;
        case '6': resultado += "0110"; break;
        case '7': resultado += "0111"; break;
        case '8': resultado += "1000"; break;
        case '9': resultado += "1001"; break;
        case 'A': resultado += "1010"; break;
        case 'B': resultado += "1011"; break;
        case 'C': resultado += "1100"; break;
        case 'D': resultado += "1101"; break;
        case 'E': resultado += "1110"; break;
        case 'F': resultado += "1111"; break;
        }
    }

    // el proyecto dice que el ancho de palabra es de 16 bits, así que rellenamos con ceros. 
    while (resultado.length() < 16) resultado = "0" + resultado;

    return resultado;
}

//*Función para truncar un número con un tamaño de palabra w
void binaryOps::truncN(int16_t &n, uint16_t w){
    n = ((1 << w) - 1) & n;
}

int16_t binaryOps::sum(int16_t a, int16_t b, bool &overflow){
    int16_t result = a + b;

    if((a < 0 && b < 0) && result > 0)
        overflow = true;
    else if((a > 0 && b > 0) && result < 0)
        overflow = true;
    else
        overflow = false;
        
    return result;
}

//*Función para convertir de hexadecimal a decimal con un tamaño de palabra de.
int16_t binaryOps::hexToDecimal(string hex){
    toUpperText(hex);
    if(hex.size() >= 2 && hex[0] == '0' && hex[1] == 'X')
        hex = hex.substr(2);
    if(hex.empty()) return 0;

    int16_t result = 0;
    int changeSig = ((hex[0] == '8' || hex[0] == '9') || (hex[0] >= 'A' && hex[0] <= 'F'))
                        ? -1
                        : 1;

    unsigned int i = hex.length() - 1;
    for(char c : hex){
        int16_t digit;
        if(c >= '0' && c <= '9') digit = changeSig * (c - '0');
        else if(c >= 'A' && c <= 'F') digit = changeSig * (10 +  (c - 'A'));
        else return 0;
        result = result + (digit * pow(16,i));
        if(changeSig != 1) changeSig = 1;
        i--;
    }

    return result;
}

//*Función para convertir un string a un número.
uint16_t binaryOps::stgToNum(string n){
    uint16_t result = 0;

    for(unsigned int i = 0; i < n.length(); i++){
        result = (result * 10) + (n[i] - '0');
    }
    return result;
}

//*Función para poner en minusculas cada caracter de un texto.
void binaryOps::toLowerText(std::string &instruction){
    int lengthInstruction = instruction.length();
    for(int i = 0; i < lengthInstruction; i++){
        instruction[i] = instruction[i] | 32;
    }
}

//*Función para poner en mayúsculas cada caracter de un text.
void binaryOps::toUpperText(std::string &instruction){
    int lengthInstruction = instruction.length();
    for(unsigned int i = 0; i < lengthInstruction; i++){
        if(instruction[i] >= 'a' && instruction[i] <= 'z'){
            instruction[i] = instruction[i] ^ 32;
        }
    }
}
//*---------------------------------------------------------------------------------------------------

//*IMPLEMENTACÓN DE FUNCIONES PARA VERIFICAR ERRORES.
//*---------------------------------------------------------------------------------------------------

//*Función para verificar errores en el nemónico de la instrucción.
void errors::verifyNemonic(std::string nemonico, unsigned int lineCount, uint8_t &opCode, char &typeRegister){
    if(isInstructionR(nemonico, opCode, typeRegister) || 
        isInstructionI(nemonico, opCode, typeRegister) || 
        isInstructionJ(nemonico, opCode, typeRegister)
        ){
            return;
        }
    
    throw std::runtime_error("Instruccion desconocida en la linea: " + std::to_string(lineCount) + ".");
}

//*Función para verificar si es una directiva.
bool errors::isDirectiva(std::string &directiva){
    std::string directivas[4] = {".ORG", ".WORD", ".SPACE", ".STRING"};
    for(int i = 0; i < 4; i++){
        if(directiva == directivas[i]){
            directiva = directiva.substr(1, directiva.length());
            return true;
        }
    }
    return false;
}

//*Función que verifica si una instrucción es de tipo R (Registro).
void errors::isValidArguments(
    string nemonic,
    vector<std::string> & aux,
    vector<uint16_t> &args,
    unsigned int lineCode,
    ArchvASM &archv,
    char typeRegister,
    uint16_t pc,
    uint8_t &bits
){
    unsigned int length = aux.size();
    string msg = "Registro no valido.";

    for(unsigned int i = 0; i < length; i++){
        uint8_t w = 7;
        ///Verifica si los argumentos son registros.
        if(aux[i][0] == 'R')
            if(aux[i][1] >= '0' && aux[i][1] <= '7'){
                args.push_back(aux[i][1] - '0');
                bits+= 3;
                continue;
            }


        if(typeRegister == 'R' && (nemonic != "LSL" && nemonic != "LSR" && nemonic != "ASR")){
            continue;
        }else if(typeRegister == 'R'){
            w = 3;
        }
        
        
        ///Verifica si el inmediato es una dirección a una instrucción.
        if(aux[i] == "0X"){
            uint16_t num_or_drr = binaryOps::hexToDecimal(aux[i]);

            ///Verifica si el inmediato es mayor a 7bits.
            errors::immOverflow(num_or_drr, w);
            
            if((typeRegister == 'R' || typeRegister == 'I') && (nemonic != "LW" && nemonic != "SW")){
                args.push_back(num_or_drr);
                bits += w;
                continue;
            } else {
                args.push_back(num_or_drr - pc);
                bits += w;
                continue;
            }
        }
        
        ///Verifica si el inmediato es un número.
        if(typeRegister != 'J' && (nemonic != "LW" && nemonic != "SW") && errors::isNum(aux[i])){
            uint16_t num = binaryOps::stgToNum(aux[i]);
            
            ///Verifica si el inmediato es mayor a 7bits.
            errors::immOverflow(num, 7);

            args.push_back(num);
        }
        
        ///Vefica si el argumento es una etiqueta.
        if(archv.existsLabel(aux[i])){
            uint16_t direction = archv.getLabel(aux[i]) - pc;
            bits += w;
            args.push_back(direction);
            continue;
        }
        
        throw runtime_error("Error en la linea " + to_string(lineCode) + ": " + msg + '\n');
    }

    if(bits > 16) 
        throw runtime_error(
            "Ha excedido el ancho de palabra de una instruccion en la linea: " + to_string(lineCode) + '\n'
        );
    if(bits < 16) 
        throw runtime_error(
            "Ha ocurrido un error en la implementacion de la instruccion en la linea: " + to_string(lineCode) + '\n'
        );
}

//*Función para verificar si un string es un número.
bool errors::isNum(string num){
    for(unsigned int i = 0; i < num.length(); i++){
        if(!(num[i] >= '0' && num[i] <= '9'))
            return false;
    }
    return true;
}

bool errors::isInstructionR(std::string nemonic, uint8_t &opCode, char &typeRegister){

    std::string iR[8] = {"ADD", "SUB", "AND", "ORR", "CMP", "LSL", "LSR", "ASR"};

    ///Verifica nemónicos incorporados.
    if(nemonic == "MOV" || nemonic == "IMOV" || nemonic == "NOP"){
        typeRegister = 'R';
        opCode = 0;
        return true;
    }

    for(int i = 0; i < 8; i++){
        if(nemonic == iR[i]){
            typeRegister = 'R';
            opCode = i;
            return true;
        }
    }
    return false;
}

//*Función que verifica si una instrucción es de tipo I (inmediato y memoria)
bool errors::isInstructionI(std::string nemonic, uint8_t &opCode, char &typeRegister){
    std::string iI[6] = {"ADDI", "SUBI", "ANDI", "ORI", "LW", "SW"};
    for(int i = 0; i < 6; i++){
        if(iI[i] == nemonic){
            typeRegister = 'I';
            opCode = i + 8;
            return true;
        }
    }
    return false;
}

//*Función que verifica si una instrucción es de tipo J (control de flujos y saltos).
bool errors::isInstructionJ(std::string nemonic, uint8_t &opCode, char &typeRegister){
    std::string iJ[8] = {"JMP", "BEQ", "BNE", "BGT", "JAL", "RET", "RETI", "HALT"};
    for(int i = 0; i < 8; i++){
        if(iJ[i] == nemonic){
            typeRegister = 'J';
            opCode = i + 6;
            return true;
        }
    }
    return false;
}

//*Función para verificar que un número excede un tamaño de palabra establecido w.
void errors::immOverflow(int n, uint16_t w){
    if(n < -pow(2, w-1) || n > pow(2,w-1)-1)
        throw runtime_error("El valor inmediato excede los 7 bits permitidos.");
}

//*---------------------------------------------------------------------------------------------------