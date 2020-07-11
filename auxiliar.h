//==========================================================================================||
//                                                                                          ||
//      Header que contiene las funciones auxiliares para el programa de la calculadora     ||
//                                                                                          ||
//==========================================================================================||


// Comprobamos que no se haya importado antes para no importarlo dos veces

#ifndef AUXILIAR_H
#define AUXILIAR_H


// Importamos el resto de librerias necesarias para implementar las funciones
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Cadenas que se emplearán en la interfaz de la calculadora de forma recurrente (formatear de ser necesario)

#define TEXTOTITULO "             Calculadora Binaria Simple             "
#define BARRA "------------------------------------------------------"
#define BARRA2 "----------------"
#define ESPACIO "                                                    "

static const char Opciones[11][50] = {"SALIR", "OR lógico", "AND lógico", "XOR lógico", "<< (desplazamiento a la izquierda)", ">> (desplazamiento a la derecha)", "Cambio de formato (0→ binario, 1→ hexadecimal)", "Habilitar memoria", "Deshabilitar memoria", "Borrar memoria", "Mostrar el contenido de la memoria"}; // Cadenas con los nombres de las distintas operaciones posibles

static const char Operaciones[6][4] = {"", "OR", "AND", "XOR", "<<", ">>"};


//----------------------------------------------------------------------------------
// Estructura para implementar la memoria de la calculadora (dada por el ejercicio)
//----------------------------------------------------------------------------------

typedef struct node{
    union {
        int dato; // operando o resultado para hexadecimal
        char dato_binario[9]; //cadena para almacenar el operando/resultado binario
        char operacion[50]; // cadena descriptiva de la operacion (Cambiado a 50 por necesidad de espacio)
    } contenido;
    void * siguiente;
} node;



//-----------------------------------------------------------------
// Funciones para descomponer la informacion de la variable estado
//-----------------------------------------------------------------

char estadoMemoria(char);   // Devuelve el estado de la memoria (habilitada 1, deshabilitada 0)

char estadoFormato(char);   // Devuelve el formato actual (binario 0, hexadecimal 1)

char estadoSalir(char);     // Devuelve el bit de salida actual (no salir 0, salir 1)

char estadoOperacion(char); // Devuelve el código de la operación

void nombreOp(char _cod, char** _nombre);   // Función que devuelve el nombre de la operación condificada dentro de los bits
                                            // 0,1,2 y 3 en función de su código del menú escribiendolo sobre un char[50]
                                            // siguiendo el formato de la estructura de almacenamiento y los nombres dados

char codigoOp(char* _nombre);   // Devuelve el código de la operación a partir del nombre



//-----------------------------------------------
// Funciones de entrada/salida de la calculadora
//-----------------------------------------------

void mostrarTitulo();   // Muestra la cabecera del programa (BARRA|TEXTOTITULO|BARRA)

void mostrarMenu();     // Muestra el menu inicial del programa (\n\n|TEXTOMENU|BARRA)

int leeValor(char*, char*, int, int);   // Lee un valor numérico del teclado entre dos cotas dadas pidiendolo 
                                        // con el mensaje indicado, en caso de salirse del margen imprime el
                                        // mensaje de error que se le indica



//-------------------------------------------------------------
// Funciones de ejecución de las operaciones de la calculadora
//-------------------------------------------------------------

int ejecutar(char, int, int);   // Funcion empleada para ejecutar todas las operaciones binarias (con dos operandos)
                                // de la calculadora

void aBinario(int, char**);     // Funcion auxiliar para transformar valores a binario (con solo 9 dígitos)



//-----------------------------------------------------
// Funciones para manejar la memoria de la calculadora
//-----------------------------------------------------

/*

La memoria se implementa como una lista continua de elementos que comienzan siempre por el código del propio
comando (u operación) a guardar. Tras el, de ser necesario, se guardarán los argumentos (uno o varios en función
de cada operación). Todos los datos numericos se guardarán en el formato en el que se ejecutaron.

*/


void guardaElemento(node**, int, char); // Guarda un elemento asignado el tipo adecuado en función del formato
                                        // siendo 0 un operando binario, 1 un operando hexadecimal y 2 una cadena
                                        // cadena descripitiva de operación. En este último caso se utilizará el 
                                        // caracter ultimo (numero 49) para almacenar el formato en el que se guardan
                                        // los operandos

void guardaOp(node**, char, int, int, int); // Guarda un elemento completo en la calculadora del tipo:
                                            // [operación] [argumento/s(opcional)]

void borra(node**);     // Función auxiliar para borraMemoria(), borra el último que se haya guardado en memoria

char imprimeElem(node*);    // Función auxiliar para imprimeMemoria(), imprime el elemento al que apunta el puntero

void borraMemoria(node**);  // Borra el contenido de la memoria al completo dejando el puntero de entrada como NULL

void imprimeMemoria(node*); // Imprime de forma consecutiva todos los elementos contenidos en memoria hasta la ultima
                            // entrada (sig == NULL). En caso de recibir memoria vacia escribe la cadena "MEMORIA VACIA"



#endif // Se cierra el if del preprocesador que comprueba si esta libreria ya estaba cargada
