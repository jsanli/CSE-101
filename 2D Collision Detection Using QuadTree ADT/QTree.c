//--------------------------------
// Your quadtree ADT implementation
//--------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "QTree.h"
#include <math.h>
#include <assert.h>


// Definitions of helper funcitons---------------------------------------------
// Some useful helper functions that can be used to finish this program (not mandatory to use)
// Feel free to add more if needed
point getCenter(point tl, point br);
int isSamePoint(point p1, point p2);
int getIndexOfChild(point p, point tl, point br);

// Constructors-Destructors ---------------------------------------------------
point createPoint(int x, int y) {
	point p = (point)malloc(sizeof(pointObj));
	p->x = x;
	p->y = y;
	return p;
}

// Return a new point which contains the same coordinate as point q
point copyPoint(point q) {
	point p = (point)malloc(sizeof(pointObj));
	p->x = q->x;
	p->y = q->y;
	return p;
}

pointsContainer createPointsContainer() {
    pointsContainer pc = (pointsContainer) malloc(sizeof(pointsContainerObj));
    memset(pc, 0, sizeof(pointsContainerObj));
    pc->size = 0;
    pc->topLeft = NULL;
    pc->botRight = NULL;
    pc->target = NULL;
    return pc;
}

void freePointsContainer(pointsContainer* pc_ptr) {
    if (pc_ptr && *pc_ptr) {
        pointsContainer pc = *pc_ptr;
        for (int i = 0; i < pc->size; i++) 
            free(pc->list[i]);
        free(pc->topLeft);
        free(pc->botRight);
        free(pc->target);
        free(pc->list);
        free(pc);
        pc = NULL;
        *pc_ptr = NULL;
    }
}

quadNode createQuadTree(point topLeft, point botRight) {
	quadNode q = (quadNode) malloc(sizeof(quadNodeObj));
	q->count = 0;
	q->topLeft = topLeft;
	q->botRight = botRight;
	q->node = NULL;
	quadNode *children = (quadNode *)malloc(4 * sizeof(quadNodeObj));
	q->child = children;
	q->child[0] = NULL;
	q->child[1] = NULL;
	q->child[2] = NULL;
	q->child[3] = NULL;
	return q;
}

void deleteQuadTree(quadNode* pRoot) {
	if((*pRoot)->child[0] == NULL && (*pRoot)->child[1] == NULL&& (*pRoot)->child[2] == NULL&& (*pRoot)->child[3] == NULL){
		//free(*pRoot);
		*pRoot = NULL;
	}/*else{
		if((*pRoot)->child[0] != NULL){
			deleteQuadTree(&(*pRoot)->child[0]);
			free((*pRoot)->child[0]);
			(*pRoot)->child[0] = NULL;
		}
		if((*pRoot)->child[1] != NULL){
			deleteQuadTree(&(*pRoot)->child[1]);
			free((*pRoot)->child[1]);
			(*pRoot)->child[1] = NULL;
		}
		if((*pRoot)->child[2] != NULL){
			deleteQuadTree(&(*pRoot)->child[2]);
			free((*pRoot)->child[2]);
			(*pRoot)->child[2] = NULL;
		}
		if((*pRoot)->child[3] != NULL){
			deleteQuadTree(&(*pRoot)->child[3]);
			free((*pRoot)->child[3]);
			(*pRoot)->child[3] = NULL;
		}
	}*/
    
}

//Helper Functions Made by Me

point * appendList(point list[], point p){
	int x = 0;
	while(list[x] != NULL){
		x++;
	}
	list[x] = copyPoint(p);
	return list;
} 

void getPoints(quadNode root, pointsContainer p){
	if(root != NULL){
		if(root->node != NULL){
			p->list[p->size++] = copyPoint(root->node);
		}
		else{
			if(root->child[0] != NULL){
				getPoints(root->child[0], p); 
			}
			if(root->child[1] != NULL){
				getPoints(root->child[1], p); 
			}
			if(root->child[2] != NULL){
				getPoints(root->child[2], p); 
			}
			if(root->child[3] != NULL){
				getPoints(root->child[3], p); 
			}
		}
	}
	return;
	
}

int square(int x){
	return x*x;
}

int onlyChild(quadNode root){
	int counter = 0;
	int counterTwo = 0;
	int i = -1;
	for(int x = 0; x < 4; x++){
		if(root->child[x] != NULL){
			counterTwo++;
			if(root->child[x]->node != NULL){
				counter++;
				i = x;
			}
		}

	}
	if(counter == 1 && counterTwo == 1){
		return i;
	}else{
		return -1;
	}
}

//end of helper functions made by me

// Insert point p into the quadtree. If p is already in the quadtree, do nothing
void insertPoint(quadNode root, point p) {
	if(root->node == NULL && root->child[0] == NULL && root->child[1] == NULL&& root->child[2] == NULL&& root->child[3] == NULL){
		root->node = p;
		root->count++;
	}
	if(root->node != NULL){
		if(isSamePoint(root->node, p)){
			return;
		}
	}
	int i = getIndexOfChild(p, root->topLeft, root->botRight);
	if(root->child[i] == NULL){
		point c = getCenter(root->topLeft, root->botRight);
		if(i == 0){
			root->child[i] = createQuadTree(root->topLeft, c);
			root->count++;
		}
		if(i == 1){
			root->child[i] = createQuadTree(createPoint(root->topLeft->x, root->botRight->y/2 + 1 ), createPoint(c->x, root->botRight->y));
			root->count++;
		}
		if(i == 2){
			root->child[i] = createQuadTree(createPoint(root->botRight->x/2 +1, root->topLeft->y), createPoint(root->botRight->x, c->y));
			root->count++;
		} 
		if(i == 3){
			root->child[i] = createQuadTree(createPoint(1 + c->x, 1 + c->y), root->botRight);
			root->count++;
		} 
		root->child[i]->node = p;
		root->child[i]->count++;
	}
	else{
		insertPoint(root->child[i], p);
		root->count++;
	}
	if(root->node !=NULL){
		point temp = root->node;
		root->node = NULL;
		root->count--;
		insertPoint(root, temp);
	}
}

