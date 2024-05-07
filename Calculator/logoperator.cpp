#include "logoperator.h"

LogOperator::LogOperator(int priority, string symbol, double (*func)(int, double, double)):priority(priority), symbol(symbol), func(func){
}

double LogOperator::calc(double a){
    return func(1, 0,a);
}
double LogOperator::calc(double a, double b){
    return func(2, a,b);
}
double stub(int countArgs, double a, double b){throw std::invalid_argument("Вызывается функция загушка");}
