//PROYECTO CHRIS,ARI Y ANAHI.



#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
//esta es una sesion de prueba 
//apocositilin 
//
int contrasenia = 246810;

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
    int ci; 
    double totalSuperficie=0.0;
    int pagoExpensas[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
};


// no se empleo en ningun momento
struct generacionExpensas{
    char Nrodepto[5]="";
    char nombrecop[30]="";
    double montoExpensa=0.0;
};






void gastosMantenimiento(string archivogastosmensuales)
{
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
        archivoGM.close();
    }
     cout << " Registro realizado exitosamente . *********************************" <<endl;
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
        while (mcops.read((char *)&mostrarcop , sizeof (mostrarcop)))
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






/*------------------------------------------------------------------------------------------*/
void generarComprobanteCopropietario( int ciaux, string archivoCop) {
    double precioPorM2 = 2.5; //le ponen precioo
    ifstream archivo(archivoCop, ios::binary);
    copropietario cop;

    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo de copropietarios." << endl;
        return;
    }

    while (archivo.read((char*)&cop, sizeof(copropietario))) 
    {
        if (ciaux ==cop.ci)
        {
             string nombreArchivo =string("Comprobante_") + cop.Nrodepto + ".txt";
        ofstream comprobante(nombreArchivo);

        if (comprobante.fail()) {
            cout << "No se pudo crear el archivo de comprobante para el depto " << cop.Nrodepto << endl;
            continue;
        }
        double montoTotal = cop.totalSuperficie * precioPorM2;

        comprobante << "===============================" << endl;
        comprobante << "      COMPROBANTE DE PAGO      " << endl;
        comprobante << "===============================" << endl;
        comprobante << "Nombre: " << cop.nombrecop << " " << cop.apellidocop << endl;
        comprobante << "Telefono: " << cop.telf << endl;
        comprobante << " CI : " << cop.ci << endl; 
        comprobante << "Departamento: " << cop.Nrodepto << endl;
        comprobante << "Superficie: " << cop.totalSuperficie << " m2" << endl;
        comprobante << "Precio por m2: " << precioPorM2 << " Bs" << endl;
        comprobante << "-------------------------------" << endl;
        comprobante << "TOTAL A PAGAR: " << montoTotal << " Bs" << endl;
        comprobante << "===============================" << endl;
        comprobante << "Gracias por su pago puntual." << endl;
        comprobante.close();

        }
       
    }

    archivo.close();
    cout << "Comprobantes generados correctamente." << endl;
}




void mostrarComprobantePersonal(string archivoCop, int carnet) 
{
    ifstream archivo(archivoCop, ios::binary);
    copropietario cop;
    bool encontrado = false;

    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo de copropietarios." << endl;
        return;
    }

    while (archivo.read((char*)&cop, sizeof(cop))) 
    {
        if (carnet == cop.ci) {//check  el ci 
            
                double precioPorM2 = 2.5;
                double montoTotal = cop.totalSuperficie * precioPorM2;

                cout << "\n===============================" << endl;
                cout << "      COMPROBANTE DE PAGO      " << endl;
                cout << "===============================" << endl;
                cout << "Nombre: " << cop.nombrecop << " " << cop.apellidocop << endl;
                cout << "C.I : " << cop.ci << endl;
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
        }archivo.close();
         if (!encontrado) {
        cout << "Copropietario no encontrado." << endl;


    }
}











