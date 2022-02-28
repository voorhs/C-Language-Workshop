#include "point.h"

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(float x, float y) {
    this->x = x;
    this->y = y;
}

void Point::set(float x, float y) {
    this->x = x;
    this->y = y;
}

Point operator+ (const Point& a, const Point& b) {
    Point res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}

Point operator- (const Point& a, const Point& b) {
    Point res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    return res;
}

float operator* (const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

std::ostream& operator<< (std::ostream& os, const Point& a) {
    return os << '(' << a.x << ", " << a.y << ')';
}
