#include"enterpoint.h"

int doOperation(int operation, char* file, DBookList* DArray, Queue* queue, char* region, int column, MyData* vals){
    switch(operation){
    case LoadData:
        return openFile(file, DArray, queue);
    case DisplayData:
        return displayData(DArray, queue, region, column, vals);
    /*case Change:{
        int t= changing(data, newData);
        if (t){return t;}
        return OK;}
        //return counting(data, newData);}*/
}
}
