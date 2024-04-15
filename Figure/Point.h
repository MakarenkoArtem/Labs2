//
// Created by artem on 09.04.24.
//

#ifndef FIGURE_POINT_H
#define FIGURE_POINT_H


class Point {
public:
    double x, y;
    Point(double x, double y);
    bool operator==(const Point &other);
    bool operator!=(const Point &other);
};


#endif //FIGURE_POINT_H
