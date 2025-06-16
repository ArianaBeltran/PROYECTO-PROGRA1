//PROYECTO CHRIS,ARI Y ANAHI.




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
    char motivo [30]= "";
    double gastosGenerales=0.0;
    double gastosalarios=0.0;
    double totalGastos=0.0;
};

struct copropietario{
    char Nrodepto[5]="";
    char nombrecop[30]="";
    char apellidocop[30]="";
    char telf[9];
    int ci; 
    double totalSuperficie=0.0;
    int pagoExpensas[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
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
        cout << "ingrese el mes actual:"<<endl;
        cin.getline(anadirGM.periodo,9);
         cout << "ingrese el motivo del egreso del mes :\n  Ejemplo : ' Compra de implementos de limpieza.'   o  'Mantenimiento de ascensor del edificio' . "<<endl;
         cin.getline(anadirGM.motivo,30);
        cout << "ingrese el monto requerido para el egreso extra: "<<endl;
        cin>>anadirGM.gastosGenerales;
        cout << "ingrese los salarios a pagar del conserje o conserjes :  "<<endl;
        cin>>anadirGM.gastosalarios;
        double total = anadirGM.gastosalarios + anadirGM.gastosGenerales;
        anadirGM.totalGastos=total;
        archivoGM.write((char*)&anadirGM, sizeof(gastosMensuales));
    }
}


