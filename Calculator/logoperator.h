#ifndef LOGOPERATOR_H
#define LOGOPERATOR_H
#pragma once
#include <string>
#include "mathfuncs.h"
using std::string;

class LogOperator
{
public:
    int priority;
    string symbol;
    double (*func)(int, double, double);
    LogOperator(int priority, string symbol, double (*func)(int, double, double));
    double calc(double a);
    double calc(double a, double b);
};

double stub(int countArgs, double a, double b);



#endif // LOGOPERATOR_H
