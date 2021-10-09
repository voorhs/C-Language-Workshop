#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define M 2
#define N 4
#define K 3

int main() {
    // вводим первую матрицу
    printf("Введите матрицу A размера %d*%d:\n", M, N);
    Matrix **A = read_matrix(M, N);

    // выводим матрицу
    print_matrix("\nМатрица A:\n", A, M, N);

    // вводим вторую матрицу
    printf("Введите матрицу B размера %d*%d:\n", M, N);
    Matrix **B = read_matrix(M, N);

    // выводим их сумму
    print_matrix("\nСумма A+B:\n", sum(A, B, M, N), M, N);

    // вводим скаляр t
    double t;
    printf("Введите вещественное число t:");
    scanf("%lf", &t);

    // выводим tA
    print_matrix("\nМатрца tA:\n", scalar_prod(t, A, M, N), M, N);

    // вводим матрицу C
    printf("Введите матрицу C размера %d*%d:\n", N, K);
    Matrix** C = read_matrix(N, K);

    // выводим A*C
    print_matrix("\nМатрица A*C:\n", dot(A, C, M, N, K), M, K);

    // вводим квадратную матрицу D
    printf("Введите матрицу D размера %d*%d:\n", M, M);
    Matrix** D = read_matrix(M, M);

    // выводим треугольный вид D
    int *c;
    print_matrix("\nТреугольный вид D:\n", triangulation(D, M, c), M, M);

    // выводим определитель D
    printf("Детерминант D равен: %10.3lf\n\n", det(D, M));
    return 0;
}