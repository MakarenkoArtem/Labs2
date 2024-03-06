#pragma once
#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "data.h"
#include "logic.h"

enum Operation {
    Initialization,
    Validation,
    Counting,
    Change
};


int doOperation(Operation operation, AppParams* params, AppContext* context);


#endif // ENTRYPOINT_H
