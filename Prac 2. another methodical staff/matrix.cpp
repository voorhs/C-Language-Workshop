#include <iostream>
#include "matrix.h"

Matrix::Matrix () {
    this->m = 0;
    this->n = 0;
    this->content = nullptr;
};

Matrix::Matrix(int m, int n, double value) {
    assert((m > 0) && (n > 0));
    
    this->m = m;
    this->n = n;

    this->content = new Vector[m];

    for (int i = 0; i < m; ++i)
        this->content[i].reshape(n, value);        
}

Matrix::Matrix(const Matrix& a) {
    this->m = a.m;
    this->n = a.n;

    this->content = new Vector[m];

    for (int i = 0; i < a.m; ++i) {
        this->content[i] = a[i];
    }
}

Matrix::~Matrix() {
    delete[] this->content;
}

Matrix& Matrix::operator= (const Matrix& a) {
    this->m = a.m;
    this->n = a.n;

    delete[] this->content;
    this->content = new Vector[a.m];

    for (int i = 0; i < a.m; ++i) {
        this->content[i] = a[i];
    }

    return *this;
}

double& Matrix::operator() (int a, int b) {
    assert((0 <= a) && (a < m) && (0 <= b) && (b < n));
    return this->content[a][b];
}

Vector& Matrix::operator[] (const int a) const {
    assert((0 <= a) && (a < m));
    return this->content[a];
}

Matrix Matrix::operator+ (const Matrix& a) {
    assert((this->n == a.n) && (this->m == a.m));

    Matrix temp(*this);

    for (int i = 0; i < a.m; ++i) 
        temp.content[i] += a[i];
    
    return temp;
}

Matrix Matrix::operator- (const Matrix& a) {
    assert((this->n == a.n) && (this->m == a.m));

    Matrix temp(*this);

    for (int i = 0; i < a.m; ++i) 
        temp.content[i] -= a[i];
    
    return temp;
}

Matrix Matrix::operator* (const double c) {
    Matrix temp(*this);

    for (int i = 0; i < this->m; ++i)
        temp.content[i] *= c;
    
    return temp;
}

std::ostream& operator<< (std::ostream& os, const Matrix& v) {
    for (int i = 0; i < v.m; ++i) {
        os << v.content[i] << std::endl;
    }
    return os;
}

std::istream& operator>> (std::istream& is, Matrix& v) {
    for (int i = 0; i < v.m; ++i) {
        is >> v.content[i];
    }
    return is;
}

Matrix Matrix::transpose() const {
    Matrix temp(this->n, this->m);
    
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j)
            temp.content[j][i] = this->content[i][j];
    }

    return temp;
}

Vector Matrix::operator() (const Vector& v) {
    Vector temp(this->m);
    Matrix res(*this);
    res.transpose();
    
    for (int i = 0; i < m; ++i) {
        temp[i] = res[i] * v;
    }

    return temp;
}

Matrix& Matrix::operator*= (const double c) {
    for (int i = 0; i < this->m; ++i)
        this->content[i] *= c;
    return *this;
}

void Matrix::operator() () {
    (*this) *= 0;
}

Matrix Matrix::operator* (const Matrix& a) {
    assert(this-> n == a.m);
    
    Matrix temp(a), res(this->m, a.n);
    temp.transpose();

    for (int i = 0; i < this->m; ++i)
        for (int j = 0; j < a.m; ++j)
            res(i, j) = this->content[i] * temp[j];

    return res;
}

void Matrix::reshape (const int a, const int b) {
    assert(a * b == this->m * this->n);

    Matrix temp(a, b);

    for (int i = 0; i < this->m; ++i)
        for (int j = 0; j < this->n; ++j) {
            int I = (i * this->n + j) / b;
            int J = (i * this->n + j) % b;

            temp(I, J) = this->content[i][j];
        };
    
    *this = temp;
}

int Matrix::colMax(const int col) {
  double max = std::abs(this->content[col][col]);
  int maxPos = col;
  for (int i = col + 1; i < n; ++i) {
    double element = std::abs(this->content[i][col]);
    if (element > max) {
      max = element;
      maxPos = i;
    }
  }
  return maxPos;
}

int Matrix::firstNonZeroCol(const int j) {
    int i;
    for (i = j; (i < this->m) && (this->content[i][j] == 0); ++i) {}
    return i == this->m ? --i : i;
}

Matrix Matrix::triangulate(int& swaps) const {
  swaps = 0;
  Matrix res(*this);
  for (int j = 0; j < n - 1; ++j) {
    unsigned int imax = res.firstNonZeroCol(j);
    if (j != imax) {
        Vector tmp = res.content[j];
        res.content[j] = res.content[imax];
        res.content[imax] = tmp;
        ++swaps;
    }
    for (int i = j + 1; i < n; ++i) {
      double factor = res.content[i][j] / res.content[j][j];
      res.content[i] -= res.content[j] * factor;
    }
  }
  return res;
}

double Matrix::determinant() {
    int swaps;
    Matrix traingle = this->triangulate(swaps);
    double res = 1;
    
    if (swaps % 2 == 1)
        res *= -1;
    
    for (int i = 0; i < this->n; ++i)
        res *= traingle(i, i);
    
    return res;
}

double Matrix::norm(int p) {
    assert((p >= 1.0) || (p == -1.0));
    
    double res = 0;

    if (p == -1.0)
        for (int i = 0; i < this->m; ++i) {
            double tmp = this->content[i].Vector::norm(1.0);
            if (tmp > res)
                res = tmp;
        }
    else if (p == 1.0) {
        res = this->transpose().norm(-1.0);
    }
    else {
        Matrix tmp(*this);
        tmp.reshape(1, (this->m) * (this->n));
        res = tmp[0].norm(p);
    }

    return res;
}