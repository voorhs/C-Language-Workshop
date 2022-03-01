#include "circle.h"


Circle::Circle(float radius, Vec center) {
    this->center = center;
    this->radius = radius;
}

bool Circle::contain(Vec point) {
    return (norm(point - this->center) < this->radius);
}

void Circle::move(Vec shift) {
    this->center += shift;
}

void Circle::scale(float scalar) {
    this->radius *= scalar;
} 

void Circle::rotate(float angle, Vec pivot) {
    this->center.rotate(angle, pivot);
}

void Circle::set(float radius, Vec center) {
    this->center = center;
    this->radius = radius;
}

void Circle::alienate(float scalar) {
    this->center *= scalar;
}

void Circle::setCenter(Vec center) {
    this->center = center;
}

void Circle::setRadius(float radius) {
    this->radius = radius;
}

Vec Circle::getCenter() {
    return this->center;
}

float Circle::getRadius() {
    return this->radius;
}

std::ostream& operator<< (std::ostream& os, Circle a) {
    return os << a.center << ", " << a.radius;
}