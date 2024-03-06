#include"enterpoint.h"

int doOperation(Operation operation, AppParams* params, AppContext* context){
    switch(operation){
    case Initialization:
        return initialization(params, context);
    case Validation:{
        params->error=OK;
        char* binaryNum = copyStr(params->binaryNum);
        char* otherNum = copyStr(params->otherNum);
        char* val = copyStr(params->val);
        int decimalNum = params->decimalNum;
        int c = counting(params, context);
        qDebug("fff 2 %i", c);
        if(c!=ValueExceded){freeStr(params->binaryNum);}
        freeStr(params->otherNum);
        freeStr(params->val);
        params->binaryNum=binaryNum;
        params->otherNum=otherNum;
        params->val=val;
        params->decimalNum=decimalNum;
        return c?c:validation(params, context);
    }
    case Counting:{
        //doOperation(Validation, params, context);
        int c=counting(params, context);
        qDebug("fff 3 %i", c);
        return c;}
    /*case Change:{
        int t= changing(params, context);
        if (t){return t;}
        return OK;}
        //return counting(data, newData);}*/
}
}
