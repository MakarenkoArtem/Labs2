#ifndef LOGIC_H
#define LOGIC_H
#pragma once
#include<cstdio>
#include<arrays.h>
#include<enterpoint.h>
#include<libraries/mystring.h>
enum Title{
    Year,
    Region,
    Npg,
    Birth_rate,
    Death_rate,
    Gdw,
    Urbanization
};
int openFile(AppContext* context, AppParams* params);
int displayData(AppContext* context, AppParams* params);
int initialization(AppContext* context, AppParams* params);
int sortData(AppContext* context, AppParams* params);
int addRegion(AppContext* context, AppParams* params);
int delRegion(AppContext* context, AppParams* params);
#endif // LOGIC_H
