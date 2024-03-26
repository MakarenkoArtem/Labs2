#include"enterpoint.h"

int doOperation(int operation, AppContext* context, AppParams* params){//char* file, AllData* DArray, Queue* queue, char* region, int column, StatisticData* vals){
    switch(operation){
    case Initialization:
        return initialization(context, params);
    case LoadData:
        return openFile(context, params);
    case DisplayData:
        return displayData(context, params);
    case SortData:
        return sortData(context, params);
    /*case Change:{
        int t= changing(data, newData);
        if (t){return t;}
        return OK;}
        //return counting(data, newData);}*/
}
}
