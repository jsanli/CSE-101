// -------------------------------
// Dictionary ADT:
//
// -------------------------------

#include "Dictionary.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
// -------------------------------
// TODO: implement create
// create( *D, n ) -- creates a dictionary with n slots
// Initializes slots to n, and size to 0.
// -------------------------------

void create(dictionary *D, int n) {
    // initialize the 'slots' and 'size' field
    D->slots = n;
    D->size = 0;
    D->hash_table = (node_t *) calloc(n, sizeof(node_t));

    // allocate memoRy for 'n' node_t structs and assignt to 'hash_table' field
    for (int x = 0; x < n; x++) {
        D->hash_table[x] = *(node_t *) calloc(1, sizeof(node_t));
        D->hash_table[x].value = NULL;
        D->hash_table[x].prev = NULL;
        D->hash_table[x].next = NULL;
        memcpy(D->hash_table[x].key, "", 5);
    }

    // loop over the 'n' elements
    // initialize 'value', 'next' , and 'prev' fields to 'NULL'
    // initialize the 'key' field of each node to a char string of size 5
    // HINT: can use something like this 'memcpy( D->hash_table[i].key, "", 5 );
}

// -------------------------------
// TODO: implement insert
// insert( *D, *e ) -- inserts element e->key:e->value into the dictionary.
// First, make sure that e->key does not exist in *D yet.
// If it does, return an error code of -1.
// Otherwise, update the size of *D, and return 0.
// -------------------------------

int insert(dictionary *D, element *e) {
    // check if element's key already in dictionary

    // if not:

    // instantiate a new node

    // set the 'key' and 'value' fields of the newly instantiated node
    // these come from 'key' and 'value' fields of element
    // HINT: can use memcpy to copy element's key to node's key field

    // get the index of element in the dictionary

    // using the index, get the node/head of the list corresp. to that index
    // add the newly created node to the list
    // NOTE: this follows the same logic of adding a node to list
    // but do NOT use insertList from List.c

    int present = 0;
    for (int x = 0; x < D->slots; x++) {
        if (D->hash_table[x].key == e->key) {
            present = 1;
        }
    }
    if (present == 0) {
        node_t *n = (node_t *) calloc(1, sizeof(node_t));
        n->value = e->value;
        memcpy(n->key, e->key, 5);
        n->prev = NULL;
        n->next = NULL;
        int index = hash(e->key, D->slots);
        node_t *head = &(D->hash_table[index]);
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = n;
        n->prev = head;
        D->size++;
        return 0;
    } else {
        return -1;
    }
}

// -------------------------------
// TODO: implement delete
// delete( *D, *key ) -- deletes element with key (*key) from the dictionary.
// If *key does not exist in *D, return an error code of -1.
// Update the size of *D, and return 0.
// -------------------------------

int delete (dictionary *D, char *key) {
    // check if node with *key is in dictionary

    // if key exists, navigate to the node that has such key
    // remove the node from the list
    // NOTE: again, this is same logic as in deleting a node
    // but do NOT use delete method from List.c
    int present = 0;
    for (int x = 0; x < D->slots; x++) {
        if (D->hash_table[x].key == key) {
            present = 1;
            D->hash_table[x].prev->next = D->hash_table[x].next;
            D->hash_table[x].next->prev = D->hash_table[x].prev;
            D->size--;
            return 0;
        }
    }
    return -1;
}

// -------------------------------
// TODO: implement find
// find( D, k ) -- returns pointer to node whose key is *k from dictionary *D.
// If *k is not found in *D, then return NULL.
// -------------------------------

node_t *find(dictionary *D, char *k) {
    // hash key to get index and then loop over the list at that index
    // to find node with same key
    // NOTE: you can use the findList method from List.c but need to
    // distinguish between the case when it returns the node with key
    // or just the sentinel head of the list at that index of the dict

    int index = hash(k, D->slots);
    node_t *head = &(D->hash_table[index]);

    while (head != NULL) {
        if (strcmp(head->key, k) == 0) {
            break;
        } else {
            head = head->next;
        }
    }
    //printf("No %s in the index %d\n", k, index);
    return head;
}

// -------------------------------
// TODO: implement print
// print( dictionary *D ) -- prints the dictionary.
// Specifically, it looks at the non-empty slots of the hash table,
// and prints the key field of each node in the list.
// -------------------------------

void print(dictionary *D) {
    for (int x = 0; x < D->slots; x++) {
        if (D->hash_table[x].value != NULL) {
            printf("%s\n", D->hash_table[x].key);
        }
    }
}
