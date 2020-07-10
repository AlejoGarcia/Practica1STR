//==========================================================================================||
//                                                                                          ||
//      Header que contiene las funciones auxiliares para el programa de la calculadora     ||
//                                                                                          ||
//==========================================================================================||


#include <string.h>
#include "auxiliar.h"



//-----------------------------------------------------------------
// Funciones para descomponer la informacion de la variable estado
//-----------------------------------------------------------------

// Devuelve el estado de la memoria (habilitada 1, deshabilitada 0)
char estadoMemoria(char _cod){
    return (_cod&128)>>7;
}

char estadoFormato(char _cod){
    return (_cod&64)>>6;
}

char estadoFormato(char _cod){
    return (_cod&32)>>5;
}

char estadoOperacion(char _cod){
    return _cod&15;
}


//-----------------------------------------------
// Funciones de entrada/salida de la calculadora
//-----------------------------------------------

// Muestra la cabecera del programa (BARRA|TEXTOTITULO|\n|BARRA)
void mostrarTitulo(){
    printf(BARRA);
    printf(strcat(TEXTOTITULO,"\n"));
    printf(BARRA);
}   

// Muestra el menu inicial del programa (\n\n|TEXTOMENU|BARRA)
void mostrarMenu(){
    print("\n\n")
}     

// Lee un valor numérico del teclado entre dos cotas dadas
int leeValor(char* msg, char* err, int min, int max){
    int r;          
    printf(msg);
    scanf("%d",&r);
    while((r < min)||(r > max)){
        printf(err);
        printf(msg);
        scanf("%d",&r);
    }
    return r;
}   
                                        
// Función que devuelve el nombre de la operación
void nombreOp(char _cod, char** nombre){
    strcpy(*nombre, opEnum[estadoOperacion(_cod)]);
}    



//-------------------------------------------------------------
// Funciones de ejecución de las operaciones de la calculadora
//-------------------------------------------------------------

// Funcion empleada para ejecutar operaciones binarias
int ejecutar(char _cod, int _a, int _b){
    int r;
    switch(estadoOperacion(_cod)){
        case 1:
            r = _a | _b;
            break;
        case 2:
            r = _a & _b;
            break;
        case 3:
            r = _a ^ _b;
            break;
        case 4:
            r = _a << _b;
            break;
        case 5:
            r = _a >> _b;
            break;
        default:
            printf("\n***ERROR: funcion ejecutar con código erroneo.\n")
    }
    return r;
}

void aBinario(int x, char** bin){
    int i, m;
    m = 1;
    for (i = 0; i < 9; i++){
        if(x&m) bin[8 - i] = '1';
        else bin[8 - i] = '0';
        m <<= 1;
    }
}




//-----------------------------------------------------
// Funciones para manejar la memoria de la calculadora
//-----------------------------------------------------

/*

La memoria se implementa como una lista continua de elementos que comienzan siempre por el código del propio
comando (u operación) a guardar. Tras el, de ser necesario, se guardarán los argumentos (uno o varios en función
de cada operación). Todos los datos numericos se guardarán en el formato en el que se ejecutaron.

*/

// Guarda un elemento
void guarda(nodo** _mem, int _x, char _f){
    nodo * aux = *_mem;
    if(aux == NULL){
        aux = (nodo*) malloc(sizeof(nodo));
    } else{
        while(aux->siguiente != NULL) aux = aux->siguiente;
        aux->siguiente = (nodo*) malloc(sizeof(nodo));
        aux = aux->siguiente;
    }
    aux->siguiente = NULL;
    switch(_f){
        case 0:
            
        case 1:
        case 2:
            aux->contenido.operacion = estadoOperacion((char) _x);
        default:
            printf("\n***ERROR: guardaElemento, formato incorrecto.\n");
            break;
    }
}

// Guarda una operacion
void guarda(nodo** _mem, char _cod, int _a, int _b,int _r){
    char formato = estadoFormato(_cod);
    guardaElemento(_mem,(int) _cod, 2);
    switch(_cod&15){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            guardaElemento(_mem,_a,formato);
            guardaElemento(_mem,_b,formato);
            guardaElemento(_mem,_r,formato);
            break;
        case 6:
            guardaElemento(_mem,_a,1);
            break;
        default:
            break;
    }
}

void borra(nodo**);     // Función auxiliar para borraMemoria(), borra el último que se haya guardado en memoria


void imprime(nodo*);    // Función auxiliar para imprimeMemoria(), imprime el elemento al que apunta el puntero


void borraMemoria(nodo**);  // Borra el contenido de la memoria al completo dejando el puntero de entrada como NULL


void imprimeMemoria(nodo*); // Imprime de forma consecutiva todos los elementos contenidos en memoria hasta la ultima
                            // entrada (sig == NULL). En caso de recibir memoria vacia escribe la cadena "MEMORIA VACIA"


                           
#endif // Se cierra el if del preprocesador que comprueba si esta libreria ya estaba cargada