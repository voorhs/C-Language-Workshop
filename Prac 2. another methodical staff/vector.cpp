#include "vector.h"

Vector::Vector() {
    this->n = 0;
    this->content = nullptr;
}

Vector::Vector(int n, double value) {
    this->n = n;
    this->content = new double[n];
    for (int i = 0; i < n; ++i)
        this->content[i] = value;
}

Vector::Vector(const Vector& v) {
    this->n = v.n;
    this->content = new double[v.n];
    for (int i = 0; i < v.n; ++i)
        this->content[i] = v.content[i];
}

Vector::~Vector() {
    delete[] this->content;
}

void Vector::reshape(int a, double value) {
    assert(0 < a);

    Vector res(a, value);

    for (int i = 0; i < std::min(a, this->n); ++i) {
        res.content[i] = this->content[i];
    }

    *this = res;
}

double& Vector::operator[] (const int a) const {
    assert((0 <= a) && (a < this->n));
    return this->content[a];
}

void Vector::operator() (double value) {
    for (int i = this->n - 1; i > -1; --i)
        this->content[i] = value;
}

const Vector operator+ (const Vector& v, const Vector& vv) {
    assert(v.n == vv.n);

    Vector temp(v);

    for (int i = 0; i < v.n; ++i)
        temp.content[i] += vv.content[i];

    return temp;
}

const Vector operator- (const Vector& v, const Vector& vv) {
    assert(v.n == vv.n);

    Vector temp(v);

    for (int i = 0; i < v.n; ++i)
        temp.content[i] -= vv.content[i];

    return temp;
}

Vector& Vector::operator= (const Vector& v) {
    if (this->content)
        delete[] this->content;

    this->n = v.n;
    this->content = new double[v.n];
    
    for (int i = 0; i < v.n; ++i)
        this->content[i] = v.content[i];

    return *this;
}

Vector& Vector::operator+= (const Vector& v) {
    assert(v.n == this->n);

    for (int i = 0; i < this->n; ++i)
        this->content[i] += v[i];

    return *this;
}

Vector& Vector::operator-= (const Vector& v) {
    assert(v.n == this->n);

    for (int i = 0; i < this->n; ++i)
        this->content[i] -= v[i];

    return *this;
}

Vector& Vector::operator*= (const double c) {
    for (int i = 0; i < this->n; ++i)
        this->content[i] *= c;

    return *this;
}

const Vector operator* (const Vector& v, const double c) {
    Vector temp(v);

    for (int i = 0; i < v.n; ++i)
        temp.content[i] *= c;

    return temp;
}

double operator* (const Vector& v, const Vector& vv) {
    assert(vv.n == v.n);
    
    double temp;
    for (int i = 0; i < v.n; ++i) {
        temp += v[i] * vv[i];
    }

    return temp;
}

std::ostream& operator<< (std::ostream& os, const Vector& v) {
    for (int i = 0; i < v.n; ++i)
        os << v.content[i] << ' ';
    return os;
}

std::istream& operator>> (std::istream& is, Vector& v) {
    std::cout << "\ninput " << v.n << " elemets: \n  > ";
    for (int i = 0; i < v.n; ++i) {
        is >> v.content[i];
    }
    return is;
}