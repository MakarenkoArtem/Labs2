#ifndef TYPESDATA_H
#define TYPESDATA_H
#include "logoperator.h"
struct Node{
    bool typeOper;
    union{
        double val;
        LogOperator* oper;
    } value;
    //Node* next;
};
#endif // TYPESDATA_H
