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
    char carnet[9];
};

struct generacionExpensas{
    char Nrodepto[5]="";
    char nombrecop[30]="";
    double montoExpensa=0.0;
};

bool existeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    return archivo.good();
}

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

bool soloNumeros(char* texto, int longitud) {
    for (int i = 0; i < longitud; i++) {
        if (texto[i] == '\0' || !isdigit(texto[i])) {
            return false;
        }
    }

    return texto[longitud] == '\0'; // Verifica que no haya más caracteres luego de los 8 (o en longitud)
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
        cout << "No se pudo abrir el archivo para registro." << endl;
        return;
    }

    do // nombre
    {
        cout << "Ingrese el nombre del copropietario" << endl;
        cin.getline(sumarcop.nombrecop, 30);
        if (!soloLetras(sumarcop.nombrecop)) {
            cout << "NOMBRE INVALIDO. (solo se permite letras)" << endl;
        }
    } while (!soloLetras(sumarcop.nombrecop));

    do // apellido
    {
        cout << "Ingrese el apellido del copropietario" << endl;
        cin.getline(sumarcop.apellidocop, 30);
        if (!soloLetras(sumarcop.apellidocop)) {
            cout << "APELLIDO INVALIDO. (solo se permite letras)" << endl;
        }
    } while (!soloLetras(sumarcop.apellidocop));

    do // teléfono
    {
        cout << "Ingrese el telefono del copropietario" << endl;
        cin.getline(sumarcop.telf, 9); // 8 + 1 para '\0'
        
        if (!soloNumeros(sumarcop.telf, 8)) {
            cout << "TELEFONO INVALIDO. (8 dígitos)" << endl;
        }
    } while (!soloNumeros(sumarcop.telf, 8));

    do // departamento
    {
        cout << "Ingrese el depto en el que vive el copropietario" << endl;
        cin.getline(sumarcop.Nrodepto, 9);
        if (!letraYnumero(sumarcop.Nrodepto)) {
            cout << "NUMERO DE DEPARTAMENTO INVALIDO. (debe contener al menos una letra y un numero)" << endl;
        }
    } while (!letraYnumero(sumarcop.Nrodepto));
    do
    {
        cout<<"Ingrese el carnet del copropietario"<<endl;
        cin.getline(sumarcop.carnet ,9);

        if (!soloNumeros(sumarcop.carnet , 8)){
            cout<<"CARNET INVALIDO. (8 digitos)"<<endl;
        }
        
    } while (!soloNumeros(sumarcop.carnet,8));
    
    while (true) {
        cout << "Ingrese la superficie del departamento a registrar" << endl;
        if (cin >> sumarcop.totalSuperficie && sumarcop.totalSuperficie >= 0) {
            cin.ignore();
            break;
        } else {
            cout << "SUPERFICIE INVALIDA. (debe ser un numero positivo)" << endl;
            cin.clear(); // limpia los errores ingresados
            cin.ignore(1000, '\n'); // elimina lo qeu queda en el buffer hasta el salto de linea o 1000 caracteres
        }
    }

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
/*------------------------------------------------------------------------------------------*/
void generarComprobanteCopropietario(string archivoCop) {
    double precioPorM2 = 2.5; //le ponen precioo
    ifstream archivo(archivoCop, ios::binary);
    copropietario cop;

    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo de copropietarios." << endl;
        return;
    }

    while (archivo.read((char*)&cop, sizeof(copropietario))) {
        string nombreArchivo =string("Comprobante_") + cop.Nrodepto + ".txt"; //Comprobante_cop.Nrodepto.txt
        ofstream comprobante(nombreArchivo);

        if (comprobante.fail()) {
        cout << "No se pudo crear el archivo de comprobante para el depto " << cop.Nrodepto << endl;
        } else {
            double montoTotal = cop.totalSuperficie * precioPorM2;

            comprobante << "===============================" << endl;
            comprobante << "      COMPROBANTE DE PAGO      " << endl;
            comprobante << "===============================" << endl;
            comprobante << "Nombre: " << cop.nombrecop << " " << cop.apellidocop << endl;
            comprobante << "Telefono: " << cop.telf << endl;
            comprobante << "Departamento: " << cop.Nrodepto << endl;
            comprobante << "Superficie: " << cop.totalSuperficie << " m2" << endl;
            comprobante << "Precio por m2: " << precioPorM2 << " Bs" << endl;
            comprobante << "-------------------------------" << endl;
            comprobante << "TOTAL A PAGAR: " << montoTotal << " Bs" << endl;
            comprobante << "===============================" << endl;
            comprobante << "Gracias por su pago puntual." << endl;

            comprobante.close();
        }
    archivo.close();
    cout << "Comprobantes generados correctamente." << endl;
    }
}