void registroIngresos ( string archivoCop )
{
     fstream archivo;
    copropietario cop;
    // se pide el ci para registrar el pago a nombre del propietario. 
    int auxci = 0;
    bool encontrado = false;
    // para registrar el pago de mantenimiento en el vector del propietario. 
    int posicion = 0  ;
    archivo.open(archivoCop, ios::binary | ios::in | ios::out);
    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    else
    {
        while (archivo.read((char *)&cop, sizeof(cop)) && !encontrado)
        {
            if (auxci == cop.ci)
            {
                cout << "El nombre del copropietario es : "<< cop.nombrecop <<endl;
                cout << "El apellido del copropietario es "<< cop.apellidocop <<endl;
                cout << "El numero de depto es : "<<cop.Nrodepto <<endl;
                cout << "su superficie es de : " << cop.totalSuperficie <<endl;
                encontrado = true ;
                cout << "Recuerde que el pago de mantenimiento es de 2,5 bs x metro cuadrado. \n Por lo tanto, su pago de mantenimiento es de un total de  ";
                cout << cop.totalSuperficie*2.5 << " bs. " ; 
                cout << "  Que Mes va a cancelar ? \n MES DEL PAGO DEL MANTENIMIENTO : 0 = Enero, 1 = Febrero, etc . " << endl;
                cin >> posicion;
                cout << "Ingrese el monto que acaba de cancelar : ";
                cin >> cop.pagoExpensas[posicion]; 
                cin.ignore();

                archivo.seekp(-static_cast<int>(sizeof(cop)), ios::cur);
                archivo.write((char *)&cop, sizeof(cop));
                encontrado = true;
            }

        } 
        archivo.close();
         if (!encontrado)
        {
            cout << "Contacto NO encontrado." << endl;
        }
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



void registroCopropietario(string archivoCop)
{
    ofstream registroCop;
    copropietario sumarcop;
    registroCop.open(archivoCop, ios::binary | ios::app);
    if (registroCop.fail())
    {
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

    // CI 
        cout << "ingrese el numero de carnet de indentidad del copropietario ( solo digitos!)"<<endl;
        cin>> sumarcop.ci;
       
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





void eliminarCop(string archivoCop, char banderaDepto[9]) 
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



void modificarCop(string archivoCop, char banderaDepto [9]){
    fstream modCop;
    copropietario modificarCop;
    int opcion=0;
    modCop.open(archivoCop, ios::binary | ios::in|ios::out);
    if (modCop.fail())
    {
        cout << "nel pastel";
    } else 
    {
        while (modCop.read((char*)&modificarCop, sizeof(copropietario))) 
        {
            if (strcmp(banderaDepto, modificarCop.Nrodepto)==0)
            {
                cout << "Persona encontrada " << endl;
                cout << "Departamento  : " << modificarCop.Nrodepto <<endl;
                cout << "de nombre : " << modificarCop.nombrecop << " y apellido " << modificarCop.apellidocop <<endl;
                cout << "de telefono :"<< modificarCop.telf <<endl;
                cout << "de CI : "<< modificarCop.ci <<endl;
                cout << "tiene una extension de " << modificarCop.totalSuperficie<<endl;
                cout << "------------------------" <<endl;


                do
                {
                    cout<<"Ingrese un nuevo telefono"<<endl;
                    cin.getline(modificarCop.telf, 9);
                    if(!soloNumeros(modificarCop.telf,9)){
                        cout<<"TELEFONO INVALIDO. (debe contener 8 digitos)"<<endl;
                    }
                } while (!soloNumeros(modificarCop.telf,8));

                 do
                {
                    cout<<"Ingrese el nuevo CI"<<endl;
                    cin>> modificarCop.ci;
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
}

void mostrarArchivoCop(string archivoCop){
    ifstream mcops;
    copropietario mostrarcop;
    mcops.open (archivoCop, ios::binary);
    if(mcops.fail()){
        cout << "nel pastel ";
    } else {
        while (mcops.read((char*)&mostrarcop, sizeof (copropietario)));
        cout << "El nombre del copropietario es : "<< mostrarcop.nombrecop <<endl;
        cout << "El apellido del copropietario es "<< mostrarcop.apellidocop <<endl;
        cout << "El numero de depto es : "<<mostrarcop.Nrodepto <<endl;
        cout << "C.I.  : " <<mostrarcop.ci <<endl;
        cout << "su superficie es de : " << mostrarcop.totalSuperficie <<endl;
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



void encontrarInfoCop (int cibuscador, string archivoCop)
{
      ifstream mcops;
       copropietario mostrarcop;
       bool encontrado = false; 
    mcops.open (archivoCop, ios::binary);
    if(mcops.fail()){
        cout << "nel pastel ";
    } else {
        while (mcops.read((char*)&mostrarcop, sizeof (copropietario)))
        {
                if ( cibuscador == mostrarcop.ci)
            {
            cout << "El nombre del copropietario es : "<< mostrarcop.nombrecop <<endl;
            cout << "El apellido del copropietario es "<< mostrarcop.apellidocop <<endl;
            cout << "El numero de depto es : "<<mostrarcop.Nrodepto <<endl;
            cout << "su superficie es de : " << mostrarcop.totalSuperficie <<endl;
            encontrado = true; 
            }
        }
        mcops.close();
        if (!encontrado)
        {
            cout << "nel pastel . ni modex " << endl;
        }

    }
}


bool encontrarCop (int cibuscador, string archivoCop)
{
    ifstream mcops;
    copropietario mostrarcop;
    mcops.open (archivoCop, ios::binary);
    if(mcops.fail())
    {
        cout << "nel pastel ";
    } 
    else 
    {
        while (mcops.read((char*)&mostrarcop, sizeof (copropietario)));
        {
            if ( cibuscador == mostrarcop.ci)
            {  
             return true ; 
            }
            else 
            {   
              return false ; 
            }
        }
        mcops.close();
       
    }
}



void ReporteGeneralPeriodo(string nombreArchivoPeriodo)
{
        
    
}






void menuprincipal(string archivoCop, string  archivoGastosmensuales)
{
    int opcion;
    char clave[30];
    do
    {
         system("cls");
        cout << "  ----------------------------------------- BIENVENIDO A  APOCOSITILIN (̶◉͛‿◉̶) --------------------------------------------" << endl;
        cout << "                                                  ================" << endl;
        cout << " ¿QUE TIPO DE USUARIO ERES?   ( ͡' ͜ʖ ͡') " << endl;
          cout << " RECUERDA :  (︡ᵔ ͜ʖᵔ︠) " << endl;
          cout << "\t \t opcion  '1'  : Parte de la directiva encargada de los ingresos y egresos del edificio."  << endl;
          cout << "\t \t opcion  '2'  : Eres in copropietario que desea ver el regsitro de sus pagos, ingresos y egresos del edicio."  << endl;
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
                menuCopropietario(archivoCop);
                system("pause");
                break;  
            case 2:
            system("cls");
            menuOpciones (archivoCop, archivoGastosmensuales);
            break;
        }
    } while (opcion != 0);
}






void menuCopropietario( string archivoCop)
{
    int opcion;
    char clave[30];
    int ciaux;
    bool encontrado = false ; 


   
         system("cls");
        cout << "  ------------- BIENVENIDO COPROPIEATARIO (̶◉͛‿◉̶) -------------------" << endl;
        cout << "  Ingrese su C.I. para ingresar a las opciones : " << endl;
        cin >> ciaux; 
        bool encontrarCop(ciaux,archivoCop);
        if (encontrarCop)
    {
          cout << "\t ¿QUE  DESEAS VER ? " << endl;
          cout << "\t \t 1. : Informacion personal."  << endl;
          cout << "\t \t 2. : Fondo de reserva del edificio. "  << endl;
          cout << "\t \t 3. : Egresos del  del edificio. "  << endl;
        cout << "\n\tIngrese la opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
          do {
             case 0:
                system("cls");
                break;

            case 1:
                system("cls");
                encontrarInfoCop(ciaux, archivoCop);
                system("pause");
                break;  
            case 2:
            system("cls");
            
            break;

            case 3:
            system("cls");

            break;
        } while (opcion != 0);
    }   else 
        {
            cout << "C.I. inexistente en lista de copropietarios . " 
        }
}
   





void menuOpciones (string archivoCop, string archivoGastosmensuales){
    int opcion;
    do
    {
        system("cls");
        cout << "MENU DE OPCIONES" << endl;
        cout << "================" << endl;
        cout << "\t1. Registrar ingresos del edficio." << endl;
         cout << "\t2. Registrar egresos del edficio." << endl;
        cout << "\t3. Registrar (o modificar) copropietario." << endl;
        cout << "\t4. Mostrar copropietarios." << endl;
        cout << "\t5. Mostrar ingresos, egresos del mes " << endl;
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
                gastosMantenimiento(archivoGatosmensuales);
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

            default:
                cout << "No existe la opcion ingresada." << endl;
                break;
        }
    } while (opcion != 0);
}



int main(){
    string arGastosMantenimiento="GastosDeMantenimiento.BIN";
    string arRegistroCop="RegistroDeCopropietario.BIN";
    string arRegistroIngresos = "RegistroIngresos.bin";
    menuprincipal(arGastosMantenimiento,arRegistroCop);
    
    return 0;
}