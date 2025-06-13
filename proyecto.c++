#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;
//esta es una sesion de prueba 
//apocositilin 
//
struct gastosMensuales{
    char periodo[9]="";
    double gastosGenerales=0.0;
    double gastosalarios=0.0;
    double totalGastos=0.0;
};

struct copropietario{
    char Nrodepto[5]="";
    char nombrecop[30]="";
    char apellidocop[30]="";
    char telf[9];
    double totalSuperficie=0.0;
};

struct generacionExpensas{
    char Nrodepto[5]="";
    char nombrecop[30]="";
    double montoExpensa=0.0;
};

void gastosMantenimiento(string archivogastosmensuales){
    ofstream archivoGM;
    gastosMensuales anadirGM;
    archivoGM.open(archivogastosmensuales, ios::binary | ios::app);
    if (archivoGM.fail()){
        cout << "nel pastel ";
    } else{
        cout << "ingrese el periodo actual"<<endl;
        cin.getline(anadirGM.periodo,9);
        cout << "ingrese el los gastos del edificio durante el mes"<<endl;
        cin>>anadirGM.gastosGenerales;
        
        cout << "ingrese los salarios a pagar "<<endl;
        cin>>anadirGM.gastosalarios;
        double total = anadirGM.gastosalarios + anadirGM.gastosGenerales;
        anadirGM.totalGastos=total;
        archivoGM.write((char*)&anadirGM, sizeof(gastosMensuales));
    }
}

bool soloLetras(char * texto){
    for (int i = 0; texto[i]; i++)
    {
        if (!isalpha(texto[i])){ // si el caracter recorrido del texto es diferente a una letra retorna falso
            return false;
        }
    }
    return true;
}

bool soloNumeros(char * texto, int longitud){
    int largoTexto =strlen(texto); // para sacar la longitud de un char
    bool esValido = true;
    for (int i = 0; i < largoTexto; i++)
    {
        if (!isdigit(texto[i])){
            esValido= false;
            break;
        }
    }
    return esValido;
}

bool letraYnumero (char* texto){
    bool hayLetra = false;
    bool hayNumero =false;
    for (int i = 0; texto[i]; i++)
    {
        if (isalpha(texto[i])){
            hayLetra = true;
        }
        if (isdigit(texto[i])){
            hayNumero = true;
        }
    }
    return hayLetra && hayNumero;
}
void registroCopropietario(string archivoCop){
    ofstream registroCop;
    copropietario sumarcop;
    registroCop.open(archivoCop, ios::binary | ios::app);
    if (registroCop.fail()){
        cout << "nel pastel ";
        return;
    } 
    do //nombre
    {
        cout << "ingrese el nombre del copropietario"<<endl;
        cin.getline(sumarcop.nombrecop,30);
        if(!soloLetras(sumarcop.nombrecop)){
            cout<<"NOMBRE INVALIDO. (solo se permite letras)"<<endl;
        }
    } while (!soloLetras(sumarcop.nombrecop));

    do //apellido
    {
        cout << "ingrese el apellido del copropietario"<<endl;
        cin.getline(sumarcop.apellidocop,30);
        if(!soloLetras(sumarcop.apellidocop)){
            cout<<"APELLIDO INVALIDO. (solo se permite letras)"<<endl;
        }
    } while (!soloLetras(sumarcop.apellidocop));

    do //telefono
    {
        cout << "ingrese el telefono del copropietario"<<endl;
        cin.getline(sumarcop.telf,9);
        if(!soloNumeros(sumarcop.telf,9)){
            cout<<"TELEFONO INVALIDO. (8 digitos)"<<endl;;
        }
    } while (!soloNumeros(sumarcop.telf, 9));
    
    do //departamento
    {
        cout << "ingrese el depto en el que vive el copropietario"<<endl;
        cin.getline(sumarcop.Nrodepto,9);
        if(!letraYnumero(sumarcop.Nrodepto)){
            cout<<"NUMERO DE DEPARTAMENTO INVALIDO. (debe contener al menos una letra y un numero)"<<endl;
        }
    } while (!letraYnumero(sumarcop.Nrodepto));
    
    do
    {
        cout << "ingrese la superficie del departamento a registrar"<<endl;
        cin>>sumarcop.totalSuperficie; 
        cin.ignore();
        if(sumarcop.totalSuperficie < 0){
            cout<<"SUPERFICIE INVALIDA. (debe ser un numero positivo)"<<endl;
        }
    } while (sumarcop.totalSuperficie < 0);
    registroCop.write((char*)&sumarcop, sizeof(copropietario));
    registroCop.close();
}

