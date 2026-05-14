#include "Header.h"
#include <cmath>
#include <algorithm>

const double EPS = 1e-9;

double distance(Point p1, Point p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

double heronArea(Point a, Point b, Point c) {
    double sideA = distance(a, b);
    double sideB = distance(b, c);
    double sideC = distance(c, a);
    double s = (sideA + sideB + sideC) / 2.0;
    double val = s * (s - sideA) * (s - sideB) * (s - sideC);
    return std::sqrt(std::max(0.0, val));
}

double calculateArea(Point a, Point b, Point c) {
    return heronArea(a, b, c);
}

bool isDegenerate(Triangle t) {
    return calculateArea(t.a, t.b, t.c) < EPS;
}

bool isBetween(double start, double end, double val) {
    return val >= (std::min(start, end) - EPS) && val <= (std::max(start, end) + EPS);
}

bool isOnSegment(Point s1, Point s2, Point p) {
    double cross = (s2.x - s1.x) * (p.y - s1.y) - (s2.y - s1.y) * (p.x - s1.x);
    if (std::abs(cross) > EPS) return false;
    return isBetween(s1.x, s2.x, p.x) && isBetween(s1.y, s2.y, p.y);
}

int checkByArea(Triangle t, Point p) {
    if (isDegenerate(t)) {
        if (isOnSegment(t.a, t.b, p) || isOnSegment(t.b, t.c, p) || isOnSegment(t.a, t.c, p)) return 2;
        return 0;
    }

    double S_abc = calculateArea(t.a, t.b, t.c);
    double S_pab = calculateArea(p, t.a, t.b);
    double S_pbc = calculateArea(p, t.b, t.c);
    double S_pca = calculateArea(p, t.c, t.a);

    double S_sum = S_pab + S_pbc + S_pca;

    if (std::abs(S_abc - S_sum) < EPS) {
        if (S_pab < EPS || S_pbc < EPS || S_pca < EPS) return 2;
        return 1;
    }
    return 0;
}

int checkPointInTriangle(Triangle t, Point p) {
    if (isDegenerate(t)) return checkByArea(t, p);

    double d1 = (t.b.x - t.a.x) * (p.y - t.a.y) - (t.b.y - t.a.y) * (p.x - t.a.x);
    double d2 = (t.c.x - t.b.x) * (p.y - t.b.y) - (t.c.y - t.b.y) * (p.x - t.b.x);
    double d3 = (t.a.x - t.c.x) * (p.y - t.c.y) - (t.a.y - t.c.y) * (p.x - t.c.y);

    bool has_neg = (d1 < -EPS) || (d2 < -EPS) || (d3 < -EPS);
    bool has_pos = (d1 > EPS) || (d2 > EPS) || (d3 > EPS);

    if (has_neg && has_pos) return 0;
    if (std::abs(d1) < EPS || std::abs(d2) < EPS || std::abs(d3) < EPS) return 2;
    return 1;
}