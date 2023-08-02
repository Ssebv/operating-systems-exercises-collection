#include <stdio.h>

int main()
{
    // unsigned int a = 5;
    // long int b = 10;
    // short int c = 15;
    // double d = 20.5; 64 bits
    // float e = 25.5; 32 bits
    //char f = 'a';
    int a = 9;
    int *pointer_a = &a;
    *pointer_a = 10;
    //int *pointer_b = pointer_a;
    printf("El valor de punter : %p\n", pointer_a);
    printf("El valor donde apunta : %i\n", *pointer_a);
    //printf("El valor donde apunta el puntero : %i\n", *pointer_b);
}