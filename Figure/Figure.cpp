//
// Created by artem on 03.04.24.
//
#include "Figure.h"

Figure::Figure(std::string title) : title(title) {};

string Figure::params() {
    return string("This type firure don't defined");
}

std::ostream &operator<<(std::ostream &os, Figure *figure) {
    return figure->printType(os);
}
