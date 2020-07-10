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

// Devuelve el formato actual (binario 0, hexadecimal 1)
char estadoFormato(char _cod){
    return (_cod&64)>>6;
}

// Devuelve el bit de salida actual (no salir 0, salir 1)
char estadoSalir(char _cod){
    return (_cod&32)>>5;
}

// Devuelve el codigo de la operación
char estadoOperacion(char _cod){
    return _cod&15;
}

// Devuelve el nombre de la operación
void nombreOp(char _cod, char** _nombre){
    strcpy(*_nombre, opEnum[estadoOperacion(_cod)]);
} 

// Devuelve el condigo de la operación a partir del nombre
char codigoOp(char* _nombre){
    char i = 0;
    while(i <= 10){
        if(strcmp(_nombre, enumOp[i])) break;
        i++;
    }
    if(i > 10){
        printf("\n***ERROR: función codigoOp no se ha encontrado ninguna coincidencia.\n")
        i = -1;
    }
    return i;
}

//-----------------------------------------------
// Funciones de entrada/salida de la calculadora
//-----------------------------------------------

// Muestra la cabecera del programa
void mostrarTitulo(){
    printf("\n%s\n|%s|\n|%s|\n|%s|\n|%s|\n|%s|\n%s\n",BARRA,ESPACIO,ESPACIO,TEXTOTITULO,ESPACIO,ESPACIO,BARRA);
}   

// Muestra el menu inicial del programa
void mostrarMenu(){
    int i;
    print("\n\n");
    for(i = 1; i <= 10; i++){
        printf("%d .- %s\n", i, opEnum[i]);
    }
    printf("0 .- %s\n\n%s",opEnum[0],BARRA);
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
            printf("\n***ERROR: funcion ejecutar -> código erroneo.\n")
    }
    return r;
}

void aBinario(int _x, char** _bin){
    int i, m;
    m = 1;
    for (i = 0; i < 9; i++){
        if(_x&m) _bin[8 - i] = '1';
        else _bin[8 - i] = '0';
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
            aBinario(_x,aux->contenido.dato_binario);
            break;
        case 1:
            aux->contenido.dato = _x;
            break;
        case 2:
            nombreOp((char)_x,aux->contenido.operacion);
            break;
        default:
            printf("\n***ERROR: funcion guardaElemento -> formato incorrecto.\n");
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

// Borra el último que se haya guardado en memoria
void borra(nodo** _mem){
    nodo * aux = *_mem;
    if(aux != NULL){
        if (aux->siguiente == NULL){
            free(*_mem);
            *_mem = NULL;
        }else {
            while(aux->siguiente->siguiente != NULL) aux = aux->siguiente;
            free(aux->siguiente);
            aux->siguiente = NULL;
        }
    }
}

// Imprime el elemento al que apunta el puntero
int imprime(nodo* _elem){
    nodo * aux = _elem;
    printf("\t\t%s", aux->contenido.operacion);
    if()
}

// Borra el contenido de la memoria al completo dejando el puntero de entrada como NULL
void borraMemoria(nodo** _mem){
    while(_mem != NULL) borra(_mem);
}

// Imprime de forma consecutiva todos los elementos contenidos en memoria
void imprimeMemoria(nodo* _mem){
    nodo * aux = _mem;
    int i, n;
    if(mem_ != NULL){
        while(aux != NULL){
            n = imprime(aux);
            for(i = 0; i < n; i++) aux = aux->siguiente;
        }
    } else printf("\nMEMORIA VACÍA\n");
}