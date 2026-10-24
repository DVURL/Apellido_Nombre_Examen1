/*
Nombre del estudiante: Uriel Jaramillo
Fecha: 23/10/2026
Tema: Sistema de registro y análisis de notas

Enunciado: Una Academia necesita un programa en C++ para registrar las notas finales de un grupo de estudiantes y consultar información básica del curso.
El sistema trabajará con un máximo de 20 estudiantes.
De cada estudiante se almacenará:
* primer nombre (sin espacios);
* nota final en escala de 0 a 20.

Entrada: cantidad, nombres, notas, opción del menú y nombre a buscar
Proceso: validar, almacenar, recorrer, calcular y buscar
Salida: reporte general y resultado de búsqueda
*/

#include <iostream>   
#include <string>     
using namespace std;

// Máximo de estudiantes
const int MAX_ESTUDIANTES = 20; 
// Nota mínima para aprobar  
const double NOTA_APROBAR = 14; 

// Imprime el menú
void mostrarMenu() {
    cout << "\n============ MENÚ ============" << endl;
    cout << "--------------------------------" << endl;
    cout << "1. Registrar estudiantes y notas" << endl;
    cout << "--------------------------------" << endl;
    cout << "2. Mostrar reporte general" << endl;
    cout << "--------------------------------" << endl;
    cout << "3. Buscar estudiante por nombre" << endl;
    cout << "--------------------------------" << endl;
    cout << "4. Salir" << endl;
    cout << "--------------------------------" << endl;
    cout << "Seleccione una opción :D : ";
}

//Función 2: leerOpcion 
// Pide la opción del menú y la repite hasta que esté entre 1 y 4.
// Devuelve la opción válida (int).

int leerOpcion() {
    // Aquí se guarda lo que escribe el usuario
    int opcion;  
    // Lee la primera opción                 
    cin >> opcion;      
    // Mientras sea inválida (menor a 1 o mayor a 4)              
    while (opcion < 1 || opcion > 4) { 
        cout << "Opción inválida. Ingrese un número entre 1 y 4: ";
        // Vuelve a pedir
        cin >> opcion;                
    }
    return opcion;
}

//Función 3: obtenerEstado 
// Recibe una nota y devuelve "~~~APROBADO~~~" o "~~~REPROBADO~~~".
// Se usa en el reporte y en la búsqueda, para no tener que repetir el if :x
string obtenerEstado(double nota) {
    // Aprueba con 14 o más
    if (nota >= NOTA_APROBAR) {       
        return "~~~APROBADO~~~";
    }
    // Si no entró al if, reprueba
    return "~~~REPROBADO~~~";         
}

//Función 4: registrarEstudiantes
// Llena los arreglos nombres[] y notas[].
// Devuelve la cantidad de estudiantes registrados.
int registrarEstudiantes(string nombres[], double notas[]) {
    // Cuántos estudiantes se van a registrar
    int cantidad;                     
    cout << "Cantidad de estudiantes (1-20): ";
    cin >> cantidad;
    // Validación 1-20
    while (cantidad < 1 || cantidad > MAX_ESTUDIANTES) {  
        cout << "Cantidad inválida. Ingrese un valor entre 1 y 20: ";
        cin >> cantidad;
    }

    // Bucle for: se repite una vez por estudiante (posiciones 0 hasta cantidad-1).
    // Al sobrescribir las posiciones, los datos anteriores se reemplazan.
    for (int i = 0; i < cantidad; i++) {
        cout << "\nEstudiante " << (i + 1) << endl;
        cout << "Nombre (sin espacios): ";
        // Guarda el nombre en la posición i
        cin >> nombres[i];            

        cout << "Nota final (0-20): ";
        // Guarda la nota en la misma posición i
        cin >> notas[i];              
        // Validación de la nota
        while (notas[i] < 0 || notas[i] > 20) {  
            cout << "Nota inválida. Ingrese una nota entre 0 y 20: ";
            cin >> notas[i];
        }
    }

    cout << "\nRegistro completado." << endl;
    return cantidad;                  
}

