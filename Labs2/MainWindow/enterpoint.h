#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "data.h"
#include "logic.h"

enum Operation {
    Validation,
    Counting,
    Change,
    Copy
};


void doOperation(Operation operation, Data* data, NewData* newData);


#endif // ENTRYPOINT_H
