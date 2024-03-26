#pragma once
#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H


#include "logic.h"
#include"arrays.h"

enum Operation {
    Initialization,
    LoadData,
    DisplayData,
    Change,
    SortData
};

enum Errors{
    OK,
    FileNotFound=-50
};


int doOperation(int operation, AppContext* context, AppParams* params);//, char* file, AllData* DArray, Queue* queue, char* region, int column, StatisticData* vals);

#endif // ENTRYPOINT_H