void eliminarCop(string archivoCop, char banderaDepto[9]) {
    fstream delCop;
    copropietario elcop;
    delCop.open(archivoCop, ios::binary | ios::in);
    if (delCop.fail()) {
        cout << "nel pastel\n";
        return;
    }
    ofstream archivoTemp("ArchivoTemporal.BIN", ios::binary);
    if (archivoTemp.fail()) {
        cout << "Error al crear archivo temporal\n";
        delCop.close();
        return;
    }

    while (delCop.read((char*)&elcop, sizeof(copropietario))) {
        if (strcmp(banderaDepto, elcop.Nrodepto) != 0) {
            archivoTemp.write((char*)&elcop, sizeof(copropietario));
        }
    }
    delCop.close();
    archivoTemp.close();
    remove(archivoCop.c_str());
    rename("ArchivoTemporal.BIN", archivoCop.c_str());
}

void modificarCop(string archivoCop, char banderaDepto [9]){
    fstream modCop;
    copropietario modificarCop;
    int opcion=0;
    modCop.open(archivoCop, ios::binary | ios::in|ios::out);
    if (modCop.fail()){
        cout << "nel pastel";
    } else {
        while (modCop.read((char*)&modificarCop, sizeof(copropietario))) {
            if (strcmp(banderaDepto, modificarCop.Nrodepto)==0)
            {
                cout << "Persona encontrada " << endl;
                cout << "La persona del depto " << modificarCop.Nrodepto <<endl;
                cout << "de nombre " << modificarCop.nombrecop << " y apellido " << modificarCop.apellidocop <<endl;
                cout << "de telefono "<< modificarCop.telf <<endl;
                cout << "tiene una extension de " << modificarCop.totalSuperficie<<endl;
                cout << "------------------------" <<endl;
                do
                {
                    cout<<"Ingrese un nuevo telfono"<<endl;
                    cin.getline(modificarCop.telf, 9);
                    if(!soloNumeros(modificarCop.telf,9)){
                        cout<<"TELEFONO INVALIDO. (debe contener 8 digitos)"<<endl;
                    }
                } while (!soloNumeros(modificarCop.telf,8));

                cout << "desea cambiar el nombre y apellido de la persona?   1.si   2.no"<<endl;
                cin >> opcion;
                cin.ignore();
                if (opcion == 1) //veremos si funciona 
                {
                    do //nombre
                    {
                        cout<<"Ingrese el nuevo nombre"<<endl;
                        cin.getline(modificarCop.nombrecop,30);
                        if(!soloLetras(modificarCop.nombrecop)){
                            cout<<"NOMBRE INVALIDO. (ingrese solo letras)"<<endl;
                        }
                    } while (!soloLetras(modificarCop.nombrecop));
                    
                    do //apellido
                    {
                        cout<<"Ingrese el nuevo apellido"<<endl;
                        cin.getline(modificarCop.apellidocop,30);
                        if(!soloLetras(modificarCop.apellidocop)){
                            cout<<"APELLIDO INVALIDO. (ingrese solo letras)"<<endl;
                        }
                    } while (!soloLetras(modificarCop.apellidocop));
                    

                }
                else if (opcion!=1){
                    return;
                }
                //cambios guardados
                modCop.seekp(-sizeof(copropietario), ios::cur);
                modCop.write((char*)&modificarCop, sizeof(copropietario));
                cout << "Registro modificado exitosamente." << endl;
                break;
            }          
        }
    }
    modCop.close();
}

