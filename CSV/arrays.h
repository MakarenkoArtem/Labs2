#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdlib.h>
const int SIZE = 50;
struct Row {
    int year;
    char* region;
    float npg, birth_rate, death_rate, gdw, urbanization;
};


struct Node {
    Row data;  // поле данных
    Node* next; // поле связей
};

/*======DynamicList=======*/
struct AllData {
    Row* rows;
    int size;
};
void dynamicClearList(AllData* allData);
void dynamicAddRow(AllData* allData, Row row, int index);
void dynamicRemoveRow(AllData* allData, int index);

/*======Queue=======*/
struct Queue {
    Node *head, *tail;
    int size;
};

Queue initQueue();
bool isEmpty(Queue* queue);
bool pop(Row* row, Queue* queue);
void push(Queue *queue, Row row);

struct StatisticData{
    float minVal, maxVal, averageVal;
};



/*======List=======*/
struct NewNode {
    float data;  // поле данных
    NewNode* next; // поле связей
};
struct List {
    NewNode* first;
    int size;
};

List* init(float data);
//void addData(List* elem, NewNode book);
void clear(List* list);
void pushStart(List* list, float data);
void push(List* list, float data);
void pushEnd(List* list, float data);
NewNode* getOnIndex(List* list, int ind);
void deleteList(List* list);
/*
void handleBooks(List* list, void(*handler)(Book*));
*/



struct AppContext{
    char* file;
    char* region;
    int column;
};

struct AppParams{
    AllData DArray;
    Queue queue;
    StatisticData vals;
};
#endif
