#pragma once
#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H


#include "logic.h"
#include"arrays.h"

enum Operation {
    LoadData,
    DisplayData,
    Change
};

enum Errors{
    OK,
    FileNotFound=-50
};

int doOperation(int operation, char* file, DBookList* DArray, Queue* queue, char* region, int column, MyData* vals);

#endif // ENTRYPOINT_H
