#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "QTree.h"

// Destroy all points inside the explosion range in quadtree.
// The explosion range is 4*radius starting from the center of all collision dots
// [Return] number of points have been deleted from the quadtree due to the explosions
int explosion(quadNode Q, pointsContainer ap, int radius) {
	int distance = 0;
	double distance_d = 0.0;
	//pointsContainer alist = createPointsContainer();
	//blist->list = (point *)malloc(Q->count * sizeof(pointObj));
	//alist->list = (point *)malloc(Q->count * sizeof(pointObj));
	int counter = 0;
	for(int a = 0; a < ap->size-1; a++){
		for(int b = a+1; b<ap->size; b++){
			distance = (ap->list[b]->y - ap->list[a]->y)*(ap->list[b]->y - ap->list[a]->y)+(ap->list[b]->x - ap->list[a]->x)*(ap->list[b]->x - ap->list[a]->x);
			distance_d = sqrt((double)(distance));
			if(distance_d < 2*radius){
				/*printPoint(ap->list[b]);
				printf("%s\n", "awiuehf;aweoi");
				printPoint(ap->list[a]);
				printf("%s\n", "avwiuehf;aweoi");*/
				pointsContainer blist = getNeighbors(Q, ap->list[b], radius);
				pointsContainer alist = getNeighbors(Q, ap->list[a], radius);
				for(int d = 0; d < blist->size;d++){
					if(blist->list[d] != NULL){
						if(deletePoint(Q, blist->list[d])){
							counter++;
						}
					}
				}
				for(int c = 0; c< alist->size; c++){
					if(alist->list[c] != NULL){
						if(deletePoint(Q, alist->list[c])){
							counter++;
						}
					}
				}
			}
		}
		
	}
	return counter;
}

// Check how many collision events occur in the current map
// Leverage explosion function to destroy all points in the explosion range
// [Return] the number of collision events
int collision(quadNode Q, int radius) {
	pointsContainer ap = getAllPoints(Q);
	int distance = 0;
	double distance_d = 0.0;
	int counter = 0;
	for(int a = 0; a < ap->size-1; a++){
		for(int b = a+1; b<ap->size; b++){
			distance = (ap->list[b]->y - ap->list[a]->y)*(ap->list[b]->y - ap->list[a]->y)+(ap->list[b]->x - ap->list[a]->x)*(ap->list[b]->y - ap->list[a]->x);
			distance_d = sqrt((double)(distance));
			if(distance_d < 2*radius){
				counter++;
			}
		}
	}
	return explosion(Q, ap, radius) - counter;
}

int main()
{
    char	line[100];
    char 	*command;
    int done = 0;
    
    quadNode Q = NULL;
    int size, x, y, radius, seed, numPoints;

    // process input
    while( !done ) {
        // read an entire line as a string
        fgets(line, 100, stdin);

        // pulls command code, assume comma or tab separated
        command = strtok( line, " \t" );

        if (strncmp(command, "ex", 2) == 0) {
            if (Q)
                deleteQuadTree(&Q);
            printf( "Exited Program\n" );
            done = 1;
        } else if (strncmp(command, "ct", 2) == 0) {
            size = atoi( strtok( NULL, " " ) );
            radius = atoi( strtok( NULL, " " ) );
            
            if (Q != NULL)
                deleteQuadTree(&Q);

             Q = createQuadTree(createPoint(0, 0), createPoint(size-1, size-1));
            
        } else if (strncmp(command, "ap", 2) == 0) {
            if (Q == NULL) {
                printf("Please create QuadTree first...\n");
                continue;
            }
            x = atoi( strtok( NULL, " " ) );
            y = atoi( strtok( NULL, " " ) );
            insertPoint(Q, createPoint(x, y));
        } else if (strncmp(command, "dp", 2) == 0) {
            if (Q == NULL) {
                printf("Please create QuadTree first...\n");
                continue;
            }
            x = atoi( strtok( NULL, " " ) );
            y = atoi( strtok( NULL, " " ) );
            point p = createPoint(x, y);
            deletePoint(Q, p);
		if(Q->count == 1 && p->x == Q->node -> x && p->y == Q->node -> y){
			Q->count = 0;
			Q->node = NULL;
		}
         
            free(p);	
        } else if (strncmp(command, "se", 2) == 0) {
            seed = atoi( strtok( NULL, " " ) );
            srand(seed);
        } else if (strncmp(command, "ip", 2) == 0) {
            if (Q == NULL) {
                printf("Please create QuadTree first...\n");
                continue;
            }
            numPoints = atoi( strtok( NULL, " " ) );
            for (int i = 0; i < numPoints; i++) {
                x = rand() % size;
                y = rand() % size;
                insertPoint(Q, createPoint(x, y));
            }
        } else if (strncmp(command, "gn", 2) == 0) {
            // Get neighbors of (x, y)
            if (Q == NULL) {
                printf("Please create QuadTree first...\n");
                continue;
            }
            x = atoi( strtok( NULL, " " ) );
            y = atoi( strtok( NULL, " " ) );
            point p = createPoint(x, y);
            pointsContainer pc = getNeighbors(Q, p, radius);

            // VALIDATION
             point* list = pc->list;
             for (int i = 0; i < pc->size; i++) {
                 printPoint(list[i]);
                 printf(", ");
             }
             printf("\n");

            free(p);
            freePointsContainer(&pc);
        } else if (strncmp(command, "ga", 2) == 0) {
            // Get neighbors of (x, y)
            if (Q == NULL) {
                printf("Please create QuadTree first...\n");
                continue;
            }
            pointsContainer pc = getAllPoints(Q);

            // VALIDATION
             point* list = pc->list;
             for (int i = 0; i < pc->size; i++) {
                 printPoint(list[i]);
                 printf(", ");
             }
             printf("\n");

            freePointsContainer(&pc);
		pc = NULL;
        } else if (strncmp(command, "pt", 2) == 0) {
            if (Q == NULL) {
                printf("Please create QuadTree first...\n");
                continue;
            }
            displayQuadTree(Q);
            printf("\n");
        
        } else if (strncmp(command, "co", 2) == 0) {
            if (Q == NULL) {
                printf("Please create QuadTree first...\n");
                continue;
            }
            int numCollision = collision(Q, radius);
            printf("%d collisions happened in the map!\n", numCollision);
        }
        else printf("Unrecognized command: %2s\n", command);
    }

    return 0;
}



