#include "List.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct NodeObj {
    int data;
    struct NodeObj *next;
} NodeObj;
typedef NodeObj *Node;

typedef struct ListObj {
    NodeObj *head;
    int length;
} ListObj;

Node newNode(int x) {
    Node n = (Node) calloc(1, sizeof(Node));
    n->next = NULL;
    n->data = x;
    return n;
}

List newList(void) {
    List l = (List) calloc(1, sizeof(ListObj));
    l->head = NULL;
    l->length = 0;
    return l;
}

void freeNode(Node *Pn) {
    free(*Pn);
    *Pn = NULL;
}

void freeList(List *pL) {
    Node n = (*pL)->head;
    while (n != NULL) {
        freeNode(&n);
        n = (*pL)->head->next;
    }
    free(*pL);
    pL = NULL;
}

int length(List L) {
    /*    if (L == NULL)
        exit(-1);*/
    return L->length;
}

int max(List L) {
    if (L == NULL)
        exit(-1);
    int index = 0;
    int iter = 0;
    Node n = L->head;
    int max = n->data;
    while (n->next != NULL) {
        iter++;
        if (n->next->data > max) {
            index = iter;
            max = n->next->data;
        }
        n = n->next;
    }
    return index;
}

void appendList(List L, int i) {
    if (L == NULL)
        exit(-1);
    Node n = newNode(i);
    if (L->length == 0) {
        L->head = n;
    } else {
        Node temp = L->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = n;
    }
    L->length++;
}

int delElement(List L, int i) {
    int temp = 0;
    if (i + 1 > L->length)
        exit(-1);
    Node n = L->head;
    if (i == 0) {
        temp = L->head->data;
        L->head = n->next;
        L->length--;
        return temp;
    }
    int iter = 1;
    while (n->next != NULL) {
        if (i == iter) {
            temp = n->next->data;
            n->next = n->next->next;
            L->length--;
            return temp;
        }
        iter++;
        n = n->next;
    }
    exit(-1);
}

int find(List L, int i) {
    Node n = L->head;
    int iter = 0;
    while (n != NULL) {
        if (n->data == i) {
            return iter;
        }
        n = n->next;
        iter++;
    }
    return -1;
}

void printList(List L) {
    if (L == NULL)
        exit(-1);
    Node n = L->head;
    while (n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n");
}
