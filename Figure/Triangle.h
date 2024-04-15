//
// Created by artem on 09.04.24.
//

#ifndef FIGURE_TRIANGLE_H
#define FIGURE_TRIANGLE_H

#include <vector>
#include "Figure.h"

using std::vector;

class Triangle : public Figure {
private:
    double a, b, c;
public:
    Point first, second, third;

    Triangle(string title, Point first, Point second, Point third);

    double getArea() override;

    double perimeter() override;

    string params() override;

    std::ostream &printType(std::ostream &os) const override;
};


#endif //FIGURE_TRIANGLE_H
