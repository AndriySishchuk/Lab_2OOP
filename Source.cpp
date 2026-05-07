#include "Header.h"
#include <cmath>

const double EPS = 1e-9;

double crossProduct(Point a, Point b, Point p) {
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

double calculateArea(Point a, Point b, Point c) {
    return std::abs(crossProduct(a, b, c)) / 2.0;
}

bool isDegenerate(Point a, Point b, Point c) {
    return calculateArea(a, b, c) < EPS;
}

int checkPointInTriangle(Point a, Point b, Point c, Point p) {
    double d1 = crossProduct(a, b, p);
    double d2 = crossProduct(b, c, p);
    double d3 = crossProduct(c, a, p);

    bool has_neg = (d1 < -EPS) || (d2 < -EPS) || (d3 < -EPS);
    bool has_pos = (d1 > EPS) || (d2 > EPS) || (d3 > EPS);

    if (has_neg && has_pos) return 0;
    if (std::abs(d1) < EPS || std::abs(d2) < EPS || std::abs(d3) < EPS) return 2;
    return 1;
}

int checkByArea(Point a, Point b, Point c, Point p) {
    double S_abc = calculateArea(a, b, c);
    double S_pab = calculateArea(p, a, b);
    double S_pbc = calculateArea(p, b, c);
    double S_pca = calculateArea(p, c, a);

    double S_sum = S_pab + S_pbc + S_pca;

    if (std::abs(S_sum - S_abc) < EPS) {
        if (S_pab < EPS || S_pbc < EPS || S_pca < EPS) return 2;
        return 1;
    }
    return 0;
}