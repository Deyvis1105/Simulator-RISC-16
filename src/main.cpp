#include <iostream>
#include <string>
#include <math.h>
#include "..\include\Headers\readASM.h"

using namespace std;

int main(){
    int operation = 0;

    while(operation != 3){

        ///Menú para elegir que opción la entrada a elegir.
        cout << "1.Leer un archivo .asm" << endl;
        cout << "2.Leer instrucciones linea por linea" << endl;
        cout << "3.Salir" << endl << endl;
        cout << "opcion: "; cin >> operation;

        ///Leerá el archivo .asm mediante la ruta exacta donde esté ubicado.
        if(operation == 1){
            string rut;
            cout << "Ingrese la ruta del archivo: "; cin >> rut;

            ///Lee el archivo
            readASM::readArchv(rut);
        }

        ///Leerá línea por línea introducida por la terminal
        if(operation == 2){
            string code;
            string line;
            
            cout << "Escriba el codigo." << endl;

            while(true){
                getline(cin, line);
                binaryOps::toUpperText(line);
                
                if(line == "exit")
                    break;

                code += line;
                code.push_back('\n');
            }
            
            cout << endl;
            readASM::MLC(code);
        }
    }
    
    return 0;
}
