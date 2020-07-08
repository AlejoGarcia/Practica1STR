// Header que contiene las funciones auxiliares para el programa de la calculadora

// Comprobamos que no se haya importado antes para no importarlo dos veces
#if !defined(AUXILIAR_H)
#define AUXILIAR_H
#endif

// Cadenas que se emplearán en la interfaz de la calculadora de forma recurrente
#define TEXTOMENU "Calcula"
#define BARRA ------------------------------------------------------

//----------------------------------------------------------------------------------
// Estructura para implementar la memoria de la calculadora (dada por el ejercicio)
//----------------------------------------------------------------------------------

//-------------------------------------------------------------
// Funciones de ejecución de las operaciones de la calculadora
//-------------------------------------------------------------





//-----------------------------------------------------
// Funciones para manejar la memoria de la calculadora
//-----------------------------------------------------

/*

La memoria se implementa como una lista continua de elementos que comienzan siempre por el código del propio
comando (u operación) a guardar. Tras el, de ser necesario, se guardarán los argumentos (uno o varios en función
de cada operación). Todos los datos numericos se guardarán en el formato en el que se ejecutaron.

*/


void guarda(nodo**);    // Guarda un elemento completo en la calculadora del tipo:
                        // [operación] [argumento/s(opcional)]

void borra(nodo**);     // Función auxiliar para borraMemoria(), borra el último que se haya guardado en memoria


void imprime(nodo*);    // Función auxiliar para imprimeMemoria(), imprime el elemento al que apunta el puntero


void borraMemoria(nodo**);  // Borra el contenido de la memoria al completo dejando el puntero de entrada como NULL


void imprimeMemoria(nodo*); // Imprime de forma consecutiva todos los elementos contenidos en memoria hasta la ultima
                            // entrada (sig == NULL). En caso de recibir memoria vacia escribe la cadena "MEMORIA VACIA"