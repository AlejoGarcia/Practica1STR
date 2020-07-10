//================================================||
//                                                ||
//      Implementación del fichero auxiliar.h     ||
//                                                ||
//================================================||


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
    strcpy(*_nombre, Opciones[estadoOperacion(_cod)]);
}

// Devuelve el condigo de la operación a partir del nombre
char codigoOp(char* _nombre){
    char i = 0;
    while(i <= 10){
        if(strcmp(_nombre, Opciones[i])) break;
        i++;
    }
    if(i > 10){
        printf("\n***ERROR: función codigoOp no se ha encontrado ninguna coincidencia.\n");
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
    printf("\n\n");
    for(i = 1; i <= 10; i++){
        printf("%d .- %s\n", i, Opciones[i]);
    }
    printf("0 .- %s\n\n%s",Opciones[0],BARRA);
}

// Lee un valor numérico del teclado entre dos cotas dadas
int leeValor(char* _msg, char* _err, int _min, int _max){
    int r;          
    printf("%s", _msg);
    scanf("%d",&r);
    while((r < _min)||(r > _max)){
        printf("%s\n", _err);
        printf("%s", _msg);
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
            printf("\n***ERROR: funcion ejecutar -> código erroneo.\n");
    }
    return r;
}

// Función auxiliar para pasar los datos a binario con 9 caracteres
void aBinario(int _x, char** _bin){
    int i, m;
    m = 1;
    for (i = 0; i < 9; i++){
        if(_x&m) (*_bin)[8 - i] = '1';
        else (*_bin)[8 - i] = '0';
        m <<= 1;
    }
}



//-----------------------------------------------------
// Funciones para manejar la memoria de la calculadora
//-----------------------------------------------------

/*

La memoria se implementa como una lista continua de elementos que comienzan siempre por el código del propio
comando (u operación) a guardar. Tras él, de ser necesario, se guardarán los argumentos (uno o tres en función
de cada operación). Todos los datos numéricos se guardarán en el formato en el que se ejecutaron.

*/

// Guarda un elemento
void guardaElemento(node** _mem, int _x, char _f){
    node * aux = *_mem;
    if(aux == NULL){
        aux = (node*) malloc(sizeof(node));
    } else{
        while(aux->siguiente != NULL) aux = aux->siguiente;
        aux->siguiente = (node*) malloc(sizeof(node));
        aux = aux->siguiente;
    }
    aux->siguiente = NULL;
    switch(_f){
        case 0:
            aBinario(_x,(char**)&(aux->contenido.dato_binario));
            break;
        case 1:
            aux->contenido.dato = _x;
            break;
        case 2:
            nombreOp((char)_x,(char**)&(aux->contenido.operacion));
            aux->contenido.operacion[49] = _f;
            break;
        default:
            printf("\n***ERROR: funcion guardaElemento -> formato incorrecto.\n");
            break;
    }
}

// Guarda una operacion
void guardaOp(node** _mem, char _cod, int _a, int _b,int _r){
    char formato = estadoFormato(_cod);
    guardaElemento(_mem, (int) _cod, 2);
    switch(estadoOperacion(_cod)){
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
            printf("\n***ERROR: función guardaOp -> Operación inexistente.\n");
            break;
    }
}

// Borra el último que se haya guardado en memoria
void borra(node** _mem){
    node * aux = *_mem;
    node * aux2;
    if(aux != NULL){
        if (aux->siguiente == NULL){
            free(*_mem);
            *_mem = NULL;
        } else {
            while(aux->siguiente != NULL){
                aux2 = aux;
                aux = aux->siguiente;
            } 
            free(aux);
            aux2->siguiente = NULL;
        }
    }
}

// Imprime el elemento al que apunta el puntero
char imprimeElem(node* _elem){
    node * aux = _elem;
    char cod = codigoOp(aux->contenido.operacion);
    char n = 1;
    char f = aux->contenido.operacion[49];
    printf("\t%s", aux->contenido.operacion);
    aux = aux->siguiente;
    if((cod >= 1)&&(cod <= 5)){
        printf(":\t");
        if(f){
            printf("%x %s ", aux->contenido.dato, Operaciones[cod]);
            aux = aux->siguiente;
            printf("%x = ", aux->contenido.dato);
            aux = aux->siguiente;
            printf("%x \n", aux->contenido.dato);
        } else {
            printf("%s %s ", aux->contenido.dato_binario, Operaciones[cod]);
            aux = aux->siguiente;
            printf("%s = ", aux->contenido.dato_binario);
            aux = aux->siguiente;
            printf("%s \n", aux->contenido.dato_binario);
        }
        n = 3;
    }else if(cod != 6){
        printf(": %d\n", aux->contenido.dato);
        n = 2;
    }
    return n;
}

// Borra el contenido de la memoria al completo dejando el puntero de entrada como NULL
void borraMemoria(node** _mem){
    while(_mem != NULL) borra(_mem);
}

// Imprime de forma consecutiva todos los elementos contenidos en memoria
void imprimeMemoria(node* _mem){
    node * aux = _mem;
    int i, n, k;
    if(_mem != NULL){
        k = 1;
        while(aux != NULL){
            printf("(%3d)",k);
            n = imprimeElem(aux);
            for(i = 0; i < n; i++) aux = aux->siguiente;
            k++;
        }
    } else printf("\nMEMORIA VACÍA\n");
}