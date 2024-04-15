//
// Created by artem on 09.04.24.
//

#ifndef FIGURE_POLYGON_H
#define FIGURE_POLYGON_H
#pragma once

#include <vector>
#include "Figure.h"

using std::vector;

class Polygon : public Figure {
public:
    vector<Point> points;

    Polygon(string title, vector<Point> points);

    double getArea() override;

    double perimeter() override;

    string params() override;

    std::ostream &printType(std::ostream &os) const override;
};


#endif //FIGURE_POLYGON_H