void mostrarComprobantePersonal(string archivoCop) {
    ifstream archivo(archivoCop, ios::binary);
    copropietario cop;
    char nombre[30], apellido[30], carnet[10];
    bool encontrado = false;

    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo de copropietarios." << endl;
        return;
    }

    cout << "Ingrese el nombre: ";
    cin.getline(nombre, 30);
    cout << "Ingrese el apellido: ";
    cin.getline(apellido, 30);

    while (archivo.read((char*)&cop, sizeof(copropietario))) {

        if (strcmp(nombre, cop.nombrecop) == 0 && strcmp(apellido, cop.apellidocop) == 0) {//check nombre y apell

            cout << "Ingrese el carnet: ";
            cin.getline(carnet, 10);

            if (strcmp(carnet, cop.carnet) == 0) {
                double precioPorM2 = 20.0;
                double montoTotal = cop.totalSuperficie * precioPorM2;

                cout << "\n===============================" << endl;
                cout << "      COMPROBANTE DE PAGO      " << endl;
                cout << "===============================" << endl;
                cout << "Nombre: " << cop.nombrecop << " " << cop.apellidocop << endl;
                cout << "Telefono: " << cop.telf << endl;
                cout << "Departamento: " << cop.Nrodepto << endl;
                cout << "Superficie: " << cop.totalSuperficie << " m2" << endl;
                cout << "Precio por m2: " << precioPorM2 << " Bs" << endl;
                cout << "-------------------------------" << endl;
                cout << "TOTAL A PAGAR: " << montoTotal << " Bs" << endl;
                cout << "===============================" << endl;
                cout << "Gracias por su pago puntual." << endl;

                encontrado = true;
                break;
            } else {
                cout << "Carnet incorrecto." << endl;
                encontrado = true;
                break;
            }
        }
    }

    if (!encontrado) {
        cout << "Copropietario no encontrado." << endl;
    }

    archivo.close();
}

void listarCopropietarios(const string& archivoCop) {
    ifstream archivo(archivoCop, ios::binary);
    if (!archivo) {
        cout << "No se pudo abrir el archivo de copropietarios." << endl;
        return;
    }
    copropietario cop;
    cout << "Lista de copropietarios:\n";
    while (archivo.read((char*)&cop, sizeof(copropietario))) {
        cout << "Nombre: " << cop.nombrecop << " " << cop.apellidocop
             << ", Carnet: " << cop.carnet
             << ", Telefono: " << cop.telf
             << ", Depto: " << cop.Nrodepto
             << ", Superficie: " << cop.totalSuperficie << " m2\n";
    }
    archivo.close();
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
        cout << "\t5. Generar comprobantes de copropietarios" << endl;
        cout << "\t6. Listar copropietarios" << endl;
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
            case 5:
                system("cls");
                generarComprobanteCopropietario(archivoCop);
                system("pause");
                break;
            case 6:
                system("cls");
                listarCopropietarios(archivoCop);
                system("pause");
            default:
                cout << "No existe la opcion ingresada." << endl;
                break;
        }
    } while (opcion != 0);
}

void MenuOpcionesCopropietario(string archivoCop, string archivoGastosmensuales){
    int opcion=0;
    cout<<"MENU DE OPCIONES PARA EL COPROPIETARIO"<<endl;
    cout<<"\t1. Mostrar Comprobante Personal"<<endl;
    cout<<"\t0. Volver al menu principal"<<endl;
    cout<<"Ingrese una opcion: ";
    cin >> opcion;
    cin.ignore(); 

    switch (opcion)
    {
    case 1:
        system("cls");
        mostrarComprobantePersonal(archivoCop);
        system("pause");
        break;
    case 0:
        return;
    default:
        cout << "Opción no válida." << endl;
        break;
    }
}

void crearArchivoPrueba(const std::string& nombreArchivo) { // aqui hice la prueba por eso creo que no llena
    copropietario cop;                                      //el archivo binario llora*
    strcpy(cop.nombrecop, "Juan");
    strcpy(cop.apellidocop, "Perez");
    strcpy(cop.carnet, "12345678");
    strcpy(cop.telf, "76543210");
    strcpy(cop.Nrodepto, "101");
    cop.totalSuperficie = 50.5;

    std::ofstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo) {
        std::cout << "No se pudo crear el archivo." << std::endl;
        return;
    }
    archivo.write((char*)&cop, sizeof(copropietario));
    archivo.close();
    std::cout << "Archivo de prueba creado con éxito." << std::endl;
}

int main(){
    int opcion=0;
    string arRegistroCop = "RegistroDeCopropietario.BIN";
    string arGastosMantenimiento = "GastosDeMantenimiento.BIN";
    if (!existeArchivo(arRegistroCop)) {
        cout << "Archivo de copropietarios no existe, creando archivo de prueba..." << endl;
        crearArchivoPrueba(arRegistroCop);
    }
    do {
        system("cls");
        cout<<"\tBIENVENIDO AL REGISTRO DE EXPENSAS DEL EDIFICIO MONTERREY" << endl;
        cout<<"===========================================================" << endl;
        cout<<"1. Administrador del edificio" << endl;
        cout<< "2. Copropietario" << endl;
        cout<<"0. Salir" << endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
            menuOpciones(arGastosMantenimiento, arRegistroCop);
            break;
        case 2:
            MenuOpcionesCopropietario(arRegistroCop, arGastosMantenimiento);
            break;
        case 0:
            cout << "Gracias por usar el sistema." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            system("pause");
            break;
        }
    } while (opcion != 0);

    return 0;
}

