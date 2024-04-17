//
// Created by artem on 09.04.24.
//
#include "iostream"
#include "Polygon.h"

Polygon::Polygon(std::string title, std::vector<Point> points) : Figure(title), points(points) {
    if (points.size() < 3) {
        throw UniversalException("A polygon must have more than 2 points");
    }
    double a, b, k, c;
    int zeroInd, firInd, secInd, thiInd;
    for (int i = 0; i < points.size(); ++i) {
        zeroInd = (i + 1) % points.size();
        firInd = i;
        secInd = (points.size() + i - 1) % points.size();
        thiInd = (points.size() + i - 2) % points.size();
        if (points[firInd] == points[secInd]) { UniversalException("Two points are identical"); }
        if (points[firInd].x - points[secInd].x == 0) {
            a = points[zeroInd].x - points[firInd].x;
            b = points[thiInd].x - points[firInd].x;
        } else {
            k = (points[firInd].y - points[secInd].y) / (points[firInd].x - points[secInd].x);
            c = points[firInd].y - k * points[firInd].x;
            a = (k * points[zeroInd].x + c) - points[zeroInd].y;
            b = (k * points[thiInd].x + c) - points[thiInd].y;
        }
        if (a * b <= 0) {
            throw UniversalException("The polygon is non-convex");
        }
    }
}

double Polygon::getArea() {
    double s = 0;
    for (int i = 2; i < points.size(); ++i) {
        Triangle t("", points[0], points[i - 1], points[i]);
        s += t.getArea();
    }
    return s;
}

double Polygon::perimeter() {
    double p = 0;
    for (int i = 0; i < points.size(); ++i) {
        p += sqrt(std::pow(points[(i + 1) % points.size()].x - points[i].x, 2) +
                  std::pow(points[(i + 1) % points.size()].y - points[i].y, 2));
    }
    return p;
}

string Polygon::params() {
    stringstream strStream;
    strStream<<getTitle()<<" ";
    for (int i = 0; i < points.size(); ++i)
        strStream << "Point (" << points[i].x << ", " << points[i].y << ")  ";
    return strStream.str();
}

std::ostream &Polygon::printType(std::ostream &os) const {
    os << "Polygon";
    return os;
}