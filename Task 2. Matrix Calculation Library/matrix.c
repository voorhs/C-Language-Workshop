#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "matrix.h"

Matrix** read_matrix(int m, int n) {
    Matrix** a = malloc(sizeof(Matrix*) * m);
    
    int i, j, read_err = 0;

    for (i = 0; i < m && !read_err; i++) {
        a[i] = malloc(sizeof(Matrix) * n);

        for (j = 0; j < n && !read_err; j++) {
            if (scanf("%lf", a[i] + j) == 0)
                read_err = 1;
        }
    }
    if (read_err) {
        for (i = 0; i < m; i++)
            free(a[i]);
        free(a);
        printf("ops");
        exit(1);
    }
    return a;
    
}

void print_matrix(Matrix** a, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            printf("%lf ", a[i][j]);
        printf("\n");
    }
}

void free_matrix(Matrix** a, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        free(a[i]);
    }
    free(a);
}

Matrix** sum(Matrix** a, Matrix** b, int m, int n) {
    Matrix** c = malloc(sizeof(Matrix*) * m);

    int i, j;

    for (i = 0; i < m; i++) {
        c[i] = malloc(sizeof(Matrix) * n);

        for (j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
    }
    
    return c;
}

Matrix** scalar_prod(double num, Matrix** a, int m, int n)  {
    Matrix** c = malloc(sizeof(Matrix*) * m);

    int i, j;

    for (i = 0; i < m; i++) {
        c[i] = malloc(sizeof(Matrix) * n);

        for (j = 0; j < n; j++)
            c[i][j] = num * a[i][j];
    }

    return c;
}

Matrix** dot(Matrix** a, Matrix** b, int m, int n, int k) {
    Matrix** c = malloc(sizeof(Matrix*) * m);

    int i, j, r;

    for (i = 0; i < m; i++) {
        c[i] = malloc(sizeof(Matrix) * k);
        for (j = 0; j < k; j++) {
            c[i][j] = 0;
            for (r = 0; r < n; r++)
                c[i][j] += a[i][r] * b[r][j];
        }
    }

    return c;
}