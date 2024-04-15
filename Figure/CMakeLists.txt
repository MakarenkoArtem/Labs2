cmake_minimum_required(VERSION 3.27)
project(Figure)

set(CMAKE_CXX_STANDARD 17)

add_executable(Figure main.cpp
        Circle.cpp
        Circle.h
        Point.cpp
        Point.h
        Figure.cpp
        Rectangle.cpp
        Rectangle.h
        Triangle.cpp
        Triangle.h
        Polygon.cpp
        Polygon.h
        UniversalException.cpp
        UniversalException.h
        Menu.cpp
        Menu.h
)
