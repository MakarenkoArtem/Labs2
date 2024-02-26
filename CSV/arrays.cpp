#include "arrays.h"

void staticAddBook(SBookList* books, Book book, int index) {
    for (int i = books->size; i != index; i--)
        books->books[i] = books->books[i - 1];
    books->books[index] = book;
    books->size++;
}

void staticRemoveBook(SBookList* books, int index) {
    for (int i = index; i < books->size; i++)
        books->books[i] = books->books[i + 1];
    books->size--;
}

void dynamicAddBook(DBookList* books, Book book, int index) {
    books->size++;
    books->books = (Book*)realloc(books->books, books->size * sizeof(Book));
    for (int i = books->size; i == index; i--)
        books->books[i] = books->books[i - 1];
    books->books[index] = book;
}

void dynamicRemoveBook(DBookList* books, int index) {
    for (int i = index; i < books->size; i++)
        books->books[i] = books->books[i + 1];
    books->size--;
    books->books = (Book*)realloc(books->books, books->size * sizeof(Book));
}
void dynamicClearList(DBookList* books) {
    for (int i = 0; i < books->size; i++){
        free(books->books[i].region);
    }
    free(books->books);
    books->size=0;
    books->books = (Book*)malloc(books->size * sizeof(Book));
}


Queue initQueue() {
    Queue queue;
    queue.head = NULL;
    queue.tail = NULL;
    return queue;
}

bool isEmpty(Queue* queue) {
    return !queue->head;
}

bool pop(Book* book, Queue* queue) {
    if(isEmpty(queue))
        return false;

    Node* node = queue->head;
    *book = node->data;

    queue->head = node->next;

    free(node);

    return true;

}

void push(Queue *queue, Book book) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = book;
    node->next = NULL;

    if(isEmpty(queue))
        queue->head = queue->tail = node;
    else
        queue->tail->next = node;

    queue->tail = node;
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
void printBooks(List* list) {
    NewNode* p = list->first;

    if (p == NULL)
        return;

    do {
        printf("%p ", &(p->data));  // вывод адреса элемента p->data
        p = p->next;                // переход к следующему узлу
    } while (p != NULL);
}

void printHandler(NewNode* book) {
    printf("%f ", book);
}*/
/*
void handleBooks(List* list, void(*handler)(Book*)) {
    NewNode* p = list->first;

    if (p == NULL)
        return;

    do {
        handler(&(p->data));
        p = p->next;
    } while (p != NULL);
}*/
