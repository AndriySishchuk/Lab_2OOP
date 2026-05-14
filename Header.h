#pragma once 
#include <vector>

struct Point {
    double x, y;
};

struct Triangle {
    Point a, b, c;
};

bool isDegenerate(Triangle t);
int checkPointInTriangle(Triangle t, Point p);
double calculateArea(Point a, Point b, Point c);
int checkByArea(Triangle t, Point p);
