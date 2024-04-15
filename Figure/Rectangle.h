//
// Created by artem on 09.04.24.
//

#ifndef FIGURE_RECTANGLE_H
#define FIGURE_RECTANGLE_H

#include "Figure.h"

class Rectangle : public Figure {
public:
    Point first, second;

    Rectangle(string title, Point first, Point second);

    double getArea() override;

    double perimeter() override;

    string params() override;

    std::ostream &printType(std::ostream &os) const override;
};


#endif //FIGURE_RECTANGLE_H