void mostrarArchivoCop(string archivoCop){
    ifstream mcops;
    copropietario mostrarcop;
    mcops.open (archivoCop, ios::binary);
    if(mcops.fail()){
        cout << "nel pastel ";
    } else {
        while (mcops.read((char*)&mostrarcop, sizeof (copropietario)));
        cout << "El nombre del copropietario es "<< mostrarcop.nombrecop <<endl;
        cout << "El apellido del copropietario es "<< mostrarcop.apellidocop <<endl;
        cout << "El numero de depto es "<<mostrarcop.Nrodepto <<endl;
        cout << "su superficie es de " << mostrarcop.totalSuperficie <<endl;
    }
    cout << endl;
    mcops.close();
}

void mostrarArchivoGM(string archivoMensual){
    ifstream mGastos;
    gastosMensuales mostrarGM;
    mGastos.open (archivoMensual, ios::binary);
    if(mGastos.fail()){
        cout << "nel pastel ";
    } else {
        while (mGastos.read((char*)&mostrarGM, sizeof (gastosMensuales)));
        cout << mostrarGM.gastosGenerales <<endl;
        cout << mostrarGM.gastosalarios <<endl;
        cout << mostrarGM.periodo <<endl;
        cout << mostrarGM.totalGastos<<endl;
    }
    cout << endl;
    mGastos.close();
}

void ReporteGeneralPeriodo(string nombreArchivoPeriodo){
        
    
}




void menuOpciones (string archivoCop, string archivoGastosmensuales){
    int opcion;
    do
    {
        system("cls");
        cout << "MENU DE OPCIONES" << endl;
        cout << "================" << endl;
        cout << "\t1. Registrar gastos mensuales del edficio." << endl;
        cout << "\t2. Registrar (o modificar) copropietario." << endl;
        cout << "\t3. Mostrar copropietarios." << endl;
        cout << "\t4. Mostrar gastos realizados. " << endl;
        cout << "\t0. SALIR" << endl;

        cout << "\n\tIngrese la opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
            case 0:
                system("cls");
                break;
            case 1:
                system("cls");
                gastosMantenimiento(archivoGastosmensuales);
                system("pause");

                break;  
            case 2:
                system("cls");
                cout<<"\t\tCO-PROPIETARIO"<<endl;
                cout<<"\tOPCIONES"<<endl;
                cout<<"\t========"<<endl;
                cout << "\t1. Registrar un copropietario. "<<endl;
                cout << "\t2. Eliminar un copropietario. "<<endl;
                cout << "\t3. Modificar un copropietario."<<endl;
                int opCop;
                cin>>opCop;
                cin.ignore();
                if (opCop == 1)
                {
                    registroCopropietario(archivoCop);
                    
                } else if (opCop ==2){
                    cout << "Ingrese el numero de depto del copropietario a eliminar "<<endl;
                    char banderaDepto[9];
                    cin.getline(banderaDepto,9);
                    eliminarCop(archivoCop,banderaDepto);
                } else if (opCop ==3 ){
                    cout << "Ingrese el numero de depto del copropietario a modificar "<<endl;
                    char banderaDepto[9];
                    cin.getline(banderaDepto,9);
                    modificarCop(archivoCop,banderaDepto);
                }
                system("pause");
                break;
            case 3:
                system("cls");
                mostrarArchivoCop(archivoCop);
                system("pause");
                break;
            case 4:
                system("cls");
                mostrarArchivoGM(archivoGastosmensuales);
                system("pause");
                break;

            default:
                cout << "No existe la opcion ingresada." << endl;
                break;
        }
    } while (opcion != 0);
}

int main(){
    string arGastosMantenimiento="GastosDeMantenimiento.BIN";
    string arRegistroCop="RegistroDeCopropietario.BIN";
    menuOpciones(arGastosMantenimiento,arRegistroCop);
    
    return 0;
}