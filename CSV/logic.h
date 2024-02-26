#ifndef LOGIC_H
#define LOGIC_H
#pragma once
#include<cstdio>
#include<arrays.h>
#include<enterpoint.h>
#include<libraries/mystring.h>

int openFile(char* file, DBookList* DArray, Queue* queue);
int displayData(DBookList* DArray, Queue* queue, char* region, int column, MyData *vals);
#endif // LOGIC_H
