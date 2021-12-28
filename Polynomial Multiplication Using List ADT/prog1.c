/*The purpose of this lab is to sort and multiply up to two polynomials. It does this using a linked list to store data and two functions that manipulate these lists, order and multiply. One enters input and specifies an output using program arguments -i and -o*/

#include "List.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "i:o"

void order(List *l1, List *l2) {
    List l3 = newList();
    List l4 = newList();

    while (length(*l2) != 0) {
        appendList(l3, delElement(*l1, max(*l2)));
        appendList(l4, delElement(*l2, max(*l2)));
    }
    *l1 = l3;
    *l2 = l4;
}

void print(List l1, List l2, char var) {
    int co;
    int ex;
    int l = length(l1);
    for (int x = 0; x < l; x++) {
        co = delElement(l1, 0);
        ex = delElement(l2, 0);
        if (x == 0) {
            if (ex > 1) {
                if (co == 1) {
                    printf("%c%c%d ", var, '^', ex);
                } else if (co == -1) {
                    printf("%c%c%c%d ", '-', var, '^', ex);
                } else {
                    printf("%d%c%c%d ", co, var, '^', ex);
                }
            } else if (ex == 1) {
                if (co == 1) {
                    printf("%c ", var);
                } else if (co == -1) {
                    printf("%c%c ", '-', var);
                } else {
                    printf("%d%c ", co, var);
                }
            } else {
                printf("%d ", co);
            }
        } else if (co < 0) {
            if (ex > 1) {
                if (co == -1) {
                    printf("%c %c%c%d ", '-', var, '^', ex);
                } else {
                    printf("%c %d%c%c%d ", '-', co * -1, var, '^', ex);
                }
            } else if (ex == 1) {
                if (co == -1) {
                    printf("%c %c ", '-', var);

                } else {
                    printf("%c %d%c ", '-', co * -1, var);
                }
            } else {
                printf("%c %d ", '-', co * -1);
            }
        } else {
            if (ex > 1) {
                if (co == 1) {
                    printf("%c %c%c%d ", '+', var, '^', ex);
                } else {
                    printf("%c %d%c%c%d ", '+', co, var, '^', ex);
                }
            } else if (ex == 1) {
                if (co == 1) {
                    printf("%c %c ", '+', var);
                } else {
                    printf("%c %d%c ", '+', co, var);
                }
            } else {
                printf("%c %d ", '+', co);
            }
        }
    }
    printf("\n");
}

void multiply(List l1, List l2, List l3, List l4, char variable) {
    List l5 = newList();
    List l6 = newList();
    List l7 = newList();
    List l8 = newList();
    List l9 = newList();
    List l10 = newList();
    int co;
    int ex;
    int co2;
    int ex2;
    int counter = 0;
    int len = length(l1);
    int len2 = length(l3);
    for (int q = 0; q < len; q++) {
        co = delElement(l1, 0);
        ex = delElement(l2, 0);
        for (int y = 0; y < len2; y++) {
            if (counter % 2 == 0) {
                order(&l3, &l4);
                co2 = delElement(l3, 0);
                ex2 = delElement(l4, 0);
                appendList(l5, co * co2);
                appendList(l6, ex + ex2);
                appendList(l7, co * co2);
                appendList(l8, ex + ex2);
                appendList(l9, co2);
                appendList(l10, ex2);
            } else {
                order(&l9, &l10);
                co2 = delElement(l9, 0);
                ex2 = delElement(l10, 0);
                appendList(l5, co * co2);
                appendList(l6, ex + ex2);
                appendList(l7, co * co2);
                appendList(l8, ex + ex2);
                appendList(l3, co2);
                appendList(l4, ex2);
            }
        }
        counter++;
    }
    print(l5, l6, variable);
    printf("%s\n", "which simplifies to");
    int len3 = length(l7);
    int deg;
    for (int z = 0; z < len3; z++) {
        co = delElement(l7, 0);
        ex = delElement(l8, 0);
        deg = find(l6, ex);
        if (deg == -1) {
            appendList(l5, co);
            appendList(l6, ex);
        } else {
            co2 = delElement(l5, deg);
            ex2 = delElement(l6, deg);
            if (co + co2 != 0) {
                appendList(l5, co2 + co);
                appendList(l6, ex);
            }
        }
    }
    print(l5, l6, variable);
}