void registroIngresos (string archivoCop)
{
    fstream archivo;
    copropietario cop;
    // se pide el ci para registrar el pago a nombre del propietario. 
    int auxci = 0;
    bool encontrado = false;
    // para registrar el pago de mantenimiento en el vector del propietario. 
    int posicion = 0  ;
    cout << "ingrese el C.I. del copropietario que desea registrar el pago : "<< endl;
    cin >> auxci; 
    encontrarCop(auxci,archivoCop);
        if(!encontrarCop)
        {
        cout << "Error en el programa   : " << endl; 
        } else 
    {
            archivo.open(archivoCop, ios::binary | ios::in | ios::out);
            if (archivo.fail())
            {
                cout << "No se pudo abrir el archivo." << endl;
            }
            else
            {
                while (archivo.read((char *)&cop, sizeof(cop)))
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
                        cout << "\n  Que Mes va a cancelar ? \n MES DEL PAGO DEL MANTENIMIENTO : 0 = Enero, 1 = Febrero, etc . " << endl;
                        cin >> posicion;
                        cout << "Ingrese el monto que acaba de cancelar : ";
                        cin >> cop.pagoExpensas[posicion]; 
                        cin.ignore();
                         generarComprobanteCopropietario( auxci,archivoCop);

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

    
}








bool soloLetras(char * texto)
{
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
        cin.ignore();
       
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
        cout << "ingrese la superficie del departamento a registrar "<<endl;
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







void modificarCop(string archivoCop, char banderaDepto[9])
{
    fstream modCop;
    copropietario modificarCop;
    int opcion = 0;
    modCop.open(archivoCop, ios::binary | ios::in | ios::out);
    if (modCop.fail())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    else
    {
        while (modCop.read((char*)&modificarCop, sizeof(modificarCop)))
        {
            if (strcmp(banderaDepto, modificarCop.Nrodepto) == 0)
            {
                cout << "Persona encontrada " << endl;
                cout << "Departamento  : " << modificarCop.Nrodepto << endl;
                cout << "de nombre : " << modificarCop.nombrecop << " y apellido " << modificarCop.apellidocop << endl;
                cout << "de telefono :" << modificarCop.telf << endl;
                cout << "de CI : " << modificarCop.ci << endl;
                cout << "tiene una extension de " << modificarCop.totalSuperficie << endl;
                cout << "------------------------" << endl;

                do
                {
                    cout << "Ingrese un nuevo telefono (8 digitos)" << endl;
                    cin.ignore(); // para limpiar buffer antes de getline
                    cin.getline(modificarCop.telf, 9);
                    if (!soloNumeros(modificarCop.telf, 8))
                    {
                        cout << "TELEFONO INVALIDO. (debe contener 8 digitos)" << endl;
                    }
                } while (!soloNumeros(modificarCop.telf, 8));

                cout << "Ingrese el nuevo CI" << endl;
                cin >> modificarCop.ci;
                cin.ignore();

                cout << "desea cambiar el nombre y apellido de la persona?   1.si   2.no" << endl;
                cin >> opcion;
                cin.ignore();

                if (opcion == 1) // si quiere cambiar nombre y apellido
                {
                    do
                    {
                        cout << "Ingrese el nuevo nombre" << endl;
                        cin.getline(modificarCop.nombrecop, 30);
                        if (!soloLetras(modificarCop.nombrecop))
                        {
                            cout << "NOMBRE INVALIDO. (ingrese solo letras)" << endl;
                        }
                    } while (!soloLetras(modificarCop.nombrecop));

                    do
                    {
                        cout << "Ingrese el nuevo apellido" << endl;
                        cin.getline(modificarCop.apellidocop, 30);
                        if (!soloLetras(modificarCop.apellidocop))
                        {
                            cout << "APELLIDO INVALIDO. (ingrese solo letras)" << endl;
                        }
                    } while (!soloLetras(modificarCop.apellidocop));
                }
                else if (opcion != 1)
                {
                    // si no quiere cambiar nombre, continua sin modificar nombre
                }

               //cambios guardados
                modCop.seekp(-sizeof(copropietario), ios::cur);
                modCop.write((char*)&modificarCop, sizeof(copropietario));
                cout << "Registro modificado exitosamente." << endl;
                modCop.close();
                break;
            }
        }
        modCop.close();
    }
}





void mostrarArchivoCop(string archivoCop)
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
        cout << "C.I.  : " <<mostrarcop.ci <<endl;
        cout << "su superficie es de : " << mostrarcop.totalSuperficie <<endl;
        contador ++; 
         }
    cout << "Se mostraron " << contador << " copropietarios . " << endl;
    cout << endl;
    mcops.close();
    }
}





