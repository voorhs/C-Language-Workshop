#pragma once
#include "vec.h"
#include <algorithm>

class Square {
    Vec a, b, c, d;
    float side;
public:    
    Square(float = 0.1, Vec = Vec(0, 0), float = 0);
    
    bool contain(Vec);
    void move(Vec);
    void scale(float);
    void rotate(float, Vec = Vec(0, 0));
    
    void set(float = 0.3, Vec = Vec(0, 0), float = 0);
    void setCenter(Vec);
    void setSide(float);
    void setAngle(float);
    
    Vec getCenter();
    float getSide();    
    float getAngle();
    friend std::ostream& operator<< (std::ostream&, Square&);
};