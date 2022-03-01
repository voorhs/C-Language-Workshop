#pragma once
#include <iostream>
#include <math.h>

class Vec {
public:
    float x, y;
    Vec();
    Vec(float, float);    
    void set(float, float); 
    friend Vec operator+ (const Vec&, const Vec&);
    friend Vec operator- (const Vec&, const Vec&);
    friend float operator* (const Vec&, const Vec&);
    friend std::ostream& operator<< (std::ostream&, const Vec&);
    Vec& operator+= (const Vec&);
    Vec& operator-= (const Vec&);
    Vec operator* (const float);
    Vec& operator*= (const float);
    Vec rotate(float, Vec = Vec(0, 0));
};

float norm(Vec);