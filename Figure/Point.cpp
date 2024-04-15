//
// Created by artem on 09.04.24.
//

#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

bool Point::operator==(const Point &other) {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) {
    return !(*this == other)
}