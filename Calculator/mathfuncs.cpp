#include "mathfuncs.h"
double summ(int countArgs, double a, double b){
    if(countArgs!=2){
        throw std::invalid_argument("Сумма должна иметь 2 аргумента");
    }
    double res = a+b;
    if (a>0 && b>0 && (res <a || res<b)){
        throw std::out_of_range("Число больше размеров double");
    }
    if (a<0 && b<0 && (res >a || res>b)){
        throw std::out_of_range("Число больше размеров double со знаком минус");
    }
    return res;
}

double minu(int countArgs, double a, double b){
    switch(countArgs){
    case 1:
        return -b;
    case 2:
        return summ(2, a, -b);
    default:
        throw std::invalid_argument("Разность должна иметь 2 аргумента");
    }
}

double mult(int countArgs, double a, double b){
    if(countArgs!=2){
        throw std::invalid_argument("Произведение должно иметь 2 аргумента");
    }
    long double resLong = a*b;
    double res = a*b;
    if (resLong!=res){
        throw std::out_of_range("Число больше размеров double");
    }
    return res;
}
double divi(int countArgs, double a, double b){
    if(countArgs!=2){
        throw std::invalid_argument("Деление должно иметь 2 аргумента");
    }
    if(!b){throw std::invalid_argument("Division by zero");}
    return a/b;
}

double sqrtFunc(int countArgs, double a, double b){
    if(countArgs!=1){
        throw std::invalid_argument("Извлечение корня должно иметь 1 аргумент");
    }
    return std::sqrt(b);
}

double sinFunc(int countArgs, double a, double b){
    if(countArgs!=1){
        throw std::invalid_argument("Синунс должен иметь 1 аргумент");
    }
    return std::sin(b);
}

double cosFunc(int countArgs, double a, double b){
    if(countArgs!=1){
        throw std::invalid_argument("Косинус должен иметь 1 аргумент");
    }
    return std::cos(b);
}
double tgFunc(int countArgs, double a, double b){
    if(countArgs!=1){
        throw std::invalid_argument("Тангенс должен иметь 1 аргумент");
    }
    return std::tan(b);
}
double ctgFunc(int countArgs, double a, double b){
    if(countArgs!=1){
        throw std::invalid_argument("Котангенс должен иметь 1 аргумент");
    }
    return 1/std::tan(b);
}
