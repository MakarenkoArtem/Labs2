//
// Created by artem on 03.04.24.
//

#ifndef LABS2_FIGURE_H
#define LABS2_FIGURE_H
#pragma once

#include <math.h>
#include <string>
#include <sstream>
#include "UniversalException.h"
#include "Point.h"

using std::stringstream;
using std::string;

class Figure {
public:
    string title;

    Figure(string title);

    virtual double getArea() = 0;

    virtual double perimeter() = 0;

    virtual string params();

    virtual std::ostream &printType(std::ostream &os) const = 0;
};

std::ostream &operator<<(std::ostream &os, Figure *figure);

#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Polygon.h"

#endif //LABS2_FIGUR_H
