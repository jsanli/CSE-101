#ifndef __PROG0_H__
#define __PROG0_H__

#include <stdbool.h>
#include <stdint.h>

void print_arr(int row,int col, int array[row][col]){
	for(int r = 0; r < row; r++){
		if(r!=0){
			printf("\n");
		}
		for(int c = 0; c < col; c++){
			if(array[r][c] < 10){
				printf("%s", "   ");
			}
			else if(array[r][c] < 100){
				printf("%s", "  ");
			}
			else if(array[r][c] < 1000){
				printf("%s", " ");
			}
			printf("%d", array[r][c]);

		}
	}
	printf("\n");
}

void fill_back_col(int x, int y, int poly, int fill, int r, int c, int array[r][c]){
	if(x == 0 && y == 0){
		print_arr(r,c,array);
	}
	else if(x == 0){
		if(array[x][y - 1] == poly){
			if(array[x +1][y-1]){
				print_arr(r,c,array);
			}
			else{
				array[x + 1][y - 1] = fill;
				fill_back_col(x + 1,y - 1,poly,fill, r, c, array);
			}
		}
		else{
			array[x][y - 1] = fill;
			fill_back_col(x,y - 1,poly,fill, r, c, array);
		}
	}
	else if(array[x - 1][y]== poly){
		if(y == 0){
			print_arr(r,c,array);
		}
		else if(array[x][y - 1] == poly){
			if(array[x + 1][y-1]){
				print_arr(r,c,array);
			}
			else{
				array[x + 1][y - 1] = fill;
				fill_back_col(x + 1,y - 1,poly,fill, r, c, array);
			}
		}
		else{	
			array[x][y - 1] = fill;
			fill_back_col(x,y - 1,poly,fill, r, c, array);
		}
	}		 
	else{
		array[x - 1][y] = fill;
		fill_back_col(x - 1,y,poly,fill, r, c, array);
	}
}

void fill_forward_row(int x, int y, int poly, int fill, int r, int c, int array[r][c]){
	if(x == r-1&& y == c-1){
		fill_back_col(x, y, poly, fill, r, c, array);
	}
	else if(y == r-1){
		if(array[x + 1][y] == poly){
			if(array[x + 1][y - 1] == poly){
				fill_back_col(x, y, poly, fill, r, c, array);
			}
			else{
				array[x + 1][y - 1] = fill;	
				fill_forward_row(x + 1,y - 1,poly,fill, r, c,array);
			}
		}
		else{
			array[x + 1][y] = fill;
			fill_forward_row(x + 1,y,poly,fill, r, c, array);
		}
	}
	else if(array[x][y + 1] == poly){
		if(x == 0){
			fill_back_col(x, y, poly, fill, r, c, array);
		}
		else if(array[x + 1][y] == poly){
			if(array[x+1][y-1] == poly){
				fill_back_col(x, y, poly, fill, r, c, array);
			}
			else{
				array[x+1][y-1] = fill;
				fill_forward_row(x+ 1,y-1,poly,fill, r, c,array);
			}
		}
		else{	
			array[x + 1][y] = fill;
			fill_forward_row(x + 1,y,poly,fill, r, c, array);
		}
	}		 
	else{
		array[x][y + 1] = fill;
		return fill_forward_row(x,y + 1,poly,fill, r, c, array);
	}
}


void fill_forward_col(int x, int y, int poly, int fill, int r, int c, int array[r][c]){
	if(x == r - 1 && y == c - 1){
		fill_forward_row(x,y,poly,fill, r, c, array);
	}
	else if(x == r-1){
		if(array[x][y + 1] == poly){
			if(array[x -1][y+1]){
				fill_forward_row(x,y,poly,fill, r, c, array);
			}
			else{
				array[x - 1][y + 1] = fill;
				fill_back_col(x - 1,y + 1,poly,fill, r, c, array);
			}
		}
		else{
			array[x][y + 1] = fill;
			fill_back_col(x,y + 1,poly,fill, r, c, array);
		}
	}
	else if(array[x + 1][y]== poly){
		if(y == c -1){
			fill_forward_row(x,y,poly,fill, r, c, array);
		}
		else if(array[x][y + 1] == poly){
			if(array[x -1][y+1]){
				fill_forward_row(x,y,poly,fill, r, c, array);
			}
			else{
				array[x - 1][y + 1] = fill;
				fill_back_col(x - 1,y + 1,poly,fill, r, c, array);
			}
		}
		else{	
			array[x][y + 1] = fill;
			fill_back_col(x,y + 1,poly,fill, r, c, array);
		}
	}		 
	else{
		array[x + 1][y] = fill;
		fill_forward_col(x + 1,y,poly,fill, r, c, array);
	}
}

void fill_back_row(int x, int y, int poly, int fill, int r, int c, int array[r][c]){
	if(x == 0 && y == 0){
		fill_forward_col(x, y, poly, fill, r, c, array);
	}
	else if(y == 0){
		if(array[x- 1][y] == poly){
			if(array[x- 1][y+1] == poly){
				fill_forward_col(x, y, poly, fill, r, c, array);
			}
			else{
				array[x- 1][y+1] = fill;	
				fill_forward_row(x- 1,y+1,poly,fill, r, c,array);
			}
		}
		else{
			array[x- 1][y] = fill;
			fill_forward_row(x- 1,y,poly,fill, r, c, array);
		}
	}
	else if(array[x][y- 1] == poly){
		if(x == 0){
			fill_forward_col(x, y, poly, fill, r, c, array);
		}
		else if(array[x- 1][y] == poly){
			if(array[x-1][y+1] == poly){
				fill_forward_col(x, y, poly, fill, r, c, array);
			}
			else{
				array[x-1][y+1] = fill;
				fill_forward_row(x- 1,y+1,poly,fill, r, c,array);
			}
		}
		else{	
			array[x- 1][y] = fill;
			fill_forward_row(x- 1,y,poly,fill, r, c, array);
		}
	}		 
	else{
		array[x][y- 1] = fill;
		return fill_back_row(x,y- 1,poly,fill, r, c, array);
	}
}

#endif
