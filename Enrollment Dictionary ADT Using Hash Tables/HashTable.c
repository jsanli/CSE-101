// -------------------------------
// Operations supporting hash tables
// -------------------------------

#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>

// -------------------------------
// Converts a 5 letter key into an integer
// CC###: ascii equivalent of letters and digits are simply added together.
// #####: ascii equivalent of digits are simply added together.
// -------------------------------
int convert(char key[5]) {
    int total = 0;
    for (int x = 0; x < 5; x++) {
        total += (int) (key[x]);
    }
    return total;
}

// -------------------------------
// Hash function that returns an index into the hash table given a key
// use the module formula on page 263 of CLRS.
// -------------------------------
int hash(char key[5], int slots) {
    return convert(key) % slots;
}
