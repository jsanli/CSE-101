#include<stdio.h>
#include"List.h"
#include"graph.h"
#include<stdlib.h>

/* TODO: implement the deferred acceptance/Gale-Shapley algorithm
- Note that we want to find the M-optimal set of stable matches
- You can write your own helper functions	
*/

void galeShapley(int n, int preferences[][n/2]){
	graph g = createGraph(n);
	int tf = 0;
	int fman = 0;
	int temp;
	int y = 0;
	for(int x = 0; x < n/2; x++){   //iterates through men
		for(y = 0; y < n/2; y++){   //iterates through each mens preferences
			for(int z =0; z< n/2; z++){
				if(hasEdge(g, z, preferences[x][y])){
					fman = z;
					tf = 1;
					z = n/2;
				}
			}
			if(tf != 1){
				addEdge(g, x, preferences[x][y]);
				temp = y;
				y = n/2;
			}else{
				for(int a = 0; a < n/2; a++){
					if(preferences[preferences[x][y]][a] == x){
						addEdge(g,x,preferences[x][y]);
						removeEdge(g, fman, preferences[x][y]);
						temp = y;
						y = n/2;
						x = fman - 1;
						a = n/2; 
					}
					else if(preferences[preferences[x][y]][a] == fman){
						a=n/2;
					}
				}
			}
			fman = 0;
			tf = 0;
		}
		y = temp;
	}
	printf("%s", "M-Optimal matches are: ");
	for(int w = 0; w < n; w++){
		for(int m = 0; m < n; m++){
			if(g->matrix[w][m] == 1){
				printf("(%d, %d) ", w, m);
			}
		}
	}
	printf("\n");
	destructGraph(g);

}





/* TODO: implement the main() function
Here, you would read in the input (from stdin) and execute deferred acceptance algorithm
and print out the set of M-optimal stable matches.
*/
int main(void)
{
	int n;
	fscanf(stdin, "%d", &n);
	int preferences [n][n/2];
	for(int r = 0; r <n; r++){
		for(int c =0; c< n/2; c++){
			fscanf(stdin, "%d", &preferences[r][c]);
		}
	}
	
	galeShapley(n, preferences);
	
	
	return 0;
}

	

