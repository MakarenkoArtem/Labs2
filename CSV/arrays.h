#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdlib.h>
const int SIZE = 50;
struct Book {
    int year;
    char* region;
    float npg, birth_rate, death_rate, gdw, urbanization;
};

struct LinkedNode {
    Book data;
    LinkedNode* next;
    LinkedNode* prev;
};

struct Node {
    Book data;  // поле данных
    Node* next; // поле связей
};


/*======StaticList=======*/
// Список на базе статического массива
struct SBookList {
    Book books[SIZE];
    int size;
};

void staticAddBook(SBookList* books, Book book, int index);
void staticRemoveBook(SBookList* books, int index);

/*======DynamicList=======*/
struct DBookList {
    Book* books;
    int size;
};
void dynamicClearList(DBookList* books);
void dynamicAddBook(DBookList* books, Book book, int index);
void dynamicRemoveBook(DBookList* books, int index);

/*======Queue=======*/
struct Queue {
    Node *head, *tail;
};

Queue initQueue();
bool isEmpty(Queue* queue);
bool pop(Book* book, Queue* queue);
void push(Queue *queue, Book book);

struct MyData{
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




#endif // ARRAYS_H
