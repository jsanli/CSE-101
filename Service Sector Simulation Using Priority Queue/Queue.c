/*Contains the immplementation for a Queue data type to be used by simulator.c*/

#include "Queue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int head;
    int tail;
    int length;
    int count;
    int *array;
} Queue;

Queue *initializeQueue(int n, int *arr) {
    Queue *q = (Queue *) calloc(1, sizeof(Queue));
    q->array = arr;
    q->length = n;
    q->count = 0;
    q->head = 0;
    q->tail = 0;
    return q;
}

void destructQueue(Queue *q) {
    free(q);
    q = NULL;
}

void enqueue(Queue *q, int x) {
    if (q->count != q->length) {
        q->array[q->tail] = x;
        if (q->tail == q->length) {
            q->tail = 0;
        } else {
            q->tail++;
        }
        q->count++;
    }
}

int dequeue(Queue *q) {
    if (q->count != 0) {
        int value = q->array[q->head];
        q->array[q->head] = -1;
        if (q->head == q->length) {
            q->head = 0;
        } else {
            q->head++;
        }
        q->count--;
        return value;
    }
    return 0;
}

void printQueue(Queue *q) {
    printf("%s", "Queue: ");
    for (int x = 0; x < q->length; x++) {
        if (q->array[x] != -1) {
            printf("%d ", q->array[x]);
        }
    }
    printf("\n");
}

int count(Queue *q) {
    return q->count;
}
