#include"enterpoint.h"

void doOperation(Operation operation, Data* data, NewData* newData){
    switch(operation){
    case Validation:
        data->mes="";
        validation(data, newData);
        break;
    case Counting:
        data->val="";
        counting(data, newData);
        break;
    case Change:
        changing(data, newData);
        counting(data, newData);
        break;
    case Copy:
        copy(data, newData);
        break;
    }

}
