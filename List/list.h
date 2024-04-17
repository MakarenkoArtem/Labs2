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
    T val;
    Node *next;
};

template<typename T>
class ConstIterator : public std::iterator<std::random_access_iterator_tag, T> {
protected:
    const list<T> *container_;
    Node<T> *val;

    ConstIterator(const list<T> &container_obj, Node<T> *val) :
            container_(&container_obj),
            val(val) {};
public:
    ConstIterator(const list<T> &container_obj) : container_(&container_obj),
                                                  val(container_obj.head) {};

    ConstIterator<T> next() const;

    T value();

    bool is_end();

    ConstIterator<T> &operator++() const;

    bool operator==(const ConstIterator<T> &b);

    bool operator!=(const ConstIterator<T> &b);

    T &operator*();

    ConstIterator<T> operator+(const int num) const;
};

template<typename T>
class Iterator : public ConstIterator<T> {
public:

    Iterator(list<T> &container_obj) : ConstIterator<T>(container_obj) {};

    void operator=(const T &val);

    Iterator<T> operator+(int num);

    Iterator<T> next();

};

template<typename T>
ConstIterator<T> ConstIterator<T>::next() const {
    if (val->next == nullptr) {
        throw std::out_of_range("");
    }
    return ConstIterator<T>(*container_, val->next);
};

template<typename T>
Iterator<T> Iterator<T>::next() {
    if (this->val->next == nullptr) {
        throw std::out_of_range("");
    }
    this->val = this->val->next;
    return *this;
};

template<typename T>
T ConstIterator<T>::value() {
    return val->val;
}

template<typename T>
bool ConstIterator<T>::is_end() {
    return val->next == nullptr;
}

template<typename T>
ConstIterator<T> &ConstIterator<T>::operator++()const {
    *this = next();
    return *this;
}

template<typename T>
T &ConstIterator<T>::operator*() {
    return val->val;
}

template<typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T> &b) {
    return this->val == b.val;
}

template<typename T>
bool ConstIterator<T>::operator!=(const ConstIterator<T> &b) {
    return !(*this == b);
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator+(const int num) const {
    for (int i = 0; i != num; ++i) {
        ++(*this);
    }
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator+(const int num) {
    for (int i = 0; i != num; ++i) {
        next();
    }
    return *this;
}

template<typename T>
void Iterator<T>::operator=(const T &val) {
    this->val->val = val;
}


template<typename T>
class list {

    friend class ConstIterator<T>;

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

    int get_length() const;

    void add(const T &elem);

    void add_range(const list<T> &lst);

    void add_range(T *arr, int size);

    void set_elem(int index, const T &elem);

    T &get_elem(int index);

    void remove_elem(int index);

    T &operator[](int index);

    Iterator<T> begin();

    ConstIterator<T> cbegin() const;

    Iterator<T> end();

    ConstIterator<T> cend() const;
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
int list<T>::get_length() const {
    return sz;
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
void list<T>::add_range(const list<T> &lst) {
    /*auto tmp = lst.head;
    for (int i = 0; i != lst.sz; ++i) {
        add(tmp->val);
        tmp = tmp->next;
    }*/
//    auto it: lst.begin();
    //for (auto it: lst) {
    for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
        add(*it);
        //++it;
    }
}

template<typename T>
void list<T>::add_range(T *arr, int size) {
    for (int i = 0; i != size; add(arr[i++]));
}

template<typename T>
void list<T>::set_elem(int index, const T &elem) {
    begin() + index = elem;
}

template<typename T>
T &list<T>::get_elem(int index) {
    if (index < 0 || index >= sz) {
        throw std::out_of_range("");
    }
    return *(begin() + index);
    /*auto tmp = head;
    for (int i = 0; i != index; ++i) {
        tmp = tmp->next;
    }
    return tmp->val;*/
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

/*
template<typename T>
list<T> list<T>::combine(const list<T> &lst){
    list<T>* tmp =
}*/

template<typename T>
T &list<T>::operator[](int index) {
    if (index < 0 || index >= sz) {
        throw std::out_of_range("");
    }
    Node<T> *tmp = head;
    for (int i = 0; i < index; ++i) {
        tmp = tmp->next;
    }
    return *(begin() + index);
}

template<typename T>
Iterator<T> list<T>::begin() {
    return Iterator<T>(*this);
};

template<typename T>
ConstIterator<T> list<T>::cbegin() const {
    return ConstIterator<T>(*this);
};

template<typename T>
Iterator<T> list<T>::end() {
    return Iterator<T>(*this) + sz - ((bool) sz);
};

template<typename T>
ConstIterator<T> list<T>::cend() const {
    return ConstIterator<T>(*this) + (sz - ((bool) sz));
}

#endif //LIST_LIST_H