//Función 5: mostrarReporte 
// Recorre los arreglos y calcula todo lo que pide el examen.
// 'cantidad' dice cuántas posiciones del arreglo están realmente en uso.
void mostrarReporte(string nombres[], double notas[], int cantidad) {
    // ACUMULADOR: suma de todas las notas
    double suma = 0;       
    // CONTADOR de aprobados           
    int aprobados = 0;     
    // CONTADOR de reprobados           
    int reprobados = 0;   
    // Posición de la nota mayor           
    int posMayor = 0;      
     // Posición de la nota menor         
    int posMenor = 0;                 

    cout << "\n======= REPORTE GENERAL =======" << endl;

    for (int i = 0; i < cantidad; i++) {
        // APROBADO o REPROBADO
        string estado = obtenerEstado(notas[i]);   

        // Línea numerada del listado
        cout << (i + 1) << ". " << nombres[i] << " - Nota: " << notas[i]
             << " - " << estado << endl;

        // Se acumula la nota
        suma = suma + notas[i];      

        // Se cuenta según el estado
        if (estado == "~~~APROBADO~~~") {
            aprobados++;
        } else {
            reprobados++;
        }

        // Se usa > y < (no >= ni <=) para que, en caso de empate,
        // se quede la PRIMERA persona que apareció.
        if (notas[i] > notas[posMayor]) {
            posMayor = i;
        }
        if (notas[i] < notas[posMenor]) {
            posMenor = i;
        }
    }

    double promedio = suma / cantidad;   

    cout << "\nPromedio general: " << promedio << endl;
    cout << "Nota mayor: " << nombres[posMayor] << " (" << notas[posMayor] << ")" << endl;
    cout << "Nota menor: " << nombres[posMenor] << " (" << notas[posMenor] << ")" << endl;
    cout << "Aprobados: " << aprobados << endl;
    cout << "Reprobados: " << reprobados << endl;
}

//Función 6: buscarEstudiante 
// Búsqueda secuencial: revisa posición por posición hasta encontrar el nombre.
void buscarEstudiante(string nombres[], double notas[], int cantidad) {
    // Nombre que escribe el usuario
    string buscado;         
    // Bandera: ¿ya lo encontramos?         
    bool encontrado = false;          

    cout << "Nombre que deseas buscar: ";
    cin >> buscado;

    for (int i = 0; i < cantidad; i++) {
        // == entre strings es exacto y distingue mayúsculas/minúsculas ("Ana" != "ana")
        if (nombres[i] == buscado) {
            cout << "\nEstudiante encontrado:" << endl;
            cout << "Nombre: " << nombres[i] << endl;
            cout << "Nota: " << notas[i] << endl;
            cout << "Estado: " << obtenerEstado(notas[i]) << endl;
            encontrado = true;        
            break;                    
        }
    }
    // Si terminó el bucle sin encontrarlo
    if (!encontrado) {                
        cout << "\nNo existe un estudiante con el nombre \"" << buscado << "\"." << endl;
    }
}


int main() {
    // Arreglo de nombres (20 espacios)
    string nombres[MAX_ESTUDIANTES]; 
    // Arreglo de notas (misma posición = mismo estudiante) 
    double notas[MAX_ESTUDIANTES];    
    // 0 significa "todavía no hay datos"
    int cantidad = 0;            
    // Opción elegida en el menú     
    int opcion;                       

    do {                              
        mostrarMenu();
        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                cantidad = registrarEstudiantes(nombres, notas);
                break;

            case 2:
                 // Control obligatorio: no hay datos aún
                if (cantidad == 0) {  
                    cout << "\nTodavía no existen datos, registre los nombres de los estudiantes primero (opción 1)." << endl;
                } else {
                    mostrarReporte(nombres, notas, cantidad);
                }
                break;

            case 3:
                // Mismo control para la búsqueda
                if (cantidad == 0) {  
                    cout << "\nTodavía no existen datos, registre los nombres de los estudiantes primero (opción 1)." << endl;
                } else {
                    buscarEstudiante(nombres, notas, cantidad);
                }
                break;

            case 4:
                cout << "\nSaliendo del programa. ¡Hasta luego!" << endl;
                break;
        }
    // Se repite hasta elegir la opción 4
    } while (opcion != 4);            

    return 0;                         
}
