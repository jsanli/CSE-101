/*Includes the implementation of a max heap data type to be used by Priority Queue*/

#include "Heap.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int len;
    int size;
    int *array;
} Heap;

Heap *initializeHeap(int len, int h_size, int *arr) {
    Heap *h = (Heap *) calloc(1, sizeof(Heap));
    h->len = len;
    h->size = h_size;
    h->array = arr;
    return h;
}

void destructHeap(Heap *h) {
    free(h);
    h = NULL;
}

void heapify(Heap *h, int i) {
    int l = left(i);
    int r = right(i);
    int largest;
    if (l < h->size && h->array[l] > h->array[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r < h->size && h->array[r] > h->array[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(h->array, i, largest);
        heapify(h, largest);
    }
}

Heap *array_to_Heap(int *A, int len, int size) {
    Heap *h = initializeHeap(len, size, A);
    for (int i = parent(len); i >= 1; i--) {
        heapify(h, i);
    }
    return h;
}

int size(Heap *h) {
    return h->size;
}

int len(Heap *h) {
    return h->len;
}

int parent(int i) {
    return (i - 1) / 2;
}

int left(int i) {
    return (2 * i) + 1;
}

int right(int i) {
    return (2 * i) + 2;
}

void swap(int *A, int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}
