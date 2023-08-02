#include <stdio.h>
#include <stdlib.h>

struct Node{
    int value;
    struct Node *next;
};

int main() {

    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Crear el primer nodo
    struct Node *head = malloc(sizeof(struct Node));
    for (int i = 0; i < 10; i++) {
        // Crear un nuevo nodo
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->value = values[i];
        new_node->next = NULL;

        // Enlazar el nuevo nodo al final de la lista
        struct Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    // Recorrer la lista enlazada utilizando un puntero auxiliar
    struct Node *current = head;
    while (current != NULL) {
        // Acceder al valor y a la dirección de memoria del nodo actual
        printf("Direccion del nodo actual %p\n", current);
        printf("Valor del nodo actual %i\n", current->value);
        // Avanzar al siguiente nodo en la lista
        current = current->next;
    }

    // Liberar la memoria asignada a cada nodo
    current = head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}