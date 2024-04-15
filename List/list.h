//
// Created by artem on 15.04.24.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <iostream>
template<typename T>
struct Node{
    int val;
    Node* next;
};
template<typename T>
class list {
private:
    Node<T>* head;
    size_t sz;
public:
    list();
    list(const list<T>& lst);
    list(list<T>&& list);
    void add(const T& elem);
};

template<typename T>
list<T>::list():head(NULL), sz(0) {}


#endif //LIST_LIST_H
