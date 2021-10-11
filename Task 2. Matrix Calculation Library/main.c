#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define M 2     // размеры тестовых матриц
#define N 4     // нужны только для демонстрации
#define K 3     // работы библиотеки "matrix.h"

int main() {
/*
    РАБОТА В "matrix.h": более детальная документация в README.md
    A, B, C, D -- матрицы
*/
    // вводим матрицу A
    printf("Введите матрицу A размера %d*%d:\n", M, N);
    Matrix **A = read_matrix(M, N);

    // выводим матрицу A
    print_matrix("\nМатрица A:\n", A, M, N);

    // вводим матрицу B
    printf("Введите матрицу B размера %d*%d:\n", M, N);
    Matrix **B = read_matrix(M, N);

    // выводим сумму A + B
    print_matrix("\nСумма A+B:\n", sum(A, B, M, N), M, N);

    // вводим скаляр scalar
    double scalar;
    printf("Введите вещественное число t:");
    scanf("%lf", &scalar);

    // скалярное произведение scalar * A
    print_matrix("\nМатрца tA:\n", scalar_prod(scalar, A, M, N), M, N);

    // вводим матрицу C
    printf("Введите матрицу C размера %d*%d:\n", N, K);
    Matrix** C = read_matrix(N, K);

    // выводим матричное произведение A*C
    print_matrix("\nМатрица A*C:\n", dot(A, C, M, N, K), M, K);

    // вводим квадратную матрицу D
    printf("Введите матрицу D размера %d*%d:\n", M, M);
    Matrix** D = read_matrix(M, M);

    // треугольный вид D
    int *tmp;   // tmp для служебной информации
    print_matrix("\nТреугольный вид D:\n", triangulation(D, M, tmp), M, M);

    // определитель D
    printf("Детерминант D равен: %10.3lf\n\n", det(D, M));
    return 0;
}