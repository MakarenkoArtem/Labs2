#include "arrays.h"
#include "libraries/mystring.h"

void clearListString(ListStrings* list){
   freeMatrixStr(list->titles, list->count);
}

void dynamicAddRow(AllData* rows, Row row, int index) {
    rows->size++;
    rows->rows = (Row*)realloc(rows->rows, rows->size * sizeof(Row));
    for (int i = rows->size; i == index; i--)
        rows->rows[i] = rows->rows[i - 1];
    rows->rows[index] = row;
}

void dynamicRemoveRow(AllData* rows, int index) {
    for (int i = index; i < rows->size; i++)
        rows->rows[i] = rows->rows[i + 1];
    rows->size--;
    rows->rows = (Row*)realloc(rows->rows, rows->size * sizeof(Row));
}
void dynamicClearList(AllData* rows) {
    for (int i = 0; i < rows->size; i++){
        free(rows->rows[i].region);
    }
    free(rows->rows);
    rows->size=0;
    rows->rows = (Row*)malloc(rows->size * sizeof(Row));
}


Queue initQueue() {
    Queue queue;
    queue.head = NULL;
    queue.tail = NULL;
    queue.size=0;
    return queue;
}

bool isEmpty(Queue* queue) {
    return !queue->head;
}

bool pop(Row* row, Queue* queue) {
    if(isEmpty(queue))
        return false;

    Node* node = queue->head;
    *row = node->data;

    queue->head = node->next;

    free(node);
    --queue->size;
    return true;

}

void push(Queue *queue, Row row) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = row;
    node->next = NULL;

    if(isEmpty(queue))
        queue->head = queue->tail = node;
    else
        queue->tail->next = node;

    queue->tail = node;
    ++queue->size;
}



/*========List=======*/

List* init(float data) {
    List* list=(List*)malloc(sizeof(List));
    NewNode* root = (NewNode*) malloc(sizeof(NewNode));
    root->data = data;
    root->next = NULL; // следующий элемент списка
    // Если поддерживается стандарт c++ 20, то можно использовать именованные параметры:
    // return List{ .first = root };
    list->first= root;
    list->size= 1;
    return list;
}

void pushStart(List* list, float data) {
    NewNode* node = (NewNode*)malloc(sizeof(NewNode));

    node->data = data;
    node->next = list->first;

    list->first = node;
    ++list->size;
}
void push(List* list, float data) {
    if(data<=list->first->data){
        return pushStart(list, data);
    }
    NewNode* p=list->first;
    NewNode* node = (NewNode*)malloc(sizeof(NewNode));
    while(p->next!=nullptr && p->next->data<data){
        p=p->next;
    }
    if(p->next==nullptr){
        return pushEnd(list, data);
    }
    node->data = data;
    node->next = p->next;
    p->next=node;
    ++list->size;
}
void pushEnd(List* list, float data) {
    ++list->size;
    NewNode* node = (NewNode*)malloc(sizeof(NewNode));
    node->data = data;
    node->next = NULL;
    if (list->first == NULL) {
        list->first = node;
    } else {
        NewNode* temp = list->first;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = node;
    }
}
NewNode* getOnIndex(List* list, int ind) {
    if(ind<0 || ind>=list->size){return (NewNode*)-1;}
    NewNode* p = list->first;
    for(int i=1;i<ind;++i){
        p=p->next;
    }
    return p;
}

void deleteList(List* list) {
    NewNode* p = list->first;
    while (p->next) {
        NewNode* temp = p;
        p = p->next;
        free(temp);
    }
    free(p);                     // возможно повтороное освобождение памяти
    free(list);
}
/*
void printrows(List* list) {
    NewNode* p = list->first;

    if (p == NULL)
        return;

    do {
        printf("%p ", &(p->data));  // вывод адреса элемента p->data
        p = p->next;                // переход к следующему узлу
    } while (p != NULL);
}

void printHandler(NewNode* row) {
    printf("%f ", row);
}*/
/*
void handlerows(List* list, void(*handler)(row*)) {
    NewNode* p = list->first;

    if (p == NULL)
        return;

    do {
        handler(&(p->data));
        p = p->next;
    } while (p != NULL);
}*/
