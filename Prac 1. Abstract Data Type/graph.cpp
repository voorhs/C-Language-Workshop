#include <iostream>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

using namespace std;

int main() {
    const int WIDTH = 150;
    const int HEIGHT = 42;
    const float ASPECT = (float)WIDTH / HEIGHT;
    const float PIXELASPECT = 0.5;
    const unsigned int speed = 300;
    
    char* screen = new char[HEIGHT * WIDTH + 1];
    screen[HEIGHT * WIDTH] = '\0';

    for (int t = 0; t < 10000; ++t) 
    {
        usleep(speed);
        for (int i = 0; i < HEIGHT; ++i)
        {
            for (int j = 0; j < WIDTH; ++j)
            {    
                float x = (float)j / WIDTH * 2.0 - 1.0;
                float y = (float)i / HEIGHT * 2.0 - 1.0;            
                x *= ASPECT * PIXELASPECT;

                x += sin(t * 0.001);
            
                char pixel = ' ';
                
                if (x * x + y * y < 0.5)
                    pixel = '#';

                screen[j + i * WIDTH] = pixel;
            }        
        }
        printf("%s\n", screen);
    }

    getchar();
}