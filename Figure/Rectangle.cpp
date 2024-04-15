//
// Created by artem on 09.04.24.
//

#include "Rectangle.h"

Rectangle::Rectangle(std::string title, Point first, Point second) : Figure(title), first(first), second(second) {}

double Rectangle::perimeter() {
    return 2 * (second.x - first.x + second.y - first.y);
}

double Rectangle::getArea() {
    return 2 * (second.x - first.x) * (second.y - first.y);
}

string Rectangle::params() {
    stringstream strStream;
    strStream << "Point (" << first.x << ", " << first.y << ")   ";
    strStream << "Point (" << second.x << ", " << second.y << ")";
    return strStream.str();
}

std::ostream &Rectangle::printType(std::ostream &os) const {
    os << "Rectangle";
    return os;
}