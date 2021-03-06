// Header que contiene las funciones auxiliares para el programa de la calculadora


// Comprobamos que no se haya importado antes para no importarlo dos veces

#ifndf AUXILIAR_H
#define AUXILIAR_H



// Cadenas que se emplearán en la interfaz de la calculadora de forma recurrente

#define TEXTOMENU "Calculadora Binaria Simple\n"
#define TEXTOMENU "1.- OR lógico\n2.- AND lógico\n3.- XOR lógico\n4.- << (desplazamiento a la izquierda)\n5.- >> (desplazamiento a la derecha)\n6.- Cambio de formato (0→ binario, 1→ hexadecimal)\n7.- Habilitar memoria\n8.- Deshabilitar memoria\n9.- Borrar memoria\n10.- Mostrar el contenido de la memoria\n0.- SALIR"
#define BARRA ------------------------------------------------------



//----------------------------------------------------------------------------------
// Estructura para implementar la memoria de la calculadora (dada por el ejercicio)
//----------------------------------------------------------------------------------

typedef struct node{
    union {
        int dato; // operando o resultado para hexadecimal
        char dato_binario[9]; //cadena para almacenar el operando/resultado binario
        char operacion[30]; // cadena descriptiva de la operacion
    } contenido;
    void * siguiente;
} node;



//-----------------------------------------------
// Funciones de entrada/salida de la calculadora
//-----------------------------------------------

void mostrarTitulo();   // Muestra la cabecera del programa

void mostrarMenu();     // Muestra el menu inicial del programa

int leeValor(char*, char*, int, int);   // Lee un valor numérico del teclado entre dos cotas dadas pidiendolo 
                                        // con el mensaje indicado, en caso de salirse del margen imprime el
                                        // mensaje de error que se le indica



//-------------------------------------------------------------
// Funciones de ejecución de las operaciones de la calculadora
//-------------------------------------------------------------

int ejecutar(char, int, int);

void aBinario(int,**char);


//-----------------------------------------------------
// Funciones para manejar la memoria de la calculadora
//-----------------------------------------------------

/*

La memoria se implementa como una lista continua de elementos que comienzan siempre por el código del propio
comando (u operación) a guardar. Tras el, de ser necesario, se guardarán los argumentos (uno o varios en función
de cada operación). Todos los datos numericos se guardarán en el formato en el que se ejecutaron.

*/

void guarda(nodo**,char,int,int,int);    // Guarda un elemento completo en la calculadora del tipo:
                        // [operación] [argumento/s(opcional)]

void borra(nodo**);     // Función auxiliar para borraMemoria(), borra el último que se haya guardado en memoria


void imprime(nodo*);    // Función auxiliar para imprimeMemoria(), imprime el elemento al que apunta el puntero


void borraMemoria(nodo**);  // Borra el contenido de la memoria al completo dejando el puntero de entrada como NULL


void imprimeMemoria(nodo*); // Imprime de forma consecutiva todos los elementos contenidos en memoria hasta la ultima
                            // entrada (sig == NULL). En caso de recibir memoria vacia escribe la cadena "MEMORIA VACIA"


                           
#endif // Se cierra el if del preprocesador que comprueba si esta libreria ya estaba cargada