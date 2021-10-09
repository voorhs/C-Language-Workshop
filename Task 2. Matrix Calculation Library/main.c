#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define M 4
#define N 4
#define K 3

int main() {
    Matrix **m = read_matrix(M, M), x;
    printf("%10.3lf\n", det(m, M));
    print_matrix(m, M, M);
    return 0;
}