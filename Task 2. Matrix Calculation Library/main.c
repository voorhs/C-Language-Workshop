#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

const int rows_1 = 2;     // размеры тестовых матриц
const int columns_1 = 4;     // нужны только для демонстрации
const int rows_2 = columns_1;
const int columns_2 = 3;     // работы библиотеки "matrix.h"

int main() {
/*
    РАБОТА В "matrix.h": более детальная документация в REDME.md
    array_1, array_2, array_3, array_4 -- матрицы
*/
    // вводим матрицу array_1
    printf("Введите матрицу array_1 размера %d*%d:\n", rows_1, columns_1);
    Matrix **array_1 = read_matrix(rows_1, columns_1);

    // выводим матрицу array_1
    print_matrix("\nМатрица array_1:\n", array_1, rows_1, columns_1);

    // вводим матрицу array_2
    printf("Введите матрицу array_2 размера %d*%d:\n", rows_1, columns_1);
    Matrix **array_2 = read_matrix(rows_1, columns_1);

    // выводим сумму array_1 + array_2
    print_matrix("\nСумма array_1+array_2:\n", sum(array_1, array_2, rows_1, columns_1), rows_1, columns_1);

    // вводим скаляр scalar
    double scalar;
    printf("Введите вещественное число t:");
    scanf("%lf", &scalar);

    // скалярное произведение scalar * array_1
    print_matrix("\nМатрца tarray_1:\n", scalar_prod(scalar, array_1, rows_1, columns_1), rows_1, columns_1);

    // вводим матрицу array_3
    printf("Введите матрицу array_3 размера %d*%d:\n", columns_1, columns_2);
    Matrix** array_3 = read_matrix(columns_1, columns_2);

    // выводим матричное произведение array_1*array_3
    print_matrix("\nМатрица array_1*array_3:\n", dot(array_1, array_3, rows_1, columns_1, columns_2), rows_1, columns_2);

    // вводим квадратную матрицу array_4
    printf("Введите матрицу array_4 размера %d*%d:\n", rows_1, rows_1);
    Matrix** array_4 = read_matrix(rows_1, rows_1);

    // треугольный вид array_4
    int tmp;   // tmp для служебной информации
    print_matrix("\nТреугольный вид array_4:\n", triangulation(array_4, rows_1, &tmp), rows_1, rows_1);

    // определитель array_4
    printf("Детерминант array_4 равен: %10.3lf\n\n", determinant(array_4, rows_1));
    return 0;
}