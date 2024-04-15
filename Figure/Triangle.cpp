//
// Created by artem on 09.04.24.
//
#include "Triangle.h"

Triangle::Triangle(std::string title, Point first, Point second, Point third) : Figure(title), first(first),
                                                                                second(second), third(third) {
    a = sqrt(std::pow(first.x - second.x, 2) + std::pow(first.y - second.y, 2));
    b = sqrt(std::pow(first.x - third.x, 2) + std::pow(first.y - third.y, 2));
    c = sqrt(std::pow(third.x - second.x, 2) + std::pow(third.y - second.y, 2));
    if (!(a && b && c)) {
        throw UniversalException("The side of the triangle is equal to 0");
    }
};

double Triangle::perimeter() {
    return a + b + c;
}

double Triangle::getArea() {
    double p = this->perimeter() / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

string Triangle::params() {
    stringstream strStream;
    vector<Point> points = {first, second, third};
    for (int i = 0; i < points.size(); ++i)
        strStream << "Point (" << points[i].x << ", " << points[i].y << ")  ";
    return strStream.str();
}

std::ostream &Triangle::printType(std::ostream &os) const {
    os << "Triangle";
    return os;
}