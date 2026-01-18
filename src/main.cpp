#include <iostream>
#include <string>
#include <math.h>
#include "..\include\Headers\readASM.h"

using namespace std;

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

            readASM::ArchvASM* archv = readASM::readArchv(rut);

            if(archv == nullptr)
                continue;

            //Falta por implementar aquí
            //...

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
