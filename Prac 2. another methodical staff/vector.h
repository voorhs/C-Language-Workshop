#pragma once
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <iomanip>

class Vector {
    double* content;
    int n;
    static unsigned int objCount;
public:
    Vector();
    Vector(int n, double value = 0.0);
    Vector(const Vector& v);
    ~Vector();

    unsigned getObjCount();
    
    double& operator[] (const int a) const;
    void operator() (double value = 0.0);

    void reshape(int a, double value = 0.0);
    virtual double norm(const double p);
    
    friend const Vector operator+ (const Vector& v, const Vector& vv);
    friend const Vector operator- (const Vector& v, const Vector& vv);
    friend const Vector operator* (const Vector& v, const double c);

    Vector& operator= (const Vector& v);
    Vector& operator+= (const Vector& v);
    Vector& operator-= (const Vector& v);
    Vector& operator*= (const double c);
    
    friend double operator* (const Vector& v, const Vector& vv);
    
    friend std::ostream& operator<< (std::ostream& os, const Vector& a);
    friend std::istream& operator>> (std::istream& is, Vector& a);
};