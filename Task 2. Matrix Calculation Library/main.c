#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define M 2
#define N 2

int main() {
    Matrix **m = read_matrix(M, N);
    if (m != NULL)
        print_matrix(m, M, N);
    else
        printf("ops\n");
    return 0;
}