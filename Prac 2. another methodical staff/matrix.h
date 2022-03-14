#pragma once
#include <cassert>
#include <iostream>
#include "vector.h"

class Matrix: Vector {
    Vector* content;
    int m, n;
public:
    Matrix();
    Matrix(int m, int n, double value = 0.0);
    Matrix(const Matrix& a);
    ~Matrix();

    void    reshape(const int a, const int b);
    Matrix  transpose() const;
    int     colMax(const int i);
    int     firstNonZeroCol(const int j);
    Matrix  triangulate(int& swaps) const;
    virtual double norm(const int p);
    double  determinant();

    double& operator() (const int a, const int b);
    Vector  operator() (const Vector& v);
    void    operator() ();
    Vector& operator[] (const int a) const;
    
    Matrix  operator+ (const Matrix& m);
    Matrix  operator- (const Matrix& m);
    Matrix  operator* (const double c);
    Matrix  operator* (const Matrix& a);
    Matrix& operator*= (const double c);
    Matrix& operator= (const Matrix& m);

    friend std::ostream& operator<< (std::ostream& os, const Matrix& a);
    friend std::istream& operator>> (std::istream& is, Matrix& a);
};