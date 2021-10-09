#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define M 2
#define N 2

int main() {
    Matrix **m = read_matrix(M, N);
    print_matrix(m, M, N);
    Matrix **p = read_matrix(M, N);
    print_matrix(p, M, N);
    Matrix **c = sum(m, p, M, N);
    print_matrix(c, M, N);
    return 0;
}