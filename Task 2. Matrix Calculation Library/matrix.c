#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

Matrix** read_matrix(int m, int n) {
    Matrix** a = malloc(sizeof(Matrix*) * m);
    int i, j;
    for (i = 0; i < m; i++) {
        a[i] = malloc(sizeof(Matrix) * n);
        for (j = 0; j < n; j++) {
            scanf("%lf", a[i] + j);
        }
    }
    return a;
}