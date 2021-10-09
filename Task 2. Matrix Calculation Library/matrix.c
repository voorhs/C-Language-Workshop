#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

#define sp "%lf"
#define sp_ "%10.3lf "

Matrix** read_matrix(int m, int n) {
    Matrix** a = malloc(sizeof(Matrix*) * m);
    
    int i, j, read_err = 0;

    for (i = 0; i < m && !read_err; i++) {
        a[i] = malloc(sizeof(Matrix) * n);

        for (j = 0; j < n && !read_err; j++) {
            if (scanf(sp, a[i] + j) == 0)
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
            printf(sp_, a[i][j]);
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

int max_in_col(Matrix **m, int col, int n) {
    int res = col;
    int i;
    for (i = col + 1; i < n; i++)
    if (fabs(m[i][col]) > fabs(m[res][col]))
        res = i;
    return res;
}

Matrix** copy(Matrix** a, int m, int n) {
    Matrix** p = malloc(sizeof(Matrix*) * m);
    int i, j;
    for (i = 0; i < m; i++) {
        p[i] = malloc(sizeof(Matrix) * n);
        for (j = 0; j < n; j++)
            p[i][j] = a[i][j];
    }
    return p;
}

Matrix** triangulation(Matrix** a, int n, int *swaps) {
    Matrix** m = copy(a, n, n);
    int i, zero_det_flag = 0, swap_count = 0;
    for (i = 0; i < n - 1; i++) {
        int imax = max_in_col(m, i, n);
        if (m[imax][i] == 0) {
            zero_det_flag = 1;
            continue;
        }
        if (i != imax) {
            Matrix* tmp;
            tmp = m[i];
            m[i] = m[imax];
            m[imax] = tmp;
            swap_count++;
        }
        for (int j = i + 1; j < n; j++) {
            Matrix mul = m[j][i] / m[i][i];
            for (int k = i; k < n; k++) {
                m[j][k] -= m[i][k] * mul;
            }
        }
    }
    *swaps = swap_count;
    if (zero_det_flag)
        *swaps = -1;
    return m;
}

Matrix det(Matrix** m, int n) {
    int swap_count;
    Matrix** a = triangulation(m, n, &swap_count);
    Matrix d = 1;
    if (swap_count == -1)
        return 0;
    if (swap_count % 2 == 1)
        d = -1;
    int i;
    for (i = 0; i < n; i++)
        d *= a[i][i];
    free_matrix(a, n, n);
  return d;
}