#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

Matrix** read_matrix(int  rows_count, int  columns_count) {
    Matrix** array = malloc(sizeof(Matrix*) *  rows_count);
    
    int i, j, read_err = 0;

    for (i = 0; i <  rows_count && !read_err; i++) {
       array[i] = malloc(sizeof(Matrix) *  columns_count);
        for (j = 0; j <  columns_count && !read_err; j++) {
            if (scanf("%lf", array[i] + j) == 0)
                read_err = 1;
        }
    }
    if (read_err) {
        for (i = 0; i <  rows_count; i++)
            free(array[i]);
        free(array);
        printf("Ops! Something's wrong :|\n");
        exit(1);
    }
    return array;
    
}

void print_matrix(char* message, Matrix** array, int  rows_count, int  columns_count) {
    printf("%s", message);
    int i, j;
    for (i = 0; i <  rows_count; i++) {
        for (j = 0; j <  columns_count; j++)
            printf("%10.3lf ", array[i][j]);
        printf("\n");
    }
    printf("\n");
}

void free_matrix(Matrix** array, int  rows_count) {
    int i, j;
    for (i = 0; i <  rows_count; i++) {
        free(array[i]);
    }
    free(array);
}

Matrix** sum(Matrix** array_1, Matrix** array_2, int  rows_count, int  columns_count) {
    Matrix** result = malloc(sizeof(Matrix*) *  rows_count);

    int i, j;

    for (i = 0; i <  rows_count; i++) {
        result[i] = malloc(sizeof(Matrix) *  columns_count);

        for (j = 0; j <  columns_count; j++)
            result[i][j] = array_1[i][j] + array_2[i][j];
    }

    return result;
}

Matrix** scalar_prod(double scalar, Matrix** array, int  rows_count, int  columns_count)  {
    Matrix** result = malloc(sizeof(Matrix*) *  rows_count);

    int i, j;

    for (i = 0; i <  rows_count; i++) {
        result[i] = malloc(sizeof(Matrix) *  columns_count);

        for (j = 0; j <  columns_count; j++)
            result[i][j] = scalar * array[i][j];
    }

    return result;
}

Matrix** dot(Matrix** array_1, Matrix** array_2, int  rows_count_1, int  rows_count_2, int  columns_count_2) {
    Matrix** result = malloc(sizeof(Matrix*) *  rows_count_1);

    int i, j, r;

    for (i = 0; i <  rows_count_1; i++) {
        result[i] = malloc(sizeof(Matrix) *  columns_count_2);
        for (j = 0; j <  columns_count_2; j++) {
            result[i][j] = 0;
            for (r = 0; r <  rows_count_2; r++)
                result[i][j] += array_1[i][r] * array_2[r][j];
        }
    }

    return result;
}

int max_in_column(Matrix** array, int column, int  columns_count) {
    int result = column;
    int i;
    for (i = column + 1; i <  columns_count; i++)
        if (fabs(array[i][column]) > fabs(array[result][column]))
            result = i;
    return result;
}

Matrix** copy(Matrix** array, int  rows_count, int  columns_count) {
    Matrix** result = malloc(sizeof(Matrix*) *  rows_count);
    int i, j;
    for (i = 0; i <  rows_count; i++) {
        result[i] = malloc(sizeof(Matrix) *  columns_count);
        for (j = 0; j <  columns_count; j++)
            result[i][j] = array[i][j];
    }
    return result;
}

Matrix** triangulation(Matrix** array, int  columns_count, int *swaps) {
    Matrix** result = copy(array,  columns_count,  columns_count);
    int i, zero_det_flag = 0, swap_count = 0;
    for (i = 0; i <  columns_count - 1; i++) {
        int imax = max_in_column(result, i,  columns_count);
        if (result[imax][i] == 0) {
            zero_det_flag = 1;
            continue;
        }
        if (i != imax) {
            Matrix* tmp;
            tmp = result[i];
            result[i] = result[imax];
            result[imax] = tmp;
            swap_count++;
        }
        for (int j = i + 1; j <  columns_count; j++) {
            Matrix mul = result[j][i] / result[i][i];
            for (int k = i; k <  columns_count; k++) {
                result[j][k] -= result[i][k] * mul;
            }
        }
    }
    *swaps = swap_count;
    if (zero_det_flag)
        *swaps = -1;
    return result;
}

Matrix determinant(Matrix** array, int  columns_count) {
    int swap_count;
    Matrix** triangle = triangulation(array,  columns_count, &swap_count);
    Matrix result = 1;
    if (swap_count == -1)
        return 0;
    if (swap_count % 2 == 1)
        result = -1;
    int i;
    for (i = 0; i <  columns_count; i++)
        result *= triangle[i][i];
    free_matrix(triangle,  columns_count);
  return result;
}