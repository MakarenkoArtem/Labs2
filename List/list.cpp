//
// Created by artem on 15.04.24.
//

#include "list.h"
/*
template<typename T>
list<T>::list():head(NULL), sz(0) {}
*/
template<typename T>
list<T>::list(const list<T> &lst):head(nullptr),sz(lst.sz) {
    if (!sz) {
        return;
    }
    Node<T> *cur = lst.head;
    head = new Node<T>{cur->val, nullptr};
    Node<T> *tmp = head;
    for (int i = 1; i < lst->sz; ++i) {
        cur=cur->next;
        tmp.next = new Node<T>{cur->val, nullptr};
        tmp=tmp->next;
    }
}

template<typename T>
list<T>::list(list<T> &&list) {}

template<typename T>
void list<T>::add(const T& elem){
    Node<T>* tmp = head;
    for(;tmp->next!= nullptr;tmp=tmp->next);
    tmp.next=new Node<T>(elem, nullptr);
}