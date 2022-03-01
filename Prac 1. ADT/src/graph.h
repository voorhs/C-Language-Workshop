#pragma once
#include "vec.h"
#include "circle.h"
#include "square.h"
#include "rectangle.h"
#include <unistd.h>

const int WIDTH = 150;
const int HEIGHT = 42;
const float ASPECT = (float)WIDTH / HEIGHT;
const float PIXELASPECT = 0.5;    
const float pi = 3.14159;

class Screen {
    char content[WIDTH * HEIGHT + 1];
public:
    Screen();
    
    void addFigure(Circle, bool = false);
    void addFigure(Square, bool = false);
    void addFigure(Rectangle, bool = false);
    void display();

};

void exampleCircle();
void exampleSquare();
void exampleAnimation();
void exampleAnimation2();