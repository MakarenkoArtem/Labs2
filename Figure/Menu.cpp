//
// Created by artem on 10.04.24.
//
#include "Menu.h"

void Menu::addCircle() {
    Point *a = new Point(0, 0);
    std::cout << "Point x y: ";
    std::cin >> a->x >> a->y;
    double radius;
    std::cout << "Radius: ";
    std::cin >> radius;
    if (std::cin.fail()) { throw UniversalException("Invalid input"); }
    figures.push_back(new Circle("Circle", *a, radius));
}

void Menu::addTriangle() {
    Point *points[3] = {new Point(0, 0), new Point(0, 0), new Point(0, 0)};
    for (int i = 0; i < 3; ++i) {
        std::cout << "Point " << i + 1 << " x y: ";
        std::cin >> points[i]->x >> points[i]->y;
    }
    figures.push_back(new Triangle("Triangle", *points[0], *points[1], *points[2]));
}

void Menu::addRectangle() {
    Point *points[2] = {new Point(0, 0), new Point(0, 0)};
    for (int i = 0; i < 2; ++i) {
        std::cout << "Point " << i + 1 << " x y: ";
        std::cin >> points[i]->x >> points[i]->y;
    }
    figures.push_back(new Rectangle("Rectangle", *points[0], *points[1]));
}

void Menu::addPolygon() {
    std::vector<Point> points;
    std::cout << "To finish, enter a non-letter\n\r";
    for (int i = 0; i > -1; ++i) {
        points.push_back(*(new Point(0, 0)));
        std::cout << "Point " << i + 1 << " x y: ";
        std::cin >> points[i].x >> points[i].y;
        if (std::cin.fail()) {
            points.erase(points.begin() + i);
            throw UniversalException("End of list points");
        }
    }
    figures.push_back(new Polygon("Polygon", points));
}

void Menu::addFigure() {
    std::vector<const char *> f = {"Circle", "Triangle", "Rectangle", "Polygon"};
    for (int i = 0; i < f.size(); ++i) {
        std::cout << i + 1 << ")" << f[i] << std::endl;
    }
    int typeFigure;
    std::cin >> typeFigure;
    if (std::cin.fail()) { throw UniversalException("Invalid input"); }
    (this->*addFigs[typeFigure])();
}

void Menu::params() {
    for (int i = 0; i < figures.size(); ++i) {
        std::cout << i + 1 << ") " << figures[i] << " " << figures[i]->params() << std::endl;
    }
}

bool cmpPerimeter(Figure *a, Figure *b) {
    return a->perimeter() < b->perimeter();
}

bool cmpArea(Figure *a, Figure *b) {
    return a->getArea() < b->getArea();
}

void Menu::delFigure() {
    double n;
    std::cin >> n;
    if (std::cin.fail() || n != abs((int) n)) {
        throw UniversalException("Invalid input");
    }
    if (n >= figures.size()) {
        throw UniversalException("Index out of range");
    }
    delete figures[n];
    figures.erase(figures.begin() + n);
}

void Menu::delBigArea() {
    double n;
    std::cin >> n;
    if (std::cin.fail() || n < 0) {
        throw UniversalException("Invalid input");
    }
    for (vector<Figure *>::iterator it = figures.begin(); it != figures.end(); ++it) {
        if ((*it)->getArea() > n) {
            delete *it;
            figures.erase(it--);
        }
    }
}

void Menu::delBigPerimeter() {
    double n;
    std::cin >> n;
    if (std::cin.fail() || n < 0) {
        throw UniversalException("Invalid input");
    }
    for (auto it = figures.begin(); it != figures.end(); ++it) {
        if ((*it)->perimeter() > n) {
            delete *it;
            figures.erase(it);
        }
    }
}

void Menu::sortByArea() {
    std::sort(figures.begin(), figures.end(), cmpArea);
    areas();
}

void Menu::sortByPerimeter() {
    std::sort(figures.begin(), figures.end(), cmpPerimeter);
    perimeters();
}

void Menu::perimeters() {
    for (int i = 0; i < figures.size(); ++i) {
        std::cout << i + 1 << ") " << figures[i] << " " << figures[i]->perimeter() << std::endl;
    }
}

void Menu::areas() {
    for (int i = 0; i < figures.size(); ++i) {
        std::cout << i + 1 << ") " << figures[i] << " " << figures[i]->getArea() << std::endl;
    }
}

int Menu::run() {
    int typeOperation;
    while (1) {
        for (int i = 0; i < funcsTitle.size(); std::cout << i + 1 << ") " << funcsTitle[i++] << std::endl);
        std::cin >> typeOperation;
        try {
            if (std::cin.fail()) {
                throw UniversalException("Invalid input");
            }
            (this->*funcs[typeOperation])();
        } catch (UniversalException &ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    return 0;
}