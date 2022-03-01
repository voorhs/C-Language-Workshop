/*
Построить систему классов для описания плоских геометрических фигур: круга,
квадрата, прямоугольника. Предусмотреть методы для создания объектов, перемещения на плоскости,
изменения размеров и вращения на заданный угол.

Программа должна содержать меню, позволяющее осуществить проверку всех методов классов.
*/

#include "vec.h"
#include "graph.h"
#include "square.h"
#include "circle.h"

#include <unistd.h>
#include <math.h>
#include <stdexcept>
#include <iostream>

using namespace std;

void defineCircle(Screen& tv) {
    Circle c;
    int resp = 3;

    while (resp != 0)
    {
        while (resp == 3)
        {
            float x, y, r;
            cout << "\nВведите радиус и центр круга (в пределах  [-1.8,1.8]x[-1,1] )\n>> ";
            cin >> r >> x >> y;
            c = Circle(r, Vec(x, y));
        
            cout << "\nВы ввели: " << c << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Радиус\n3. Центр и радиус\n>> ";
            cin >> resp;
        }

        while (resp == 2)
        {
            float r;
            cout << "\nВведите радиус (в пределах  [-1.8,1.8]x[-1,1] )\n>> ";
            cin >> r;
            c.setRadius(r);

            cout << "\nВы ввели: " << c << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Радиус\n3. Центр и радиус\n>> ";
            cin >> resp;
        }

        while (resp == 1)
        {
            float x, y;
            cout << "\nВведите центр круга (в пределах  [-1.8,1.8]x[-1,1] )\n>> ";
            cin >> x >> y;
            c.setCenter(Vec(x, y));
        
            cout << "\nВы ввели: " << c << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Радиус\n3. Центр и радиус\n>> ";
            cin >> resp;
        }
    }

    tv.addFigure(c);
    tv.display();
    sleep(2);

    resp = 3;

    while (resp != 0)
    {
        cout << "\nЗафиксировано: " << c << endl;
        cout << "\nСоздать трансформированную копию?\n0. Нет\n1. Повернуть относительно точки\n2. Уменьшить\n3. Увеличить \n>> ";
        cin >> resp;
        
        if (resp == 3)
        {
            float scalar;
            cout << "\nВо сколько раз?\n>> ";
            cin >> scalar;
            c.scale(scalar);
        }

        if (resp == 2)
        {
            float scalar;
            cout << "\nВо сколько раз?\n>> ";
            cin >> scalar;
            
            c.scale(1 / scalar);
        }

        if (resp == 1)
        {
            float x, y, a;
            cout << "\nВведите точку (в пределах  [-1.8,1.8]x[-1,1] ) и угол (в радианах)\n>> ";
            cin >> x >> y >> a;

            c.rotate(a, Vec(x, y));
        }
        tv.addFigure(c);
        tv.display();
        sleep(2);
    }
}

void defineSquare(Screen& tv) {
    Square s;
    int resp = 4;

    while (resp != 0)
    {
        while (resp == 4)
        {
            float x, y, d, a;
            cout << "\nВведите сторону квадрата (в пределах [0,2]), его центр (в пределах  [-1.8,1.8]x[-1,1] ) и угол наклона (в радианах)\n>> ";
            cin >> d >> x >> y >> a;
           
            s.set(d, Vec(x, y), a);
        
            cout << "\nВы ввели: " << s << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Сторону\n3. Угол\n4. Центр, сторону и угол\n>> ";
            cin >> resp;
        }

        while (resp == 3)
        {
            float a;
            cout << "\nВведите угол (в радианах  [-1.8,1.8]x[-1,1] )\n>> ";
            cin >> a;
           
            s.setAngle(a);

            cout << "\nВы ввели: " << s << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Сторону\n3. Угол\n4. Центр, сторону и угол\n>> ";
            cin >> resp;
        }

        while (resp == 2)
        {
            float d;
            cout << "\nВведите сторону (в пределах [0,2])\n>> ";
            cin >> d;
            
            s.setSide(d);
        
            cout << "\nВы ввели: " << s << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Сторону\n3. Угол\n4. Центр, сторону и угол\n>> ";
            cin >> resp;
        }

        while (resp == 1)
        {
            float x, y;
            cout << "\nВведите центр (в пределах  [-1.8,1.8]x[-1,1] )\n>> ";
            cin >> x >> y;
            
            s.setCenter(Vec(x, y));
        
            cout << "\nВы ввели: " << s << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Сторону\n3. Угол\n4. Центр, сторону и угол\n>> ";
            cin >> resp;
        }
    }

    tv.addFigure(s);
    tv.display();
    sleep(2);

    resp = 3;

    while (resp != 0)
    {
        cout << "\nЗафиксировано: " << s << endl;
        cout << "\nСоздать трансформированную копию?\n0. Нет\n1. Повернуть относительно точки\n2. Уменьшить\n3. Увеличить \n>> ";
        cin >> resp;
        
        if (resp == 3)
        {
            float scalar;
            cout << "\nВо сколько раз?\n>> ";
            cin >> scalar;
            s.scale(scalar);
        }

        if (resp == 2)
        {
            float scalar;
            cout << "\nВо сколько раз?\n>> ";
            cin >> scalar;
            
            s.scale(1 / scalar);
        }

        if (resp == 1)
        {
            float x, y, a;
            cout << "\nВведите точку (в пределах  [-1.8,1.8]x[-1,1] ) и угол (в радианах)\n>> ";
            cin >> x >> y >> a;

            s.rotate(a, Vec(x, y));
        }
        tv.addFigure(s);
        tv.display();
        sleep(2);
    }
}

