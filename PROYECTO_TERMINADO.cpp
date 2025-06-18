//PROYECTO CHRIS,ARI Y ANAHI.
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

//ESTRUCTURAS

struct gastosMensuales{
    int  mes ;
    char motivo [30]= "";
    double gastosGenerales=0.0;
    double gastosalarios=0.0;
    double totalGasto[12] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
};

struct copropietario{
    char Nrodepto[9]="";
    char nombrecop[30]="";
    char apellidocop[30]="";
    char telf[9];
    char carnet[9];
    double totalSuperficie=0.0;
    int pagoExpensas[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
};

struct generacionExpensas{
    char Nrodepto[5]="";
    char nombrecop[30]="";
    double montoExpensa=0.0;
};

// FUNCIONES

void gastosMantenimiento(string archivogastosmensuales){ //codigo anahi
    ofstream archivoGM;
    gastosMensuales anadirGM;
    int mes;
    archivoGM.open(archivogastosmensuales, ios::binary | ios::app);
    if (archivoGM.fail()){
        cout << "nel pastel ";
    } else 
    {
        cout << " Ingrese el mes del registro || ejemplo :   0 = Enero, 1 = Febrero , 2 = Marzo , etc ......" << endl;
        cin >> anadirGM.mes ;
        cin.ignore();
        cout << "ingrese el motivo del egreso del mes :\n  Ejemplo : ' Compra de implementos de limpieza.'   o  'Mantenimiento de ascensor del edificio' . "<<endl;
        cin.getline(anadirGM.motivo,30);
        cin.ignore();
        cout << "ingrese el monto requerido para el egreso extra: "<<endl;
        cin>>anadirGM.gastosGenerales;
        cin.ignore();
        cout << "ingrese los salarios a pagar del conserje o conserjes ( OJO ! solo registrar UNA  vez al mes. ) :  "<<endl;
        cout << " \t OJO !! RECUERDE  ------>  si no es su primer registro del MES , debe poner nulo el salario de los conserjes porque ya se resgistro la primera vez. "<< endl; 
        cin>>anadirGM.gastosalarios;
        double total = anadirGM.gastosalarios + anadirGM.gastosGenerales;
        anadirGM.totalGasto[anadirGM.mes] = total;
        archivoGM.write((char*)&anadirGM, sizeof(gastosMensuales));
    }
}

bool encontrarCop(int cibuscador, string archivoCop) //codigo Anahi, yo Ari agregue el que el mostrarcop.carnet se vuelva
{                                                      // int para que se pueda comparar y validad que si existe el carnet
    ifstream mcops(archivoCop, ios::binary);
    copropietario mostrarcop;

    if (mcops.fail()) {
        cout << "nel pastel ";
        return false;
    }

    while (mcops.read((char*)&mostrarcop, sizeof(mostrarcop))) {
        int carnetInt = atoi(mostrarcop.carnet); //atoi para cambiar de char a int, Tip de LEO
        if (cibuscador == carnetInt) {
            mcops.close();
            return true;
        }
    }

    mcops.close();
    return false; //si no se encuentra ninguno;
}

void registroIngresos(string archivoCop) // codigo Anahi
{
    fstream archivo;
    copropietario cop;
    int auxci = 0;
    bool encontrado = false;
    int posicion = 0;
    double monto = cop.totalSuperficie * 2.5;

    cout<<"Ingrese el C.I. del copropietario que desea registrar el pago: ";
    cin>>auxci;

    if (!encontrarCop(auxci, archivoCop)) {
        cout<<"No se encontró el copropietario con ese C.I."<<endl;
        return;
    }

    archivo.open(archivoCop, ios::binary | ios::in | ios::out);
    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    while (archivo.read((char*)&cop, sizeof(cop))) {
        int ciLeido = atoi(cop.carnet);
        if (auxci == ciLeido) {
            cout <<"Nombre: " << cop.nombrecop << " " << cop.apellidocop << endl;
            cout <<"Departamento: " << cop.Nrodepto << endl;
            cout <<"Superficie: " << cop.totalSuperficie << " m2" << endl;
            cout <<"Debe pagar: " << monto << " Bs (2.5 Bs/m2)" << endl;
            cout <<"¿Qué mes desea registrar el pago? (0 = Enero, 1 = Febrero, ..., 11 = Diciembre): ";
            cin >> posicion;

            if (posicion < 0 || posicion > 11) {
                cout << "Mes inválido." << endl;
                break;
            }

            cout << "Ingrese el monto pagado: ";
            cin >> cop.pagoExpensas[posicion];

            archivo.seekp(-static_cast<int>(sizeof(cop)), ios::cur);
            archivo.write((char*)&cop, sizeof(cop));

            encontrado = true;
            cout << "Pago registrado correctamente." << endl;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "No se encontró el copropietario." << endl;
    }
}

//VALIDACIONES  Codigo Ari

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

void registroCopropietario(string archivoCop){ //Ari
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

void eliminarCop(string archivoCop, char banderaDepto[9]) //codigo Chris
{
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

void modificarCop(string archivoCop, char banderaDepto[9])
{
    fstream modCop;
    copropietario modificarCop;
    int opcion = 0;
    bool encontrado = false;

    modCop.open(archivoCop, ios::binary | ios::in | ios::out);
    if (modCop.fail())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    while (modCop.read((char*)&modificarCop, sizeof(modificarCop)))
    {
        if (strcmp(banderaDepto, modificarCop.Nrodepto) == 0)
        {
            encontrado = true;

            cout << "Persona encontrada: " << endl;
            cout << "Departamento: " << modificarCop.Nrodepto << endl;
            cout << "Nombre: " << modificarCop.nombrecop << " " << modificarCop.apellidocop << endl;
            cout << "Telefono: " << modificarCop.telf << endl;
            cout << "CI: " << modificarCop.carnet << endl;
            cout << "Superficie: " << modificarCop.totalSuperficie << " m2" << endl;

            do { //modificar telfono
                cout << "Ingrese un nuevo telefono (8 dígitos): ";
                cin.ignore();
                cin.getline(modificarCop.telf, 9);
                if (!soloNumeros(modificarCop.telf, 8)) {
                    cout << "TELEFONO INVALIDO. (Debe contener solo 8 dígitos)" << endl;
                }
            } while (!soloNumeros(modificarCop.telf, 8));

            cout << "Ingrese el nuevo C.I.: "; //modificar carnet
            cin >> modificarCop.carnet;
            cin.ignore();

            cout << "¿Desea cambiar el nombre y apellido? (1 = sí, 2 = no): "; // modificar nombre apellido
            cin >> opcion;
            cin.ignore();

            if (opcion == 1) // si quiere cambiar nombre y apellido
            {
                do {
                    cout << "Ingrese el nuevo nombre: ";
                    cin.getline(modificarCop.nombrecop, 30);
                    if (!soloLetras(modificarCop.nombrecop)) {
                        cout << "NOMBRE INVALIDO. (Solo letras permitidas)" << endl;
                    }
                } while (!soloLetras(modificarCop.nombrecop));

                do {
                    cout << "Ingrese el nuevo apellido: ";
                    cin.getline(modificarCop.apellidocop, 30);
                    if (!soloLetras(modificarCop.apellidocop)) {
                        cout << "APELLIDO INVALIDO. (Solo letras permitidas)" << endl;
                    }
                } while (!soloLetras(modificarCop.apellidocop));

            //cambios guardados
            modCop.seekp(-static_cast<int>(sizeof(copropietario)), ios::cur);
            modCop.write((char*)&modificarCop, sizeof(copropietario));
            cout << "Registro modificado exitosamente." << endl;
            break;
        }
    }

    if (!encontrado)
    {
        cout << "No se encontró el departamento indicado." << endl;
    }

    modCop.close();
    }
}

void mostrarArchivoCop(string archivoCop) //Chris y anahi le agrego el CI
{
    ifstream mcops;
    copropietario mostrarcop;
     int contador = 0; 
    mcops.open (archivoCop, ios::binary);
    if(mcops.fail()){
        cout << "nel pastel ";
    } else 
    {
        while (mcops.read((char*)&mostrarcop, sizeof (mostrarcop)))
        {
        cout << " ----------------------------------------------------------"<< endl;
        cout << "El nombre del copropietario es : "<< mostrarcop.nombrecop <<endl;
        cout << "El apellido del copropietario es "<< mostrarcop.apellidocop <<endl;
        cout << "El numero de depto es : "<<mostrarcop.Nrodepto <<endl;
        cout << "C.I.  : " <<mostrarcop.carnet <<endl;
        cout << "su superficie es de : " << mostrarcop.totalSuperficie <<endl;
        contador ++; 
         }
    cout << "Se mostraron " << contador << " copropietarios . " << endl;
    cout << endl;
    mcops.close();
    }
}

void encontrarInfoCop(char cibuscador[9], string archivoCop)
{
    ifstream mcops;
    copropietario mostrarcop;
    bool encontrado = false;

    mcops.open(archivoCop, ios::binary);
    if (mcops.fail()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    while (mcops.read((char*)&mostrarcop, sizeof(mostrarcop)))
    {
        if (strcmp(cibuscador, mostrarcop.carnet) == 0)
        {
            cout << "El nombre del copropietario es: " << mostrarcop.nombrecop << endl;
            cout << "El apellido del copropietario es: " << mostrarcop.apellidocop << endl;
            cout << "Con numero de carnet de identidad: " << mostrarcop.carnet << endl;
            cout << "Con numero de telefono: " << mostrarcop.telf << endl;
            cout << "El número de depto es: " << mostrarcop.Nrodepto << endl;
            cout << "Su superficie es de: " << mostrarcop.totalSuperficie << " m2" << endl;
            encontrado = true;
            cout << "-------------------------------------------------------------------------------------" << endl;
            cout << "A continuación, se presentan sus pagos registrados durante el año:"<<endl;

            cout << "ENERO \tFEBRERO \tMARZO \tABRIL \tMAYO \tJUNIO \tJULIO \tAGOSTO \tSEPTIEMBRE \tOCTUBRE \tNOVIEMBRE \tDICIEMBRE" << endl;

            for (int i = 0; i < 12; i++)
            {
                cout << mostrarcop.pagoExpensas[i] << "\t\t";
            }
            cout << endl;
            break; // si ya lo encontró, no es necesario seguir leyendo
        }
    }
    mcops.close();
    if (!encontrado)
    {
        cout << "No se encontró ningún copropietario con ese C.I." << endl;
    }
}

void ReporteEgresos(string archivoGastosmensuales) //codigo Anahi cambios Ari
{
    ifstream mcops;
    gastosMensuales gastos;
    bool encontrado = false; 
    mcops.open(archivoGastosmensuales, ios::binary);
    if(mcops.fail())
    {
        cout << "nel pastel ";
    } else 
    {
        cout << "----------------------------EGRESOS POR MES ----------------------------------- " << endl;
        cout << " ( En cada mes se reporta los egresos fijos y extras sumados a lo largo del mes.)" << endl; 
        cout << "ENERO \t FEBRERO \t MARZO \t ABRIL \t MAYO \t JUNIO \t JULIO \t AGOSTO \t SEPTIEMPRE \t OCTUBRE \t NOVIEMBRE \t DICIEMPRE" << endl;
        while (mcops.read((char*)&gastos, sizeof (gastos)))
        { 
            for (int i = 0 ; i < 12 ; i++)
            {
                cout << gastos.totalGasto[i] << " \t\t"; 
            }
            cout << "***************************************************************************************" << endl;
            cout << " DESCRIPCION DE LOS GASTOS POR MES------------------------------------------" << endl;
            cout << "\t  OJO!!\t  RECUERDE!  || 0 = ENERO , 1 FEBRERO, 2= MARZO , etc ................" << endl;
            cout << endl; 
            cout << "MES : " << gastos.mes << endl;
            cout << " Motivo  extra : " << gastos.motivo << endl;
            cout << "Monto requerido del motivo extra : " << gastos.gastosGenerales  << endl;
            cout << "Pago de salario a conserjes :(EGRESO FIJO) : " << gastos.gastosalarios << endl;
           cout << " =============================================================================================================" << endl;
        }
    }
        mcops.close();
        if (!encontrado)
        {
            cout << "nel pastel . ni modex " << endl;
        }
}

double montoXmes ( int aux, string& archivoCop) //codigo Anahi, cambios Ari
{
    ifstream mcops;
    copropietario cop; 
    double sumaTotal = 0.0;
    mcops.open(archivoCop, ios::binary);
    if(mcops.fail()){
        cout << "nel pastel ";
    } else {
                
            while (true) {
                mcops.read((char*)&cop, sizeof(cop));
                if (mcops.eof()) break; //(mcops.eof) hace que devuelve true cuando el archivo llega al final y se rompe
                sumaTotal += cop.pagoExpensas[aux];
            }
            mcops.close();
        return sumaTotal; 
    }
}

void reporteIngresos (string& archivoCop) //anahi, cambios Ari
{
    cout << "----------------------------INGRESOS POR MES ----------------------------------- " << endl;
    cout << " ( En cada mes se reporta los egresos fijos y extras sumados a lo largo del mes.)" << endl;                     
    cout << "ENERO \t FEBRERO \t MARZO \t ABRIL \t MAYO \t JUNIO \t JULIO \t AGOSTO \t SEPTIEMPRE \t OCTUBRE \t NOVIEMBRE \t DICIEMPRE" << endl;
    for (int i = 0 ; i < 12 ; i++)
    {
        cout << montoXmes(i,archivoCop) << " \t ";
    }
    cout<<endl;
}

void generarComprobanteCopropietario(string archivoCop) { //Ari
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

void mostrarComprobantePersonal(string archivoCop) { //Ari
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

void listarCopropietarios(const string& archivoCop) { //ariana
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

void menuCopropietario(char ciaux[9], string archivoCop, string archivoGastosmensuales) //anahi
{
    int opcion;

    do
    {
        system("cls");
        cout << "  ------------- BIENVENIDO COPROPIETARIO -------------------" << endl;

        cout << "\t¿Qué deseas ver?" << endl;
        cout << "\t\t1. Información personal (también tus pagos registrados)." << endl;
        cout << "\t\t2. Ingresos del edificio." << endl;
        cout << "\t\t3. Egresos del edificio." << endl;
        cout<<"\t\t 4. Mostrar Comprobante Personal."<<endl;
        cout << "\t\t0. Salir." << endl;

        cout << "\n\tIngrese la opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
            case 0:
                break;

            case 1:
                system("cls");
                encontrarInfoCop(ciaux, archivoCop);
                system("pause");
                break;

            case 2:
                system("cls");
                reporteIngresos(archivoCop);
                system("pause");
                break;

            case 3:
                system("cls");
                ReporteEgresos(archivoGastosmensuales);
                system("pause");
                break;
            case 4:
                system("cls");
                mostrarComprobantePersonal(archivoCop);
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                system("pause");
                break;
        }

    } while (opcion != 0);
}

void menuOpciones (string archivoCop, string archivoGastosmensuales){ // ari-chris
    int opcion;
    do
    {
        system("cls");
        cout << "MENU DE OPCIONES" << endl;
        cout << "================" << endl;
        cout << "\t1. Registrar ingresos del edficio." << endl;
         cout <<"\t2. Registrar egresos del edficio." << endl;
        cout << "\t3. Registrar (o modificar) copropietario." << endl;
        cout << "\t4. Mostrar copropietarios." << endl;
        cout << "\t5. Mostrar ingresos, egresos.  " << endl;
        cout<<"\t6. Listado de Copropietarios."<<endl;
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
                registroIngresos (archivoCop);
                system("pause");

                break;  
            case 2:
                system("cls");
                gastosMantenimiento(archivoGastosmensuales);
                break;
            case 3:
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
            case 4:
                system("cls");
                mostrarArchivoCop(archivoCop);
                system("pause");
                break;
            case 5:
                system("cls");

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

void menuprincipal(string archivoCop, string  archivoGastosmensuales) //Anahi REVISAR PORFI claveci
{
    int opcion;
    char clave[30];
    int claveci = 0; 
    do
    {
         system("cls");
        cout << "  ----------------------------------------- BIENVENIDO A   LIVE-EASY  --------------------------------------------" << endl;
        cout << "                                                  ================" << endl;
        cout << " ¿QUE TIPO DE USUARIO ERES?    " << endl;
        cout << " RECUERDA :  " << endl;
        cout << "\t \t opcion  '1'  : Parte de la directiva encargada de los ingresos y egresos del edificio."  << endl;
        cout << "\t \t opcion  '2'  : Eres un copropietario que desea ver el regsitro de sus pagos, ingresos y egresos del edicio."  << endl;
        cout << "\n\tIngrese la opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
            case 1:
                system("cls");
                menuOpciones (archivoCop, archivoGastosmensuales);
                system("pause");
                break;  
            case 2:{
                system("cls");
                cout << "ingresa  tu C.I. opara acceder a las opciones disponibles :  ";
                cin >> claveci ;
                bool encontrado = encontrarCop(claveci, archivoCop);
                if (!encontrado) {
                    cout<<"CI no registrado..."<<endl;
                } else {
                    menuCopropietario(claveci, archivoCop, archivoGastosmensuales);
                }
                    menuCopropietario(claveci,archivoCop,archivoGastosmensuales);
                break;
            }
            case 0:
            cout << "Gracias por usar el sistema." << endl;
            break;
            default:
            cout << "Opcion no valida." << endl;
            system("pause");
            break;
        }
                break;
    } while (opcion != 0);
}


int main(){ // anahi
    string arGastosMantenimiento="GastosDeMantenimiento.BIN";
    string arRegistroCop="RegistroDeCopropietario.BIN";
    string arRegistroIngresos = "RegistroIngresos.bin";
    menuprincipal(arRegistroCop, arGastosMantenimiento);
    
    return 0;
}