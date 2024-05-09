#ifndef DATATYPES_H
#define DATATYPES_H
#include <string>
#include <vector>
#include "logoperator.h"
using std::string;
using std::vector;

enum Errors{
    OK,
    Error
};

struct Node{
    bool typeOper;
    union{
        double val;
        LogOperator* oper;
    } value;
};

struct AppContext{
    string but;
};

struct AppParams{
    double memory=0;
    vector<string> input;
    string output="";
    vector<Node> list;
    vector<LogOperator*> stack;
};

#endif // DATATYPES_H
