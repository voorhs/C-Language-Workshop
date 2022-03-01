#include "graph.h"

Screen::Screen() {
    content[WIDTH * HEIGHT] = '\0';

    for (int i = 0; i < HEIGHT; ++i)
        for (int j = 0; j < WIDTH; ++j)
            content[j + i * WIDTH] = ' ';
}


void Screen::addFigure(Circle figure, bool clear)
{
    for (int i = 0; i < HEIGHT; ++i)
        for (int j = 0; j < WIDTH; ++j) {    
            Vec point;       
            point.x = (float)j / WIDTH * 2.0 - 1.0;
            point.y = (float)i / HEIGHT * 2.0 - 1.0;

            point.y *= -1;   
            
            point.x *= ASPECT * PIXELASPECT;                                
                        
            if (figure.contain(point))
                content[j + i * WIDTH] = '#';
            else if (clear)
                content[j + i * WIDTH] = ' ';
        }
}

void Screen::addFigure(Square figure, bool clear)
{
    for (int i = 0; i < HEIGHT; ++i)
        for (int j = 0; j < WIDTH; ++j) {    
            Vec point;       
            point.x = (float)j / WIDTH * 2.0 - 1.0;
            point.y = (float)i / HEIGHT * 2.0 - 1.0;

            point.y *= -1;   
            
            point.x *= ASPECT * PIXELASPECT;                                
            
            if (figure.contain(point))
                content[j + i * WIDTH] = '#';
            else if (clear)
                content[j + i * WIDTH] = ' ';
        }
}

void Screen::addFigure(Rectangle figure, bool clear)
{
    for (int i = 0; i < HEIGHT; ++i)
        for (int j = 0; j < WIDTH; ++j) {    
            Vec point;       
            point.x = (float)j / WIDTH * 2.0 - 1.0;
            point.y = (float)i / HEIGHT * 2.0 - 1.0;

            point.y *= -1;   
            
            point.x *= ASPECT * PIXELASPECT;                                
            
            if (figure.contain(point))
                content[j + i * WIDTH] = '#';
            else if (clear)
                content[j + i * WIDTH] = ' ';
        }
}

void Screen::display() {
    printf("%s\n", this->content);
}

void exampleCircle() {
    Screen tv;

    Circle circle(0.1, Vec(0.5, 0));

    for (int i = 0; i < 8; i++) {
        tv.addFigure(circle);
        circle.rotate(pi / 4);
    }

    circle = Circle(0.3, Vec(0, 0));
    tv.addFigure(circle);
    
    tv.display();
}

void exampleSquare() {
    Screen tv;

    Square s(0.33, Vec(0.5, 0.5));

    for (int i = 0; i < 12; i++) {
        s.rotate(pi/6);
        tv.addFigure(s);
    }
    
    tv.display();
}

void exampleAnimation() {
    Screen tv;

    Circle c(0.05, Vec(0.05, 0.05));

    for (int t = 0; t < 1500; ++t) {
        usleep(800);
        tv.addFigure(c);
        tv.display();
        c.rotate(pi/25);
        c.alienate(1.003);
    }
}

void exampleAnimation2() {
    Screen tv;

    Rectangle r(0.8, 0.4);

    for (int t = 0; t < 1000; ++t) {
        usleep(600);
        tv.display();
        
        r.setAngle(t * 0.006);

        tv.addFigure(r, true);
    }
}