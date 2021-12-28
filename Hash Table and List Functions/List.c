#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------
// Returns ptr to node with matching key, else returns NULL
// -----------------------------
node_t *findList(node_t *head, char *key) {
    node_t *ptr;

    ptr = head;
    while (ptr != NULL) {
        if (strcmp(ptr->key, key) == 0)
            break;
        else
            ptr = ptr->next;
    }
    return (ptr);
}

// -----------------------------
// Returns ptr to node with matching key, else returns NULL
// -----------------------------
void insertList(node_t **head, node_t *new) {
    // insert new node as head of list
    if (*head == NULL) {
        *head = new;
        (*head)->next = NULL;
        (*head)->prev = NULL;
    } else {
        new->next = *head;
        (*head)->prev = new;
        new->prev = NULL;
        *head = new;
    }
}

// -----------------------------
// Deletes node pointed to by del from the list.
// You can assume that del points to a node in the list.
// -----------------------------
void deleteList(node_t **head, node_t *del) {
    node_t *ptr;

    ptr = *head;
    while (ptr != NULL) {
        if (ptr == del)
            break;
        else
            ptr = ptr->next;
    }
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;
    ptr = NULL;
}

// -----------------------------
// Prints key field of each node in the list starting at head.
// -----------------------------
void printList(node_t *head) {
    printf("%s\n", head->value);
    while (head->next != NULL) {
        printf("%s\n", head->next->value);
    }
}
