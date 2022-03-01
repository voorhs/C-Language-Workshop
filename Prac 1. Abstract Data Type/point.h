#pragma once
#include <iostream>

class Point {
public:
    float x, y;
    Point();
    Point(float, float);    
    void set(float, float);        
    friend Point operator+ (const Point&, const Point&);
    friend Point operator- (const Point&, const Point&);
    friend float operator* (const Point&, const Point&);
    friend std::ostream& operator<< (std::ostream&, const Point&);
};