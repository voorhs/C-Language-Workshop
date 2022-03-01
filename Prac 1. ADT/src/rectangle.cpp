#include "rectangle.h"

Rectangle::Rectangle(float sideA, float sideB, Vec center, float angle) {
    this->sideA = sideA;
    this->sideB = sideB;
    
    this->a = Vec(-sideA / 2, -sideB / 2);
    this->b = Vec(sideA / 2, -sideB / 2);
    this->c = Vec(sideA / 2, sideB / 2);
    this->d = Vec(-sideA / 2, sideB / 2);
    
    this->rotate(angle);
    this->move(center);
}    

bool Rectangle::contain(Vec point) {
    Rectangle tmp(*this);

    float angle = tmp.getAngle();
    tmp.rotate(-angle);

    point.rotate(-angle);

    Vec center = (tmp.a + tmp.c) * 0.5;
    Vec r = point - center;


    return (abs(r.x) < tmp.sideA / 2) && (abs(r.y) < tmp.sideB / 2);
}

void Rectangle::move(Vec shift) {
    this->a += shift;
    this->b += shift;
    this->c += shift;
    this->d += shift;
}

void Rectangle::scale(float scalar) {
    Vec center = (this->a + this->c) * 0.5;
    this->move(center * (-1));

    this->sideA *= scalar;
    this->sideB *= scalar;
    this->a *= scalar;
    this->b *= scalar;
    this->c *= scalar;
    this->d *= scalar;
    
    this->move(center);
}

void Rectangle::rotate(float angle, Vec pivot) {
    this->a.rotate(angle, pivot);
    this->b.rotate(angle, pivot);
    this->c.rotate(angle, pivot);
    this->d.rotate(angle, pivot);
}

void Rectangle::set(float sideA, float sideB, Vec center, float angle) {
    Rectangle tmp(sideA, sideB);
    tmp.rotate(angle);
    tmp.a += center;
    tmp.b += center;
    tmp.c += center;
    tmp.d += center;

    *this = tmp;
}

void Rectangle::setCenter(Vec center) {
    this->move(center - this->getCenter());
}

void Rectangle::setAngle(float angle) {
    this->rotate(angle - this->getAngle(), this->getCenter());
}

void Rectangle::setSides(float sideA, float sideB) {
    this->set(sideA, sideB, this->getCenter(), this->getAngle());
}

float Rectangle::getSideA() {
    return this->sideA;
}

float Rectangle::getSideB() {
    return this->sideB;
}

float Rectangle::getAngle() {
    return atan((this->a.y - this->b.y) / (this->a.x - this->b.x));
}

Vec Rectangle::getCenter() {
    return (this->a + this->c) * 0.5;
}

std::ostream& operator<< (std::ostream& os, Rectangle& s) {
    return os << s.sideA << ", " << s.sideB << ", " << s.getCenter() << ", " << s.getAngle() << " | " << s.a << ", " << s.b << ", " << s.c << ", " << s.d;
}