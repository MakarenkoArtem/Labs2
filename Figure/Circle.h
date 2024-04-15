//
// Created by artem on 09.04.24.
//

#ifndef FIGURE_CIRCLE_H
#define FIGURE_CIRCLE_H
#include "Figure.h"
class Circle: public Figure {
    Point point;
    double radius;

public:
    Circle(std::string title, Point point, double radius);//std::string t);//, double[2], double r);
    double getArea() override;
    double perimeter() override;
    string params() override;
    std::ostream& printType(std::ostream& os) const override;
};


#endif //FIGURE_CIRCLE_H
