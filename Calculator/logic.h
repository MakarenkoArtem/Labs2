#ifndef LOGIC_H
#define LOGIC_H
#pragma once
#include <math.h>
#include "datatypes.h"
#include <QDebug>
#include <string>
using std::string;

int addChar(AppContext* context, AppParams* params);
int delChar(AppContext* context, AppParams* params);
int digitToNums(AppContext* context, AppParams* params);
int calc(AppContext* context, AppParams* params);
#endif // LOGIC_H
