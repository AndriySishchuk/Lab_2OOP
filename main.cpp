#include <iostream>
#include "Header.h"

int main() {
    Point a, b, c;
    std::cout << "Введіть координати вершин (x1 y1 x2 y2 x3 y3): ";
    
    if (!(std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y)) {
        std::cout << "Некоректний формат координат трикутника." << std::endl;
        return 1;
    }

    Triangle triangle = {a, b, c};

    if (isDegenerate(triangle)) {
        std::cout << "Трикутник вироджений (сприймається як лінія)." << std::endl;
    }

    std::cout << "\nПеревірка точок" << std::endl;
    std::cout << "Введіть координати точки (x y)" << std::endl;
    std::cout << "Щоб завершити, введіть будь-яку літеру" << std::endl;

    Point p;
    int count = 1;
    while (std::cout << "Точка №" << count << ": " && std::cin >> p.x >> p.y) {

        int resArea = checkByArea(triangle, p);
        std::cout << "Метод площ:    ";
        if (resArea == 1) std::cout << "всередині" << std::endl;
        else if (resArea == 2) std::cout << "на межі" << std::endl;
        else std::cout << "зовні" << std::endl;

        int resVector = checkPointInTriangle(triangle, p);
        std::cout << "Метод векторів: ";
        if (resVector == 1) std::cout << "всередині" << std::endl;
        else if (resVector == 2) std::cout << "на межі" << std::endl;
        else std::cout << "зовні" << std::endl;

        count++;
    }

    return 0;
}