typedef double Matrix;

Matrix** read_matrix(int row_count, int col_count);
/*  
    вводит матрицу row_count * col_count из стандартного потока
    разделители между элементами: ' ' и '\n'
    разделители между строками: ' ' и '\n'
*/

void print_matrix(char* msg, Matrix**, int row_count, int col_count);
/*  
    выводит сообщение msg
    выводит матрицу row_count * col_count в стандартный поток
    под вывод каждого числа отводится 10 пробелов
    каждое число выводится с 3 знаками после запятой
    разделители между строками: '\n'
*/

void free_matrix(Matrix**, int row_count, int col_count);
/*  очищает память из под матрицы row_count * col_count  */

Matrix** sum(Matrix** first, Matrix** second, int row_count, int col_count);
/*  возвращает сумму матриц размера row_count * col_count
    сами матрицы не меняются
*/

Matrix** scalar_prod(double scalar, Matrix**, int row_count, int col_count);
/*  возвращает матрицу row_count * col_count, умноженную на scalar
    сама матрица не меняется
*/

Matrix** dot(Matrix** first, Matrix** second, int first_row_count, int second_row_count, int second_col_count);
/*  возвращает произведение матрицы
    first размера first_row_count * second_row_count
    и матрицы second размера second_row_count * second_col_count
    сами матрицы не меняются
*/

Matrix** copy(Matrix**, int row_count, int col_count);
/*  возвращает копию матрицы row_count * col_count  */

Matrix** triangulation(Matrix**, int row_count, int *swap_count);
/*  возвращает треугольный вид квадратной матрицы row_count * row_count
    сама матрица не меняется
    в переменную swap_count записывается число перестановок строк,
    произведённое в процессе триангуляции
    swap_count = -1, если встретились нулевые столбцы
*/

Matrix det(Matrix**, int row_count);
/*  возвращает значение определителя квадратной матрицы row_count * row_count   */