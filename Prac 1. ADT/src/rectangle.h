#pragma once
#include "vec.h"
#include <algorithm>

class Rectangle {
    Vec a, b, c, d;
    float sideA, sideB;
public:    
    Rectangle(float = 1.2, float = 0.4, Vec = Vec(0, 0), float = 0);
    
    bool contain(Vec);
    
    void move(Vec);
    void scale(float);
    void rotate(float, Vec = Vec(0, 0));
    
    void set(float = 1.2, float = 0.4, Vec = Vec(0, 0), float = 0);
    void setSides(float, float);
    void setCenter(Vec);
    void setAngle(float);    
   
    Vec getCenter();
    float getSideA();
    float getSideB();
    float getAngle();

    friend std::ostream& operator<< (std::ostream&, Rectangle&);
};