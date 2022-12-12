#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
    char c = 'a'; // 1 byte
    char c1[] = "Hola"; // 5 bytes
    char c2[] = {'H', 'o', 'l', 'a', '\0'}; // 5 bytes
    char *c3 = malloc(sizeof(char) * 6); 
    strcpy(c3, c2); // Copiar el contenido de c2 en c3

    

    printf("El valor de c es: %c, y ocupa %lu bytes\n", c, sizeof(c));
    printf("El valor de c1 es: %s, y ocupa %lu bytes\n", c1, sizeof(c1));
    printf("El valor de c2 es: %s, y ocupa %lu bytes\n", c2, sizeof(c2));

    printf("El valor de c3 es: %s, y ocupa %lu bytes\n", c3, sizeof(c3));
    free(c3);
}