/*Inlucdes the implementation of a priority queue adt to be used by the simulator*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Heap.c"
#include "PriorityQueue.h"

int get_max(Heap *h) {
    return h->array[0];
}

int extract_max(Heap *h) {
    if (h->size < 1) {
        return -1;
    }
    int max = h->array[0];
    h->array[0] = h->array[size(h) - 1];
    h->size--;
    heapify(h, 0);
    return max;
}

void increase_priority(Heap *h, int i, int new_value) {
    if (new_value < h->array[i]) {
        fprintf(stderr, "new key is smaller than current key\n");
        return;
    }
    h->array[i] = new_value;
    while (i > 0 && h->array[parent(i)] < h->array[i]) {
        swap(h->array, i, parent(i));
        i = parent(i);
    }
}

void insert(Heap *h, int value) {
    h->size++;
    h->array[size(h) - 1] = -1;
    increase_priority(h, h->size - 1, value);
}
