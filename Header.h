#pragma once 
#include <vector>

struct Point {
    double x, y;
};

bool isDegenerate(Point a, Point b, Point c);
int checkPointInTriangle(Point a, Point b, Point c, Point p);
double calculateArea(Point a, Point b, Point c);
int checkByArea(Point a, Point b, Point c, Point p);

