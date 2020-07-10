#include <stdio.h>
#include "auxiliar.h"


int main (void){

    // Definición de las 6 variables del programa:
    
    unsigned char estado = 207; // 207 -> 11001111
        // estado es una variable de 8 bits formada por los siguientes flags:
            // bit 7: memoria habilitada (0 no, 1 si)
            // bit 6: formato (0 binario, 1 hexadecimal)
            // bit 5: ¿salir? (0 no, 1 el programa acaba en la siguiente iteración)
            // bit 4: sin uso
            // bits 3 a 0: codificación de la operación seleccionada siguiendo la
                // numeración del menú 

    unsigned int a, b, r;    
        // a, b y r funcionan como registros de operación 
        // (a es primer operando, b el segundo y r almacena el resultado)

    char bin[9] = "";
        // variable auxiliar para realizar las conversiones a formato binario

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
        printf("Operación seleccionada: %s\n", Opciones[estadoOperacion(estado)]);
        
        switch(estadoOperacion(estado)){
            case 0:
                printf("Saliendo del programa... \n");
                estado |= 32;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                if(estadoFormato(estado)){
                    printf("Modo hexadecimal, valores de 0 a 4294967295\n");
                    a = (unsigned int) leeValor("Introduzca el primer operando: ", "El valor introducido no es válido", 0, 4294967295);
                    b = (unsigned int) leeValor("Introduzca el segundo operando: ", "El valor introducido no es válido", 0, 4294967295);
                    printf("\n");
                    r = ejecutar(estado,a,b);
                    printf("\t\t%8x\n\t  %s\t%8x\n\t%s\n\t\t%8x\n", a, Operaciones[estadoOperacion(estado)], b, BARRA2, r);
                } else { 
                    printf("Modo binario, valores de 0 a 511\n");
                    a = leeValor("Introduzca el primer operando: ", "El valor introducido no es válido", 0, 511);
                    b = leeValor("Introduzca el segundo operando: ", "El valor introducido no es válido", 0, 511);
                    printf("\n");
                    r = ejecutar(estado,a,b);
                    aBinario(a, (char**)&bin);
                    printf("\t\t%s\n\t%s\t", bin, Operaciones[estadoOperacion(estado)]);
                    aBinario(b, (char**)&bin);
                    printf("%s\n\t%s\n\t\t", bin, BARRA2);
                    aBinario(r, (char**)&bin);
                    printf("%s\n",bin);
                }
                  printf("EstadoSalir: %d", estadoSalir(estado));
                break;
            case 6:
                a = leeValor("Seleccione el nuevo formato (0 - binario, 1 - hexadecimal): ", "Ese valor no es válido\n",0,1);
                if(a){
                   estado |= 64;
                   printf("Formato cambiado a hexadecimal\n");
                } else {
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
                borraMemoria(&memoria);
                if(memoria == NULL) printf("Memoria borrada\n");
                else printf("Error al borrar memoria.\n");
                break;
            case 10:
                printf("El contenido de la memoria es:\n");
                imprimeMemoria(memoria);
                break;
            default:
                printf("Error... volviendo al menu.\n");
                break;
        }    
        // En caso de estar habilitada la memoria, guardamos la operación realizada
        printf("EstadoSalir: %d (antes de guardar)\n", estadoSalir(estado));
        if(estadoMemoria(estado)) guardaOp(&memoria, estado, a, b, r);
        printf("EstadoSalir: %d", estadoSalir(estado));
    }
    
    // Tras salir del bucle principial, el programa finaliza
    return 0;
}