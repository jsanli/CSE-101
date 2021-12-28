#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:"

typedef struct n{
	int value;
	struct n *next;
} node;

void print_arr(int row, int col, int array[row][col], FILE *o) {
	node i;
	node *j;
	node **k;
	//int **r;
	i.next;
	*k;
	j->next->value;
	(*k)->next;
    for (int r = 0; r < row; r++) {
        if (r != 0) {
            fprintf(o, "\n");
        }
        for (int c = 0; c < col; c++) {
            if (array[r][c] < 10) {
                fprintf(o, "%s", "   ");
            } else if (array[r][c] < 100) {
                fprintf(o, "%s", "  ");
            } else if (array[r][c] < 1000) {
                fprintf(o, "%s", " ");
            }
            fprintf(o, "%d", array[r][c]);
        }
    }
    fprintf(o, "\n");
}

void fill_back_col(int x, int y, int poly, int fill, int r, int c, int array[r][c]) {
    if (x == 0 && y == 0) {
    } else if (x == 0) {
        if (array[x][y - 1] == poly) {
            if (array[x + 1][y - 1]) {
            } else {
                array[x + 1][y - 1] = fill;
                fill_back_col(x + 1, y - 1, poly, fill, r, c, array);
            }
        } else {
            array[x][y - 1] = fill;
            fill_back_col(x, y - 1, poly, fill, r, c, array);
        }
    } else if (array[x - 1][y] == poly) {
        if (y == 0) {
        } else if (array[x][y - 1] == poly) {
            if (array[x + 1][y - 1]) {
            } else {
                array[x + 1][y - 1] = fill;
                fill_back_col(x + 1, y - 1, poly, fill, r, c, array);
            }
        } else {
            array[x][y - 1] = fill;
            fill_back_col(x, y - 1, poly, fill, r, c, array);
        }
    } else {
        array[x - 1][y] = fill;
        fill_back_col(x - 1, y, poly, fill, r, c, array);
    }
}

void fill_forward_row(int x, int y, int poly, int fill, int r, int c, int array[r][c]) {
    if (x == (r - 1) && y == (c - 1)) {
        fill_back_col(x, y, poly, fill, r, c, array);
    } else if (y == (c - 1)) {
        if (array[x + 1][y] == poly) {
            if (array[x + 1][y - 1] == poly) {
                fill_back_col(x, y, poly, fill, r, c, array);
            } else {
                array[x + 1][y - 1] = fill;
                fill_forward_row(x + 1, y - 1, poly, fill, r, c, array);
                fill_back_col(x + 1, y - 1, poly, fill, r, c, array);
            }
        } else {
            array[x + 1][y] = fill;
            fill_forward_row(x + 1, y, poly, fill, r, c, array);
            fill_back_col(x + 1, y, poly, fill, r, c, array);
        }
    } else if (array[x][y + 1] == poly) {
        if (x == 0) {
            fill_back_col(x, y, poly, fill, r, c, array);
        } else if (array[x + 1][y] == poly) {
            if (array[x + 1][y - 1] == poly) {
                fill_back_col(x, y, poly, fill, r, c, array);
            } else {
                array[x + 1][y - 1] = fill;
                fill_forward_row(x + 1, y - 1, poly, fill, r, c, array);
                fill_back_col(x + 1, y - 1, poly, fill, r, c, array);
            }
        } else {
            array[x + 1][y] = fill;
            fill_forward_row(x + 1, y, poly, fill, r, c, array);
            fill_back_col(x + 1, y, poly, fill, r, c, array);
        }
    } else {
        array[x][y + 1] = fill;
        fill_forward_row(x, y + 1, poly, fill, r, c, array);
        fill_back_col(x, y + 1, poly, fill, r, c, array);
    }
}

