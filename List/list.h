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
class Iterator : public std::iterator<std::input_iterator_tag, T> {
public:
    const list<T> *container_;
    Node<T> *val;

    Node<T> &getNode() {
        return *val;
    }


    Iterator(list<T> &container_obj) : container_(&container_obj),
                                       val(container_obj.head) {};

    Iterator(list<T> &container_obj, Node<T> *val) : container_(&container_obj),
                                                     val(val) {};

    Iterator(const list<T> &container_obj) : container_(&container_obj),
                                             val(container_obj.head) {};

    Iterator(const list<T> &container_obj, Node<T> *val) : container_(
            &container_obj),
                                                           val(val) {};

    void operator=(T val) {
        this->val->val = val;
    }

    Iterator<T> operator+(int num) {
        if (!num) { return *this; }
        return this->next() + --num;
    }

    Iterator<T> next() {
        if (val == nullptr) {
            throw std::out_of_range("Iterator out of range");
        }
        return Iterator<T>(*container_, val->next);
    }

    T value() {
        return val->val;
    }

    bool is_end() {
        return val == nullptr;
    }

    Iterator<T> operator++() {
        if (val == nullptr) {
            throw std::out_of_range("");
        }
        val = val->next;
        return *this;
    }

    bool operator==(Iterator<T> b) {
        return val == b.val;
    }

    bool operator!=(Iterator<T> b) {
        return !(*this == b);
    }

    T &operator*() {
        return val->val;
    }

};

template<typename T>
class ConstIterator : public Iterator<T> {
    ConstIterator(const list<T> &container_obj, Node<T> *val) : Iterator<T>(
            container_obj, val) {};
public:
    ConstIterator(const list<T> &container_obj) : Iterator<T>(
            (list<T> &) container_obj) {};

    ConstIterator<T> operator+(int num) {
        if (!num) { return *this; }
        return this->next() + --num;
    }

    ConstIterator<T> next() const {
        if (this->val == nullptr) {
            throw std::out_of_range("Iterator out of range");
        }
        return ConstIterator<T>(*this->container_, this->val->next);
    }
};

template<typename T>
class list {
protected:
public:
    Node<T> *head;
    size_t sz;

    list() : head(nullptr), sz(0) {}

    list(const list<T> &lst) : head(nullptr), sz(lst.sz) {
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

    list(list<T> &&list) : head(list.head), sz(list.sz) {
        list.head = nullptr;
        list.sz = 0;
    }

    explicit list(std::initializer_list<T> lst) : head(nullptr), sz(0) {
        auto c = begin();
        for (auto it: lst) {
            add(it);
        }
    }

    ~list() {
        Node<T> *tmp;
        while (tmp != nullptr) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    list<T> &operator=(const list<T> &lst) {
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

    int get_length() const { return sz; }

    void add(const T &elem) {
        ++sz;
        if (head == nullptr) {
            head = new Node<T>{elem, nullptr};
            return;
        }
        (begin() + (sz - 2)).val->next = new Node<T>{elem, nullptr};
    }

    void add_range(const list<T> &lst) {
        for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
            add(*it);
        }
    }

    void add_range(T *arr, int size) {
        for (int i = 0; i != size; add(arr[i++]));
    }

    void set_elem(int index, const T &elem) {
        begin() + index = elem;
    }

    T &get_elem(int index) {
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

    void remove_elem(int index) {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("");
        }
        --sz;
        if (index == 0) {
            Node<T> *tmp = head;
            head = head->next;
            delete tmp;
        } else {
            auto t = *((begin() + index).val);
            (begin() + index + 1).val.next = t.next;
            delete t;
        }
    }

    list<T> combine(const list<T> &lst) {
        list<T> tmp(*this);
        for (auto it: lst) {
            tmp.add(it);
        }
        return tmp;
    }

    void sort(int (*comp)(const T &r1, const T &r2)) {
        for (int i = sz - 1; i; --i) {
            for (auto it = begin(); it != begin() + i; ++it) {
                if (comp(*(it + 1), *it) == 1) {
                    T val = *it;
                    it = *(it + 1);
                    it + 1 = val;
                }
            }
        }
    }

    int get_index(T &elem) const {
        int i = 0;
        for (auto it: this) {
            if (*it == elem) {
                return i;
            }
            ++i;
        }
        return -1;
    }

    T *to_array() {
        T *arr = malloc(sizeof(T) * sz);
        T *a = arr;
        for (auto it: this) {
            *(a++) = *it;
        }
        return arr;
    }

    T &operator[](int index) {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("");
        }
        return *(begin() + index);
    }

    Iterator<T> begin() {
        return Iterator<T>(*this);
    }

    ConstIterator<T> cbegin() const {
        return ConstIterator<T>(*this);
    };

    Iterator<T> end() {
        return Iterator<T>(*this) + sz;
    };

    ConstIterator<T> cend() const {
        return ConstIterator<T>(*this) + sz;
    }
};


/*==========================================================================*/
/*template<typename T>
Iterator<T> &Iterator<T>::operator++() {
    if (val == nullptr) {
        throw std::out_of_range("Out of range");
    }
    val = val->next;
    return *this;
    //return Iterator<T>(*container_, val->next);
};


template<typename T>
T Iterator<T>::value() {
    return val->val;
}

template<typename T>
bool Iterator<T>::is_end() {
    return val == nullptr;//?
}

template<typename T>
Iterator<T> Iterator<T>::next() {
    if (val == nullptr) {
        throw std::out_of_range("Iterator out of range");
    }
    return Iterator<T>(*container_, val->next);
}

template<typename T>
T &Iterator<T>::operator*() {
    return val->val;
}

template<typename T>
bool Iterator<T>::operator==(Iterator<T> b) {
    return val == b.val;
}

template<typename T>
bool Iterator<T>::operator!=(Iterator<T> b) {
    return !(*this == b);
}

/*
template<typename T>
ConstIterator<T> ConstIterator<T>::operator+(const int num) const {
    return this->Iterator<T>::operator+(num);
    //return *this;
}

template<typename T>
Iterator<T> &Iterator<T>::operator+(int num) {
    while (num--) {
        ++(*this);
    }
    return *this;
}

template<typename T>
void Iterator<T>::operator=(T val) {
    this->val->val = val;
}


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
//    auto it: lst.begin();
    //for (auto it: lst) {
    for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
        add(*it);
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
list<T> list<T>::combine(const list<T> &lst){
    list<T>* tmp =
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
    return *(begin() + index);
}

template<typename T>
Iterator<T> list<T>::begin() {
    return Iterator<T>(*this);
}

template<typename T>
ConstIterator<T> list<T>::cbegin() const {
    return ConstIterator<T>(*this);
};

template<typename T>
Iterator<T> list<T>::end() {
    return Iterator<T>(*this) + sz;
};

template<typename T>
ConstIterator<T> list<T>::cend() const {
    return ConstIterator<T>(*this) + sz;
}
*/
#endif //LIST_LIST_H
