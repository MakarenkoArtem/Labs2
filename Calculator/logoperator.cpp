#include "logoperator.h"

LogOperator::LogOperator(int priority, string symbol, double (*func)(int, double, double)):priority(priority), symbol(symbol), func(func){
}
LogOperator::LogOperator(int priority, string symbol, double (*func)(int, double, double), bool haveOnlyOneArgFunc, bool haveOnlyTwoArgFunc):
                    priority(priority),symbol(symbol), func(func), haveOnlyOneArgFunc(haveOnlyOneArgFunc), haveOnlyTwoArgFunc(haveOnlyTwoArgFunc){
}

double LogOperator::calc(double a){
    if(haveOnlyTwoArgFunc){
        throw std::invalid_argument("\""+symbol+"\" дожен(а) иметь только 2 аргумента");
    }
    return func(1, 0,a);
}
double LogOperator::calc(double a, double b){
    if(haveOnlyOneArgFunc){
        throw std::invalid_argument("\""+symbol+"\" дожен(а) иметь только 1 аргумент");
    }
    return func(2, a,b);
}
double stub(int countArgs, double a, double b){throw std::invalid_argument("Вызывается функция загушка");}