/*

void mostrarArchivoGM(string archivoMensual)
{
    ifstream mGastos;
    gastosMensuales mostrarGM;
    mGastos.open (archivoMensual, ios::binary);
    if(mGastos.fail()){
        cout << "nel pastel ";
    } else {
        while (mGastos.read((char*)&mostrarGM, sizeof (gastosMensuales)))
        {
        cout << mostrarGM.gastosGenerales <<endl;
        cout << mostrarGM.gastosalarios <<endl;
        cout << mostrarGM.periodo <<endl;
        cout << mostrarGM.totalGasto<<endl;
        cout << endl;
        mGastos.close();
        }
        
    }
    
}
    */
void encontrarInfoCop (int cibuscador, string archivoCop)
{
      ifstream mcops;
       copropietario mostrarcop;
       bool encontrado = false; 
    mcops.open (archivoCop, ios::binary);
    if(mcops.fail()){
        cout << "nel pastel ";
    } else {
        while (mcops.read((char*)&mostrarcop, sizeof (mostrarcop)))
        {
                if ( cibuscador == mostrarcop.ci)
            {
            cout << "El nombre del copropietario es : "<< mostrarcop.nombrecop <<endl;
            cout << "El apellido del copropietario es "<< mostrarcop.apellidocop <<endl;
            cout << " Con numero carnet de identidad : " << mostrarcop.ci<< endl;
            cout << "Con numero de telefono : " << mostrarcop.telf << endl; 
            cout << "El numero de depto es : "<<mostrarcop.Nrodepto <<endl;
            cout << "su superficie es de : " << mostrarcop.totalSuperficie <<endl;
            encontrado = true; 
            cout << "-------------------------------------------------------------------------------------" << endl;
            cout << "Acontinuacion, se presenta sus pagos registrados durante el anio : " << endl;
            
            cout << "ENERO \t FEBRERO \t MARZO \t ABRIL \t MAYO \t JUNIO \t JULIO \t AGOSTO \t SEPTIEMPRE \t OCTUBRE \t NOVIEMBRE \t DICIEMPRE" << endl;
            for (int i = 0 ; i < 12 ; i++)
            {
                cout << mostrarcop.pagoExpensas[i] << " \t\t"; 
            }
            cout << endl; 
            }
        }
        mcops.close();
        if (!encontrado)
        {
            cout << "nel pastel . ni modex " << endl;
        }

    }
}

void ReporteEgresos(string archivoGastosmensuales)
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
           encontrado = true; 
        }
        mcops.close();
    }
    
        if (!encontrado)
        {
            cout << "nel pastel . ni modex " << endl;
        }

}

double montoXmes ( int aux, string& archivoCop)
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

void reporteIngresos (string& archivoCop)
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

void PagosdetodosCop(string archivoCop)
{
    ifstream mcops;
    copropietario cop; 
    double sumaTotal = 0.0;
    mcops.open(archivoCop, ios::binary);
    if(mcops.fail()){
        cout << "nel pastel ";
    } else {
                
        cout<< "INGRESOS  de todos los departamentos : /////////////////////////////////////"<<endl;
        
                        cout <<  "NOMBRE \t \t  DEPARTAMENTO \t ENERO \t FEBRERO \t MARZO \t ABRIL \t MAYO \t JUNIO \t JULIO \t AGOSTO \t SEPTIEMPRE \t OCTUBRE \t NOVIEMBRE \t DICIEMPRE" << endl;
            while (mcops.read((char*)&cop, sizeof (cop)))
            {
                cout << cop.nombrecop << " " << cop.apellidocop << "\t"<< cop.Nrodepto << " \t\t" ;
                for (int i = 0 ; i < 12 ; i++)
                    {
                        cout << cop.pagoExpensas[i] << " \t ";
                    }
                    cout << endl;

            }
            cout<< "                                  --------------------------------------------------------------------------" << endl;
            mcops.close();
    } 

}  




