#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>

int main (void){
	char one;
	char two;
	char three;
	char four;
	char five;
	fscanf(stdin, "%c %c %c %c %c", &one, &two, &three, &four, &five);
	char array[] = {one, two, three, four, five};
	printf("%d\n", convert(array));
}
     
