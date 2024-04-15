//
// Created by artem on 10.04.24.
//

#ifndef FIGURE_MENU_H
#define FIGURE_MENU_H
#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "Figure.h"

using std::vector;

class Menu {
private:
    vector<Figure *> figures;
    vector<std::string> funcsTitle = {"Add figure", "Show params", "Show perimeters", "Show areas", "Sort by area",
                                      "Sort by perimeter", "Delete by index", "Delete figures with big area",
                                      "Delete figures with big perimeter"};
    std::map<int, void (Menu::*)()> funcs = {{1, &Menu::addFigure},
                                             {2, &Menu::params},
                                             {3, &Menu::perimeters},
                                             {4, &Menu::areas},
                                             {5, &Menu::sortByArea},
                                             {6, &Menu::sortByPerimeter},
                                             {7, &Menu::delFigure},
                                             {8, &Menu::delBigArea},
                                             {9, &Menu::delBigPerimeter}};
    std::map<int, void (Menu::*)()> addFigs = {{1, &Menu::addCircle},
                                               {2, &Menu::addTriangle},
                                               {3, &Menu::addRectangle},
                                               {4, &Menu::addPolygon}};

    void delBigArea();

    void delBigPerimeter();

    void sortByArea();

    void sortByPerimeter();

    void perimeters();

    void areas();

    void delFigure();

    void addFigure();

    void addCircle();

    void addTriangle();

    void addRectangle();

    void addPolygon();

    void params();

public:
    int run();
};

#endif //FIGURE_MENU_H
