typedef double Matrix;

Matrix** read_matrix(int m, int n);

void print_matrix(Matrix**, int, int);

void free_matrix(Matrix**, int, int);

Matrix** sum(Matrix**, Matrix**, int, int);

Matrix** scalar_prod(double, Matrix**, int, int);

Matrix** dot(Matrix**, Matrix**, int, int, int);