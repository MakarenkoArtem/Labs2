//
// Created by artem on 09.04.24.
//

#include "Circle.h"

Circle::Circle(string title, Point point, double radius) : Figure(title), point(point), radius(radius) {}

double Circle::perimeter() {
    return M_PI * 2 * radius;
}

double Circle::getArea() {
    return M_PI * radius * radius;
}

string Circle::params() {
    stringstream strStream;
    strStream << " "<< getTitle()<< " Point (" << point.x << ", " << point.y << ")\n Radius: " << radius;
    return strStream.str();
}

std::ostream &Circle::printType(std::ostream &os) const {
    os << "Circle";
    return os;
};