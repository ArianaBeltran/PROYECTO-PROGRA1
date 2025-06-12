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
    int telf=0;
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


void registroCopropietario(string archivoCop){
    ofstream registroCop;
    copropietario sumarcop;
    registroCop.open(archivoCop, ios::binary | ios::app);
    if (registroCop.fail()){
        cout << "nel pastel ";
    } else{
        cout << "ingrese el nombre del copropietario"<<endl;
        cin.getline(sumarcop.nombrecop,30);
        cout << "ingrese el apellido del copropietario"<<endl;
        cin.getline(sumarcop.apellidocop,30);
        cout << "ingrese el telefono del copropietario"<<endl;
        cin>>sumarcop.telf;
        cin.ignore();
        cout << "ingrese el depto en el que vive el copropietario"<<endl;
        cin.getline(sumarcop.Nrodepto,9);
        cout << "ingrese la superficie del departamento a registrar"<<endl;
        cin>>sumarcop.totalSuperficie;
        registroCop.write((char*)&sumarcop, sizeof(copropietario));
    }
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
                cout << "ingrese un nuevo telefono "<<endl;
                cin >> modificarCop.telf;
                cin.ignore();
                int op;
                cout << "desea cambiar el nombre y apellido de la persona? (1) si 2(no)"<<endl;
                cin >> op;
                cin.ignore();
                if (op == 1) //veremos si funciona 
                {
                    cout << "ingrese un nuevo nombre "<<endl;
                    cin.getline(modificarCop.nombrecop,30);
                    cout << "ingrese un nuevo apellido "<<endl;
                    cin.getline(modificarCop.apellidocop,30);
                }
                else if (op!=1){
                    return;
                }
            }            
        }
    }
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
        cout << "\t1. Registrar gastos mensuales del edficio" << endl;
        cout << "\t2. Registrar (o modificar) copropietario" << endl;
        cout << "\t3. Mostrar copropietarios" << endl;
        cout << "\t4. Mostrar gastos realizados " << endl;
        
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
                cout << "\tpara registrar un copropietario escriba 1 "<<endl;
                cout << "\tpara eliminar un copropietario escriba 2 "<<endl;
                cout << "\tpara modificar un copropietario escriba 3 "<<endl;
                int opCop;
                cin>>opCop;
                cin.ignore();
                if (opCop == 1)
                {
                    registroCopropietario(archivoCop);
                    
                } else if (opCop ==2){
                    cout << "ingrese el numero de depto del copropietario a eliminar "<<endl;
                    char banderaDepto[9];
                    cin.getline(banderaDepto,9);
                    eliminarCop(archivoCop,banderaDepto);
                } else if (opCop ==3 ){
                    cout << "ingrese el numero de depto del copropietario a modificar "<<endl;
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