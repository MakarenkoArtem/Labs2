//
// Created by artem on 09.04.24.
//

#ifndef FIGURE_UNIVERSALEXCEPTION_H
#define FIGURE_UNIVERSALEXCEPTION_H

#include <exception>


class UniversalException : public std::exception {
public:
    const char *error;

    UniversalException();

    UniversalException(const char *error);

    /*virtual: Ключевое слово virtual означает, что функция является виртуальной. Виртуальные функции могут быть переопределены в производных классах.
    const char*: Это тип возвращаемого значения функции - указатель на константную строку (массив символов char). В этом контексте это означает, что функция возвращает указатель на строку, которую нельзя изменить.
    what(): Это имя функции. В стандартной библиотеке C++ класс std::exception определяет виртуальную функцию what(), которая возвращает строку с описанием ошибки.
    const: Константный метод, который гарантирует, что функция не изменяет состояние объекта, для которого вызывается.
    throw(): Это означает, что функция не генерирует исключений. Обратите внимание, что это устаревшая конструкция, начиная с стандарта C++11, и вместо этого следует использовать noexcept.*/
    virtual const char *what() const throw() {
        return error;
    }
};


#endif //FIGURE_UNIVERSALEXCEPTION_H