void reporteGeneral(string archivoCop, string archivoGastosmensuales) {
    ifstream mcops(archivoGastosmensuales, ios::binary);
    if (mcops.fail()) {
        cout << "Error al abrir el archivo de gastos." << endl;
        return;
    }

    gastosMensuales gastos;
    double total = 0.0;
    mcops.read((char*)&gastos, sizeof(gastos));

    cout << "---------------- INGRESOS ----------------" << endl;
    PagosdetodosCop(archivoCop);
    cout << "---------------- EGRESOS ----------------" << endl;
    ReporteEgresos(archivoGastosmensuales);
    cout << "---------------- SALDO POR MES ----------------" << endl;
    cout << "RECUERDA: 0 = ENERO, 1 = FEBRERO, etc..." << endl;

    for (int i = 0; i < 12; i++) {
        double ingreso = montoXmes(i, archivoCop);
        double saldo = ingreso - gastos.totalGasto[i];
        cout << "----------------" << endl;
        cout << "MES: " << i << endl;
        cout << "INGRESO: " << ingreso << "  EGRESO: " << gastos.totalGasto[i] << endl;
        cout << "SALDO: " << saldo << " bs." << endl;
        total += saldo;
    }

    mcops.close();
    cout << "Total registrado: " << total << " BOLIVIANOS" << endl;
}

void menuCopropietario( int ciaux , string archivoCop, string archivoGastosmensuales)
{
    int opcion;
    char clave[30];
    bool encontrado = false ; 
   do
   {
    system("cls");
        cout << "  ------------- BIENVENIDO COPROPIEATARIO -------------------" << endl;
       
          cout << "\t ¿Que deseas ver? " << endl;
          cout << "\t \t 1. : Informacion personal (tambien tus pagos registrados)."  << endl;
          cout << "\t \t 2. : Ingresos  del edificio. "  << endl;
          cout << "\t \t 3. : Egresos del  del edificio. "  << endl;
          cout << "\t \t 4. :  Ver mis comprobantes de pago."  << endl;
          cout << "\t \t 0. :  SALIR   ."  << endl;
          
          

        cout << "\n\tIngrese la opcion: ";
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
        case 4 :
            system("cls");
           mostrarComprobantePersonal(archivoCop,ciaux);
            system("pause");
            break;
        default:
            cout<<"Opcion invalida. "<<endl;
            system("pause");
            break;
        }
   } while (opcion!=0);
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
        cout << "\t1. Registrar ingresos del edficio." << endl;
         cout <<"\t2. Registrar egresos del edficio." << endl;
        cout << "\t3. Registrar (o modificar) copropietario." << endl;
        cout << "\t4. Mostrar copropietarios." << endl;
        cout << "\t5. Mostrar ingresos, egresos y saldo por mes. " << endl;
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
                reporteGeneral(archivoCop, archivoGastosmensuales);
                system("pause");
                break;

            default:
                cout << "No existe la opcion ingresada." << endl;
                break;
        }
    } while (opcion != 0);
}

void menuprincipal(string archivoCop, string  archivoGastosmensuales)
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
             case 0:
                system("cls");
                break;
            case 1:
                system("cls");
                cout << "ingresa  tu contrasenia  para acceder a las opciones disponibles  \n ( ojo! solo los de la directiva saben la contrasena )         :   ";
                cin >> opcion;
                if (opcion == contrasenia)
                {
                menuOpciones (archivoCop, archivoGastosmensuales);
                system("pause");
                }
                else 
                {
                    cout << "Sorry, no puede ingresar, la contrasenia es incorrecta. " << endl; 
                }
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
            default:
                break;
        }
    } while (opcion != 0);
}

int main(){
    string arGastosMantenimiento="GastosDeMantenimiento.BIN";
    string arRegistroCop="RegistroDeCopropietario.BIN";
    string arRegistroIngresos = "RegistroIngresos.bin";
    menuprincipal(arRegistroCop, arGastosMantenimiento);
    
    return 0;
}