// Delete the point from the quadtree
// Return 1 if point p is in the quadtree, otherwise return 0
int deletePoint(quadNode root, point p) {
	if(root != NULL){
		if(root->node!=NULL){
			if(isSamePoint(root->node, p)){
				return 1;
			}
		}
		if(root->node == NULL){
			if(root->child[0] != NULL){
				if(deletePoint(root->child[0],p)){
					if(root->child[0]->node != NULL){
						if(isSamePoint(root->child[0]->node, p)){
							deleteQuadTree(&(root)->child[0]);
							root->child[0] = NULL;
							root->count--;
						}
						if(onlyChild(root) >= 0){
							root->node = root->child[onlyChild(root)]->node;
							deleteQuadTree(&(root)->child[onlyChild(root)]);
							root->child[onlyChild(root)] = NULL;
						}
					}
						
					return 1;
				}
			}
			if(root->child[1] != NULL){
				if(deletePoint(root->child[1],p)){
					if(root->child[1]->node != NULL){
						if(isSamePoint(root->child[1]->node, p)){
							deleteQuadTree(&(root)->child[1]);
							root->child[1] = NULL;
							root->count--;
						}
						if(onlyChild(root) >= 0){
							root->node = root->child[onlyChild(root)]->node;
							deleteQuadTree(&(root)->child[onlyChild(root)]);
							root->child[onlyChild(root)] = NULL;
						}
					}
						
					return 1;
				}
			}
			if(root->child[2] != NULL){
				if(deletePoint(root->child[2],p)){
					if(root->child[2]->node != NULL){
						if(isSamePoint(root->child[2]->node, p)){
							deleteQuadTree(&(root)->child[2]);
							root->child[2] = NULL;
							root->count--;
						}
						if(onlyChild(root) >= 0){
							root->node = root->child[onlyChild(root)]->node;
							deleteQuadTree(&(root)->child[onlyChild(root)]);
							root->child[onlyChild(root)] = NULL;
						}
					}
						
					return 1;
				}
			}
			if(root->child[3] != NULL){
				if(deletePoint(root->child[3],p)){
					if(root->child[3]->node != NULL){
						if(isSamePoint(root->child[3]->node, p)){
							deleteQuadTree(&(root)->child[3]);
							root->child[3] = NULL;
							root->count--;
						}
						if(onlyChild(root) >= 0){
							root->node = root->child[onlyChild(root)]->node;
							deleteQuadTree(&(root)->child[onlyChild(root)]);
							root->child[onlyChild(root)] = NULL;
						}
					}
						
					return 1;
				}
			}
		}
	}
	return 0;
}

// Get all points in the quadtree
// Return a container that contains all points in the quadtree
pointsContainer getAllPoints(quadNode root) {
	pointsContainer p = createPointsContainer();
	p->topLeft = copyPoint(root->topLeft);
	p->botRight = copyPoint(root->botRight);
	p->list = (point *)malloc(root->count * sizeof(pointObj));
	getPoints(root, p);
	return p;
}

// Get the neighbouring points of point p in 4*radius region
// Return a container that contains all neighbors of point p
pointsContainer getNeighbors(quadNode root, point p, int radius) {
	pointsContainer c = getAllPoints(root);
	pointsContainer n = createPointsContainer();
	n->list = (point *)malloc(root->count * sizeof(pointObj));
	int distance = 0;
	double distance_d = 0;
	double radius_d = (double)(radius);
	int x = p->x;
	int y = p->y;
	for(int z = 0; z < c->size; z++){
		if(c->list[z] != NULL){
			distance = square(c->list[z]->x - x) + square(c->list[z]->y - y);
			distance_d = sqrt((double)(distance));
			if(distance_d < 4.0*radius_d){
				n->list[n->size++] = copyPoint(c->list[z]);
			}
		}
	}
	n->topLeft = copyPoint(root->topLeft);
	n->botRight = copyPoint(root->botRight);
	return n;
}

void printPoint(point p) {
    if (p)
        printf("(%d,%d)", p->x, p->y);
}

void displayQuadTree(quadNode root) {
    assert(root);

    printf("[");
    printPoint(root->topLeft);
    printf(", ");
    printPoint(root->botRight);
    printf(", ");
    if (root->node) {
        printPoint(root->node);
    } else {
        for (int i = 0; i < 4; i++) {
            if (root->child[i]) {
                displayQuadTree(root->child[i]);
                printf(", ");
            }
            else
                printf("[], ");
        }
    }
    printf("]");
}

// Helper functions
// Get the center point within a region
point getCenter(point tl, point br) {
    int mid_x = (int) (br->x + tl->x)/2;
    int mid_y = (int) (br->y + tl->y)/2;
    return createPoint(mid_x, mid_y);
}

// Check if two points are the same
int isSamePoint(point p1, point p2) {
    return (p1->x == p2->x) && (p1->y == p2->y);
}

// Get the index of the child node
int getIndexOfChild(point p, point tl, point br) {
    point center = getCenter(tl, br);
    int res = -1;
    if (p->y <= center->y) {
        if (p->x  <= center->x) {
        // NW
            res = 0;
        } else {
        // SW
            res = 2;
        }
    } else {
        if (p->x  <= center->x) {
        // NE
            res = 1;
        } else {
        // SE
            res = 3;
        }
    }
    free(center);
    return res;
}

	

	
	
	

