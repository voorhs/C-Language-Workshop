#include "square.h"

Square::Square(float side, Vec center, float angle) {
    this->side = side;
    
    this->a = Vec(-side / 2, -side / 2);
    this->b = Vec(side / 2, -side / 2);
    this->c = Vec(side / 2, side / 2);
    this->d = Vec(-side / 2, side / 2);
    
    this->rotate(angle);
    this->move(center);
}

bool Square::contain(Vec point) {
    Square tmp(*this);
    float angle = tmp.getAngle();
    tmp.rotate(-angle);

    point.rotate(-angle);

    Vec center = (tmp.a + tmp.c) * 0.5;
    Vec r = point - center;
    return (std::max(std::abs(r.x), std::abs(r.y)) < tmp.side / 2);
}

void Square::move(Vec shift) {
    this->a += shift;
    this->b += shift;
    this->c += shift;
    this->d += shift;
}

void Square::scale(float scalar) {
    Vec center = (this->a + this->c) * 0.5;
    this->move(center * (-1));

    this->side *= scalar;
    this->a *= scalar;
    this->b *= scalar;
    this->c *= scalar;
    this->d *= scalar;
    
    this->move(center);
}

void Square::rotate(float angle, Vec pivot) {
    this->a.rotate(angle, pivot);
    this->b.rotate(angle, pivot);
    this->c.rotate(angle, pivot);
    this->d.rotate(angle, pivot);
}

void Square::set(float side, Vec center, float angle) {
    Square tmp(side);
    tmp.rotate(angle);
    tmp.a += center;
    tmp.b += center;
    tmp.c += center;
    tmp.d += center;

    *this = tmp;
}

void Square::setSide(float side) {
    this->set(side, this->getCenter(), this->getAngle());
}

void Square::setAngle(float angle) {
    this->rotate(angle - this->getAngle(), this->getCenter());
}

void Square::setCenter(Vec center) {
    this->move(center - this->getCenter());
}

float Square::getSide() {
    return this->side;
}

float Square::getAngle() {
    return atan((this->a.y - this->b.y) / (this->a.x - this->b.x));
}

Vec Square::getCenter() {
    return (this->a + this->c) * 0.5;
}

std::ostream& operator<< (std::ostream& os, Square& s) {
    return os << s.side << ", " << s.getCenter() << ", " << s.getAngle() << " | " << s.a << ", " << s.b << ", " << s.c << ", " << s.d;
}