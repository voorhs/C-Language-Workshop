#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define M 2
#define N 2
#define K 3

int main() {
    Matrix **m = read_matrix(M, N);
    print_matrix(m, M, N);
    Matrix **p = read_matrix(N, K);
    print_matrix(p, N, K);
    print_matrix(dot(m, p, M, N, K), M, K);
    return 0;
}