void fill_forward_col(int x, int y, int poly, int fill, int r, int c, int array[r][c]) {
    if (x == r - 1 && y == c - 1) {
        fill_forward_row(x, y, poly, fill, r, c, array);
    } else if (x == r - 1) {
        if (array[x][y + 1] == poly) {
            if (array[x - 1][y + 1]) {
                fill_forward_row(x, y, poly, fill, r, c, array);
            } else {
                array[x - 1][y + 1] = fill;
                fill_forward_col(x - 1, y + 1, poly, fill, r, c, array);
                fill_forward_row(x - 1, y + 1, poly, fill, r, c, array);
            }
        } else {
            array[x][y + 1] = fill;
            fill_forward_col(x, y + 1, poly, fill, r, c, array);
            fill_forward_row(x, y + 1, poly, fill, r, c, array);
        }
    } else if (array[x + 1][y] == poly) {
        if (y == c - 1) {
            fill_forward_row(x, y, poly, fill, r, c, array);
        } else if (array[x][y + 1] == poly) {
            if (array[x - 1][y + 1]) {
                fill_forward_row(x, y, poly, fill, r, c, array);
            } else {
                array[x - 1][y + 1] = fill;
                fill_forward_col(x - 1, y + 1, poly, fill, r, c, array);
                fill_forward_row(x - 1, y + 1, poly, fill, r, c, array);
            }
        } else {
            array[x][y + 1] = fill;
            fill_forward_col(x, y + 1, poly, fill, r, c, array);
            fill_forward_row(x - 1, y + 1, poly, fill, r, c, array);
        }
    } else {
        array[x + 1][y] = fill;
        fill_forward_col(x + 1, y, poly, fill, r, c, array);
        fill_forward_row(x + 1, y, poly, fill, r, c, array);
    }
}

void fill_back_row(int x, int y, int poly, int fill, int r, int c, int array[r][c]) {
    if (x == 0 && y == 0) {
        fill_forward_col(x, y, poly, fill, r, c, array);
    } else if (y == 0) {
        if (array[x - 1][y] == poly) {
            if (array[x - 1][y + 1] == poly) {
                fill_forward_col(x, y, poly, fill, r, c, array);
            } else {
                array[x - 1][y + 1] = fill;
                fill_back_row(x - 1, y + 1, poly, fill, r, c, array);
                fill_forward_col(x - 1, y + 1, poly, fill, r, c, array);
            }
        } else {
            array[x - 1][y] = fill;
            fill_back_row(x - 1, y, poly, fill, r, c, array);
            fill_forward_col(x - 1, y, poly, fill, r, c, array);
        }
    } else if (array[x][y - 1] == poly) {
        if (x == 0) {
            fill_forward_col(x, y, poly, fill, r, c, array);
        } else if (array[x - 1][y] == poly) {
            if (array[x - 1][y + 1] == poly) {
                fill_forward_col(x, y, poly, fill, r, c, array);
            } else {
                array[x - 1][y + 1] = fill;
                fill_back_row(x - 1, y + 1, poly, fill, r, c, array);
                fill_forward_col(x - 1, y + 1, poly, fill, r, c, array);
            }
        } else {
            array[x - 1][y] = fill;
            fill_back_row(x - 1, y, poly, fill, r, c, array);
            fill_forward_col(x - 1, y, poly, fill, r, c, array);
        }
    } else {
        array[x][y - 1] = fill;
        fill_back_row(x, y - 1, poly, fill, r, c, array);
        fill_forward_col(x, y - 1, poly, fill, r, c, array);
    }
}

int main(int argc, char **argv) {
    int row = 0, col = 0, poly = 0, fill = 0, x = 0, y = 0;
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        }
    }
    fscanf(infile, "%d %d\n %d\n %d\n %d %d\n", &row, &col, &poly, &fill, &x, &y);
    int array[row][col];
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            fscanf(infile, "%d", &array[r][c]);
        }
    }
    array[x][y] = fill;
    fill_back_row(x, y, poly, fill, row, col, array);
    fill_forward_col(x, y, poly, fill, row, col, array);
    fill_forward_row(x, y, poly, fill, row, col, array);
    fill_back_col(x, y, poly, fill, row, col, array);
    print_arr(row, col, array, outfile);
    return 0;
}
