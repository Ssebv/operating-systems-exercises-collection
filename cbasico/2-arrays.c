#include <stdio.h>
#include <stdlib.h>

// Comentario extendido en c es con /* */
/*

Entero: 4 bytes
Entero largo: 8 bytes
Entero largo largo: 8 bytes
Punto flotante: 4 bytes
Doble precisión: 8 bytes
Carácter: 1 byte

Es importante tener en cuenta que estos tamaños pueden variar 
en función de la plataforma en la que se ejecute el programa 
y de la configuración del compilador. 
*/

int main (){
    int *array = malloc(sizeof(int) * 8); // 8 * 4 = 32 bytes

    for (int i = 0; i < 8; i++)
    {
        array[i] = i + 1;
    }
    for (int i = 0; i < 8; i++)
    {
        printf("Valor de array[%i] = %i\n",i,array[i]);
        printf("Dirección de array[%i] = %p\n",i,&array[i]); // %p para punteros y direcciones de memoria
    }

    free(array); // Liberar memoria pero no es necesario en este caso

}