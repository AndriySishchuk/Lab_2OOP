#include <iostream>
#include "Header.h"

int main() {
    Point a, b, c;
    std::cout << "Введіть координати вершин (x1 y1 x2 y2 x3 y3): ";
    
    if (!(std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y)) {
        std::cout << "Некоректний формат координат трикутника." << std::endl;
        return 1;
    }

    if (isDegenerate(a, b, c)) {
        std::cout << "Трикутник вироджений (площа = 0)." << std::endl;
        return 1;
    }

    int choice;
    std::cout << "\nОберіть метод перевірки:" << std::endl;
    std::cout << "1 - Метод векторного добутку" << std::endl;
    std::cout << "2 - Метод площ" << std::endl;
    std::cout << "Ваш вибір: ";
    std::cin >> choice;

    std::cout << "\nПеревірка точок" << std::endl;
    std::cout << "Введіть координати точки (x y)" << std::endl;
    std::cout << "Щоб завершити, введіть будь-яку літеру" << std::endl;

    Point p;
    int count = 1;
    while (std::cout << "Точка №" << count << ": " && std::cin >> p.x >> p.y) {
        int result;
        
        if (choice == 2) {
            result = checkByArea(a, b, c, p);
        } else {
            result = checkPointInTriangle(a, b, c, p);
        }
        
        std::cout << ">> Результат (" << p.x << ", " << p.y << "): ";
        if (result == 1) {
            std::cout << "всередині" << std::endl;
        } else if (result == 2) {
            std::cout << "на межі" << std::endl;
        } else {
            std::cout << "ззовні" << std::endl;
        }
        count++;
    }

    std::cout << "\nПеревірено точок: " << count - 1 << std::endl;
    return 0;
}