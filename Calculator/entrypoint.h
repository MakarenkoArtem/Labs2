#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#pragma once

#include "datatypes.h"
#include "logic.h"
enum Operation {
    AddChar,
    DelChar,
    Calc,
    RevFunc
};

int doOperation(int operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
