#include <stdio.h>
#include <stdlib.h>


// struct Punto{
//     double x;
//     double y;
// };

struct Node{
    int value;
    struct Node *next;
};

int main (){

    struct Node *head = malloc(sizeof(struct Node));
    head -> value = 1;
    head -> next = malloc(sizeof(struct Node));
    head -> next -> value = 2;
    head -> next -> next = malloc(sizeof(struct Node));
    head -> next -> next -> value = 3;

    printf("Direccion del primer nodo %p\n", head);
    printf("Valor del primer nodo %i\n", head -> value);

    printf("Direccion del segundo nodo %p\n", head -> next);
    printf("Valor del segundo nodo %i\n", head -> next -> value);

    printf("Direccion del tercer nodo %p\n", head -> next -> next);
    printf("Valor del tercer nodo %i\n", head -> next -> next -> value);


    // struct Punto *punto = malloc(sizeof(struct Punto));
    // punto->x = 1.0;
    // punto->y = 2.0;
    // printf("El valor de punto es: %p, y ocupa %lu bytes\n", punto, sizeof(punto));
    // printf("El valor de punto->x es: %f, y ocupa %lu bytes\n", punto->x, sizeof(punto->x));
    // printf("El valor de punto->y es: %f, y ocupa %lu bytes\n", punto->y, sizeof(punto->y));

    // free(punto);


}