void defineRectangle(Screen& tv) {
    Rectangle r;
    int resp = 5;

    while (resp != 0)
    {
        while (resp == 5)
        {
            float d1, d2, x, y, a;
                cout << "\nВведите стороны прямоугольника (в пределах [0,2]), его центр (в пределах  [-1.8,1.8]x[-1,1] ) и угол наклона (в радианах)\n>> ";
                cin >> d1 >> d2 >> x >> y >> a;
           
            r.set(d1, d2, Vec(x, y), a);
        
            cout << "\nВы ввели: " << r << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Сторону A\n3. Сторону B\n4. Угол\n5. Центр, сторону и угол\n>> ";
            cin >> resp;
        }

        while (resp == 4)
        {
            float a;
            cout << "\nВведите угол (в радианах  [-1.8,1.8]x[-1,1] )\n>> ";
            cin >> a;
           
            r.setAngle(a);

            cout << "\nВы ввели: " << r << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Сторону A\n3. Сторону B\n4. Угол\n5. Центр, сторону и угол\n>> ";
            cin >> resp;
        }

        while (resp == 3)
        {
            float d;
            cout << "\nВведите сторону B (в пределах [0,2])\n>> ";
            cin >> d;
            
            r.setSides(r.getSideA(), d);
        
            cout << "\nВы ввели: " << r << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Сторону A\n3. Сторону B\n4. Угол\n5. Центр, сторону и угол\n>> ";
            cin >> resp;
        }

        while (resp == 2)
        {
            float d;
            cout << "\nВведите сторону A (в пределах [0,2])\n>> ";
            cin >> d;
            
            r.setSides(d, r.getSideB());
        
            cout << "\nВы ввели: " << r << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Сторону A\n3. Сторону B\n4. Угол\n5. Центр, сторону и угол\n>> ";
            cin >> resp;
        }

        while (resp == 1)
        {
            float x, y;
            cout << "\nВведите центр (в пределах  [-1.8,1.8]x[-1,1] )\n>> ";
            cin >> x >> y;
            
            r.setCenter(Vec(x, y));
        
            cout << "\nВы ввели: " << r << "\nХотите что-нибудь исправить?\n0. Нет\n1. Центр\n2. Сторону\n3. Угол\n4. Центр, сторону и угол\n>> ";
            cin >> resp;
        }
    }

    tv.addFigure(r);
    tv.display();
    sleep(2);

    resp = 3;

    while (resp != 0)
    {
        cout << "\nЗафиксировано: " << r << endl;
        cout << "\nСоздать трансформированную копию?\n0. Нет\n1. Повернуть относительно точки\n2. Уменьшить\n3. Увеличить \n>> ";
        cin >> resp;
        
        if (resp == 3)
        {
            float scalar;
            cout << "\nВо сколько раз?\n>> ";
            cin >> scalar;
            r.scale(scalar);
        }

        if (resp == 2)
        {
            float scalar;
            cout << "\nВо сколько раз?\n>> ";
            cin >> scalar;
            
            r.scale(1 / scalar);
        }

        if (resp == 1)
        {
            float x, y, a;
            cout << "\nВведите точку (в пределах  [-1.8,1.8]x[-1,1] ) и угол (в радианах)\n>> ";
            cin >> x >> y >> a;

            r.rotate(a, Vec(x, y));
        }

        tv.addFigure(r);
        tv.display();
        sleep(2);
    }
}

int main() {
    Screen tv;
    int resp = 1;

    while (resp == 1)
    {
        cout << "\n\nВыберите фигуру:\n1. Круг\n2. Квадрат\n3. Прямоугольник\n>> ";
        cin >> resp;
        switch(resp) {
            case 1: {
                defineCircle(tv);
                break;
            }
            case 2: {
                defineSquare(tv);
                break;
            }
            case 3: {
                defineRectangle(tv);
                break;
            }
        }
        cout << "Хотите добавить ещё фигур? [1/0]\n>> ";
        cin >> resp;
    }

    exampleAnimation2();
    exampleAnimation();
    sleep(2);
}