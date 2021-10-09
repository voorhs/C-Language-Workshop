typedef double Matrix;

Matrix** read_matrix(int row_count, int col_count);

void print_matrix(Matrix**, int row_count, int col_count);

void free_matrix(Matrix**, int row_count, int col_count);

Matrix** sum(Matrix** first, Matrix** second, int row_count, int col_count);

Matrix** scalar_prod(double scalar, Matrix**, int row_count, int col_count);

Matrix** dot(Matrix** first, Matrix** second, int first_row_count, int second_row_count, int second_col_count);

int max_in_col(Matrix**, int column_index, int row_count);

Matrix** copy(Matrix**, int row_count, int col_count);

Matrix** triangulation(Matrix**, int row_count, int *swap_count);

Matrix det(Matrix**, int row_count);