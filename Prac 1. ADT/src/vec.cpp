#include "vec.h"

Vec::Vec() {
    this->x = 0;
    this->y = 0;
}

Vec::Vec(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vec::set(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec operator+ (const Vec& a, const Vec& b) {
    Vec res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}

Vec operator- (const Vec& a, const Vec& b) {
    Vec res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    return res;
}

float operator* (const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y;
}

std::ostream& operator<< (std::ostream& os, const Vec& a) {
    return os << '(' << a.x << ", " << a.y << ')';
}

float norm(Vec a) {
    return sqrt(a * a);
}

Vec& Vec::operator+= (const Vec& a) {
    this->x += a.x;
    this->y += a.y;
    return *this;
}

Vec& Vec::operator-= (const Vec& a) {
    this->x -= a.x;
    this->y -= a.y;
    return *this;
}

Vec& Vec::operator*= (const float a) {
    this->x *= a;
    this->y *= a;
    return *this;
}

Vec Vec::operator* (const float scalar) {
    Vec res;
    res.x = this->x * scalar;
    res.y = this->y * scalar;
    return res;
}

Vec Vec::rotate(float angle, Vec pivot) {
    float s = sin(angle);
    float c = cos(angle);

    // translate center to origin
    Vec newCenter = *this - pivot;

    // rotate
    float xnew = newCenter.x * c - newCenter.y * s;
    float ynew = newCenter.x * s + newCenter.y * c;    

    // translate back
    *this = Vec(xnew, ynew) + pivot;
    return *this;
}