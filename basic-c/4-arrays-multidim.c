#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char c[][8] = {"Hola", "Mundo"};
    char **strings = malloc(sizeof(char*) * 2);
    char *msg1 = malloc(sizeof(char) * 8);
    char *msg2 = malloc(sizeof(char) * 8);

    strcpy(msg1, "Hola");
    strcpy(msg2, "Mundo");

    strings[0] = msg1;
    strings[1] = msg2;

    printf("El valor de c[0] es: %s, y ocupa %lu bytes\n", c[0], sizeof(c[0]));
    printf("El valor de c[1] es: %s, y ocupa %lu bytes\n", c[1], sizeof(c[1]));

    printf("El valor de msg1 es: %s, y ocupa %lu bytes\n", msg1, sizeof(msg1));
    printf("El valor de msg2 es: %s, y ocupa %lu bytes\n", msg2, sizeof(msg2));

    printf("El valor de strings[0] es: %s, y ocupa %lu bytes\n", strings[0], sizeof(strings[0]));
    printf("El valor de strings[1] es: %s, y ocupa %lu bytes\n", strings[1], sizeof(strings[1]));
}