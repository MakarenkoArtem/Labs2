//
// Created by artem on 15.04.24.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <exception>
#include <iostream>
#include <iterator>

template<typename T>
class list;

template<typename T>
struct Node {
    int val;
    Node *next;
};

template<typename T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {

private:
    list<T> *container_;
public:
    Node<T> *val;
    int index;

    Iterator(list<T> &container_obj) : container_(&container_obj),
                                       val(container_obj.head),
                                       index(0) {};

    Iterator<T> next();

    T value();

    bool is_end();

    Iterator<T> &operator++();

    bool operator==(Iterator<T> &b);

    bool operator!=(Iterator<T> &b);

    T &operator*();

    Iterator<T> operator+(const int num);
};

template<typename T>
Iterator<T> Iterator<T>::next() {
    if (val->next == nullptr) {
        throw std::out_of_range("");
    }
    val = val->next;
    ++index;
    return *this;
};

template<typename T>
T Iterator<T>::value() {
    return val->val;
}

template<typename T>
bool Iterator<T>::is_end() {
    return val->next == nullptr;
}

template<typename T>
Iterator<T> &Iterator<T>::operator++() {
    return next();
};

template<typename T>
T &Iterator<T>::operator*() {
    return val->val;
}

template<typename T>
bool Iterator<T>::operator==(Iterator<T> &b) {
    return *this == b;
};

template<typename T>
bool Iterator<T>::operator!=(Iterator<T> &b) {
    return !(this == b);
};

template<typename T>
Iterator<T> Iterator<T>::operator+(int num) {
    while (num--) {
        if (val->next == nullptr) {
            throw std::out_of_range("Iterator out of range");
        }
        next();
    }
    return *this;
}

template<typename T>
class list {

    friend class Iterator<T>;

protected:
    Node<T> *head;
    size_t sz;
public:
    list();

    list(const list<T> &lst);

    list(list<T> &&list);

    explicit list(std::initializer_list<T> lst);

    ~list();

    list<T> &operator=(const list<T> &lst);

    void add(const T &elem);

    T &get_elem(int index);

    void remove_elem(int index);

    T &operator[](int index);

    Iterator<T> begin();

    Iterator<T> end();
};

template<typename T>
list<T>::list():head(nullptr), sz(0) {}

template<typename T>
list<T>::list(const list <T> &lst):head(nullptr), sz(lst.sz) {
    if (!sz) {
        return;
    }
    Node<T> *cur = lst.head;
    head = new Node<T>{cur->val, nullptr};
    Node<T> *tmp = head;
    for (int i = 1; i < lst.sz; ++i) {
        cur = cur->next;
        tmp->next = new Node<T>{cur->val, nullptr};
        tmp = tmp->next;
    }
}

template<typename T>
list<T>::list(list<T> &&list):head(list.head), sz(list.sz) {
    list.head = nullptr;
    list.sz = 0;
}

template<typename T>
list<T>::list(std::initializer_list<T> lst):head(nullptr), sz(0) {
    for (auto it: lst) {
        add(it);
    }
}

template<typename T>
list<T>::~list() {
    Node<T> *tmp;
    while (tmp != nullptr) {
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

template<typename T>
list<T> &list<T>::operator=(const list<T> &lst) {
    while (sz) {
        remove_elem(0);
    }
    Node<T> *tmp = lst.head;
    for (; sz < lst.sz;) {
        add(tmp);
        tmp = tmp->next;
    }
    return *this;
}

template<typename T>
void list<T>::add(const T &elem) {
    ++sz;
    if (head == nullptr) {
        head = new Node<T>{elem, nullptr};
        return;
    }
    Node<T> *tmp = head;
    for (; tmp->next != nullptr; tmp = tmp->next);
    tmp->next = new Node<T>{elem, nullptr};
}

template<typename T>
T &list<T>::get_elem(int index) {
    if (index < 0 || index >= sz) {
        throw std::out_of_range("");
    }
    auto tmp = head;
    for (int i = 0; i != index; ++i) {
        tmp = tmp->next;
    }
    return tmp->val;
}

template<typename T>
void list<T>::remove_elem(int index) {
    if (index < 0 || index >= sz) {
        throw std::out_of_range("");
    }
    --sz;
    if (index == 0) {
        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
    } else {
        int ind = 0;
        Node<T> *anothertmp, *tmp = head;
        for (; ind != index - 1; ++ind) {
            tmp = tmp->next;
        }
        anothertmp = tmp->next;
        tmp->next = anothertmp->next;
        delete anothertmp;
    }
}

template<typename T>
T &list<T>::operator[](int index) {
    if (index < 0 || index >= sz) {
        throw std::out_of_range("");
    }
    Node<T> *tmp = head;
    for (int i = 0; i < index; ++i) {
        tmp = tmp->next;
    }
    return (begin() + index).val->val;
}

template<typename T>
Iterator<T> list<T>::begin() {
    return Iterator<T>(*this);
};

template<typename T>
Iterator<T> list<T>::end() {
    return Iterator<T>(*this) + sz - ((bool) sz);
};
#endif //LIST_LIST_H
