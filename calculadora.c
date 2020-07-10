#include <stdio.h>
#include "auxiliar.h"


int main (void){
    
    // Definición de las 5 variables del programa:
    
    unsigned char estado = 207;
        // estado es una variable de 8 bits formada por los siguientes flags:
            // bit 7: memoria habilitada (0 no, 1 si)
            // bit 6: formato (0 binario, 1 hexadecimal)
            // bit 5: ¿salir? (0 no, 1 el programa acaba en la siguiente iteración)
            // bit 4: sin uso
            // bits 3 a 0: codificación de la operación seleccionada siguiendo la
                // numeración del menú 
    
    int a, b, r;    
        // a, b y r funcionan como registros de operación 
        // (a es primer operando, b el segundo y r almacena el resultado) 

    node * memoria = NULL;   
        // memoria es un puntero a la estructura node sobre la que se implementa 
        // la memoria dinámica del programa (cadena) se inicialica vacia (NULL)

    
    // La primera función a la que se llama es la que imprime por pantalla el
    // título del programa (solo se hace una vez en toda la ejecución)
    mostrarTitulo();
    
    
    // Mientras el flag "¿Salir?" este a 0 en la variable estado ejecutamos el 
    // bucle principal del programa
    while(!estadoSalir(estado)){
        
        // Limpiamos la variable del estado poniendola a 0 (operación SALIR)
        estado &= ~15;
        
        // Mostramos el menú del programa al usuario
        mostrarMenu();
        
        // Pedimos el código de la operación a realizar
        a = leeValor("Seleccione una acción: ","El valor introducido no es correcto\n",0,10);
        
        // Actualizamos el valor del codigo de operacion en estado con el valor recibido
        estado |= (unsigned char) (a&15);
        
        
        switch(estado&15){
            case 0:
                printf("Saliendo del programa... \n");
                estado |= 32;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                r = ejecutar(estado,a,b);
            case 6:
                a = leeValor("Seleccione el nuevo formato (0 - binario, 1 - hexadecimal): ", "Ese valor es válido\n",0,1);
                if(a){
                   estado |= 64;
                   printf("Formato cambiado a hexadecimal\n");
                }else{
                   estado &= ~64;
                   printf("Formato cambiado a binario\n");
                }
                break;
            case 7:
                estado |= 128;
                printf("Memoria habilitada\n");
                break;
            case 8:
                estado &= ~128;
                printf("Memoria deshabilitada\n");
                break;
            case 9:
                printf("Borrando el contenido de la memoria...\n");
                if(borrarMemoria(memoria) == 0) printf("Memoria borrada\n");
                else printf("Error al borrar memoria\n");
                break;
            case 10:
                printf("El contenido de la memoria es:\n");
                imprimirMemoria(memoria);
                break;
            default:
                break;
        }
        
        // En caso de estar habilitada la memoria, guardamos la operación realizada
        if(estado&128) guardar(estado,a,b,r);
        
    }
    return 0;
}