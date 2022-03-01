#pragma once
#include "vec.h"

class Circle {
    Vec center;
    float radius;
public:
    Circle(float = 0.15, Vec = Vec(0, 0));
    
    bool contain(Vec);
    void move(Vec);
    void scale(float);
    void rotate(float, Vec = Vec(0, 0));
    void alienate(float);
    
    void set(float, Vec = Vec(0,0));
    void setCenter(Vec);
    void setRadius(float);
    
    Vec getCenter();
    float getRadius();
    
    friend std::ostream& operator<< (std::ostream&, Circle);
};