int main(int argc, char **argv) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        }
    }
    char str[30] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    int cototal = 0;
    int extotal = 0;
    List l1 = newList();
    List l2 = newList();
    List l3 = newList();
    List l4 = newList();
    List l5 = newList();
    List l6 = newList();
    List l7 = newList();
    List l8 = newList();
    int exponent = -1;
    int var = -1;
    char variable;
    int negative = -1;
    int lines = 0;
    while (fgets(str, 30, infile) != NULL) {
        lines++;
        if (lines == 1) {
            for (int x = 0; x < 30; x++) {
                if (str[x] == '0' || str[x] == '1' || str[x] == '2' || str[x] == '3'
                    || str[x] == '4' || str[x] == '5' || str[x] == '6' || str[x] == '7'
                    || str[x] == '8' || str[x] == '9') {
                    if (exponent == -1) {
                        cototal *= 10;
                        cototal += ((int) (str[x]) - 48);
                    } else {
                        extotal *= 10;
                        extotal += ((int) (str[x]) - 48);
                    }
                } else if (str[x] == '^') {
                    exponent = 1;
                } else if (str[x] == '-') {
                    negative = 1;
                } else if (str[x] == 'a' || str[x] == 'b' || str[x] == 'c' || str[x] == 'd'
                           || str[x] == 'e' || str[x] == 'f' || str[x] == 'g' || str[x] == 'h'
                           || str[x] == 'i' || str[x] == 'j' || str[x] == 'k' || str[x] == 'l'
                           || str[x] == 'm' || str[x] == 'n' || str[x] == 'o' || str[x] == 'p'
                           || str[x] == 'q' || str[x] == 'r' || str[x] == 's' || str[x] == 't'
                           || str[x] == 'u' || str[x] == 'v' || str[x] == 'w' || str[x] == 'x'
                           || str[x] == 'y' || str[x] == 'z') {
                    var = 1;
                    variable = str[x];
                    if (x == 0) {
                        if (str[x + 1] == ' ' || strlen(str) == 2) {
                            if (negative == -1) {
                                appendList(l1, 1);
                                appendList(l5, 1);
                            } else {
                                appendList(l1, -1);
                                appendList(l5, -1);
                            }
                            appendList(l2, 1);
                            appendList(l6, 1);
                            var = -1;
                        }
                    } else if (str[x - 1] == ' ' && str[x + 1] == ' ') {
                        if (negative == -1) {
                            appendList(l1, 1);
                            appendList(l5, 1);
                        } else {
                            appendList(l1, -1);
                            appendList(l5, -1);
                        }
                        appendList(l2, 1);
                        appendList(l6, 1);
                        negative = -1;
                        var = -1;
                    } else if (str[x - 1] == '-' && str[x + 1] == ' ') {
                        appendList(l1, -1);
                        appendList(l5, -1);
                        appendList(l2, 1);
                        appendList(l6, 1);
                        negative = -1;
                        var = -1;
                    } else if (x + 2 == (int) (strlen(str))) {
                        if (negative == -1) {
                            appendList(l1, 1);
                            appendList(l5, 1);
                        } else {
                            appendList(l1, -1);
                            appendList(l5, -1);
                        }
                        appendList(l2, 1);
                        appendList(l6, 1);
                        negative = -1;
                        var = -1;
                    }

                } else if (str[x] == ' ' && (cototal != 0 || extotal != 0)) {
                    if (negative == -1) {
                        if (cototal == 0) {
                            appendList(l1, 1);
                            appendList(l5, 1);
                        } else {
                            appendList(l1, cototal);
                            appendList(l5, cototal);
                        }
                    } else {
                        if (cototal == 0) {
                            appendList(l1, -1);
                            appendList(l5, -1);
                        } else {
                            appendList(l1, cototal * -1);
                            appendList(l5, cototal * -1);
                        }
                    }
                    if (extotal == 0 && var == 1) {
                        appendList(l2, 1);
                        appendList(l6, 1);
                    } else {
                        appendList(l2, extotal);
                        appendList(l6, extotal);
                    }
                    cototal = 0;
                    extotal = 0;
                    exponent = -1;
                    var = -1;
                    negative = -1;
                }
            }
        } else {
            for (int x = 0; x < 30; x++) {
                if (str[x] == '0' || str[x] == '1' || str[x] == '2' || str[x] == '3'
                    || str[x] == '4' || str[x] == '5' || str[x] == '6' || str[x] == '7'
                    || str[x] == '8' || str[x] == '9') {
                    if (exponent == -1) {
                        cototal *= 10;
                        cototal += ((int) (str[x]) - 48);
                    } else {
                        extotal *= 10;
                        extotal += ((int) (str[x]) - 48);
                    }
                } else if (str[x] == '^') {
                    exponent = 1;
                } else if (str[x] == '-') {
                    negative = 1;
                } else if (str[x] == 'a' || str[x] == 'b' || str[x] == 'c' || str[x] == 'd'
                           || str[x] == 'e' || str[x] == 'f' || str[x] == 'g' || str[x] == 'h'
                           || str[x] == 'i' || str[x] == 'j' || str[x] == 'k' || str[x] == 'l'
                           || str[x] == 'm' || str[x] == 'n' || str[x] == 'o' || str[x] == 'p'
                           || str[x] == 'q' || str[x] == 'r' || str[x] == 's' || str[x] == 't'
                           || str[x] == 'u' || str[x] == 'v' || str[x] == 'w' || str[x] == 'x'
                           || str[x] == 'y' || str[x] == 'z') {
                    var = 1;
                    variable = str[x];
                    if (x == 0) {
                        if (str[x + 1] == ' ' || strlen(str) == 2) {
                            if (negative == -1) {
                                appendList(l3, 1);
                                appendList(l7, 1);
                            } else {
                                appendList(l3, -1);
                                appendList(l7, -1);
                            }
                            appendList(l4, 1);
                            appendList(l8, 1);
                            var = -1;
                        }
                    } else if (str[x - 1] == ' ' && str[x + 1] == ' ') {
                        if (negative == -1) {
                            appendList(l3, 1);
                            appendList(l7, 1);
                        } else {
                            appendList(l3, -1);
                            appendList(l7, -1);
                        }
                        appendList(l4, 1);
                        appendList(l8, 1);
                        negative = -1;
                        var = -1;
                    } else if (str[x - 1] == '-' && str[x + 1] == ' ') {
                        appendList(l3, -1);
                        appendList(l7, -1);
                        appendList(l4, 1);
                        appendList(l8, 1);
                        negative = -1;
                        var = -1;
                    } else if (x + 2 == (int) (strlen(str))) {
                        if (negative == -1) {
                            appendList(l3, 1);
                            appendList(l7, 1);
                        } else {
                            appendList(l3, -1);
                            appendList(l7, -1);
                        }
                        appendList(l4, 1);
                        appendList(l8, 1);
                        negative = -1;
                        var = -1;
                    }

                } else if (str[x] == ' ' && (cototal != 0 || extotal != 0)) {
                    if (negative == -1) {
                        if (cototal == 0) {
                            appendList(l3, 1);
                            appendList(l7, 1);
                        } else {
                            appendList(l3, cototal);
                            appendList(l7, cototal);
                        }
                    } else {
                        if (cototal == 0) {
                            appendList(l3, -1);
                            appendList(l7, -1);
                        } else {
                            appendList(l3, cototal * -1);
                            appendList(l7, cototal * -1);
                        }
                    }
                    if (extotal == 0 && var == 1) {
                        appendList(l4, 1);
                        appendList(l8, 1);
                    } else {
                        appendList(l4, extotal);
                        appendList(l8, extotal);
                    }
                    cototal = 0;
                    extotal = 0;
                    exponent = -1;
                    var = -1;
                    negative = -1;
                }
            }
        }
        if (lines == 1) {
            order(&l1, &l2);
            order(&l5, &l6);
            print((l1), (l2), variable);
        } else {
            order(&l3, &l4);
            order(&l7, &l8);
            printf("%s\n", "multiply by");
            print((l3), (l4), variable);
            printf("%s\n", "is");
            multiply(l5, l6, l7, l8, variable);
        }
        for (int x = 0; x < 30; x++) {
            str[x] = ' ';
        }
    }
}
