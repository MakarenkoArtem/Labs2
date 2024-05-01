//
// Created by artem on 15.04.24.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <exception> // Подключение библиотеки для работы с исключениями
#include <iostream> // Подключение библиотеки для стандартного ввода-вывода
#include <iterator> // Подключение библиотеки для работы с итераторами

// Объявление класса list для предварительного объявления шаблонных функций
template<typename T>
class list;

// Структура узла списка, содержащая значение и указатель на следующий узел
template<typename T>
struct Node {
    T val; // Значение узла
    Node *next; // Указатель на следующий узел
};

// Класс Iterator, представляющий итератор для списка
template<typename T>
class Iterator : public std::iterator<std::input_iterator_tag, T> {
public:
    const list<T> *container_; // Указатель на контейнер списка
    Node<T> *val; // Указатель на текущий узел

    // Получение ссылки на текущий узел
    Node<T> &getNode() {
        return *val;
    }

    // Конструкторы итератора
    Iterator(list<T> &container_obj) : container_(&container_obj),
                                       val(container_obj.head) {};

    Iterator(list<T> &container_obj, Node<T> *val) : container_(&container_obj),
                                                     val(val) {};

    Iterator(const list<T> &container_obj) : container_(&container_obj),
                                             val(container_obj.head) {};

    Iterator(const list<T> &container_obj, Node<T> *val) : container_(
            &container_obj),
                                                           val(val) {};

    // Оператор присваивания значения текущему узлу
    void operator=(T val) {
        this->val->val = val;
    }

    // Оператор сложения итератора с числом
    Iterator<T> operator+(int num) {
        if (!num) { return *this; }// Если число равно нулю, возвращаем текущий итератор
        return this->next() +
               --num;// Рекурсивно вызываем оператор сложения для получения итератора, смещенного на num узлов вперед
    }

    // Получение следующего итератора
    Iterator<T> next() {
        if (val == nullptr) {
            throw std::out_of_range("Iterator out of range");
        }
        return Iterator<T>(*container_, val->next);
    }

    // Получение значения текущего узла
    T value() {
        return val->val;
    }

    // Проверка, является ли текущий узел конечным
    bool is_end() {
        return val == nullptr;
    }

    // Переход к следующему узлу
    Iterator<T> operator++() {
        if (val == nullptr) {
            throw std::out_of_range("");
        }
        val = val->next;
        return *this;
    }

    // Проверка на равенство итераторов
    bool operator==(Iterator<T> b) {
        return val == b.val;
    }

    // Проверка на неравенство итераторов
    bool operator!=(Iterator<T> b) {
        return !(*this == b);
    }

    // Перегрузка оператора разыменования
    T &operator*() {
        return val->val;
    }

};

// Класс ConstIterator, представляющий константный итератор для списка
template<typename T>
class ConstIterator : public Iterator<T> {
    ConstIterator(const list<T> &container_obj, Node<T> *val) : Iterator<T>(
            container_obj, val) {};
public:
    ConstIterator(const list<T> &container_obj) : Iterator<T>(
            (list<T> &) container_obj) {};

    // Оператор сложения итератора с числом
    ConstIterator<T> operator+(int num) {
        if (!num) { return *this; }// Если число равно нулю, возвращаем текущий итератор
        return this->next() +
               --num;// Рекурсивно вызываем оператор сложения для получения итератора, смещенного на num узлов вперед
    }

    // Получение следующего константного итератора
    ConstIterator<T> next() const {
        if (this->val == nullptr) {
            throw std::out_of_range("Iterator out of range");
        }
        return ConstIterator<T>(*this->container_, this->val->next);
    }
};

// Класс list, представляющий односвязный список
template<typename T>
class list {
protected:
public:
    Node<T> *head; // Указатель на голову списка
    size_t sz; // Размер списка

    // Конструктор списка, устанавливает начальные значения
    list() : head(nullptr), sz(0) {}

    // Конструктор копирования списка
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

    // Конструктор перемещения списка
    list(list<T> &&list) : head(list.head), sz(list.sz) {
        list.head = nullptr;
        list.sz = 0;
    }

    // Конструктор списка на основе списка инициализаторов
    explicit list(std::initializer_list<T> lst) : head(nullptr), sz(0) {
        auto c = begin();
        for (auto it: lst) {
            add(it);
        }
    }

    // Деструктор списка, освобождает выделенную память
    ~list() {
        Node<T> *tmp;
        while (tmp != nullptr) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    // Оператор присваивания для списка
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

    // Получение длины списка
    int get_length() const { return sz; }

    // Добавление элемента в список
    void add(const T &elem) {
        ++sz;
        if (head == nullptr) {
            head = new Node<T>{elem, nullptr};
            return;
        }
        (begin() + (sz - 2)).val->next = new Node<T>{elem, nullptr};
    }

    // Добавление диапазона элементов в список
    void add_range(const list<T> &lst) {
        for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
            add(*it);
        }
    }

    // Добавление массива элементов в список
    void add_range(T *arr, int size) {
        for (int i = 0; i != size; add(arr[i++]));
    }

    // Установка элемента по индексу
    void set_elem(int index, const T &elem) {
        begin() + index = elem;
    }

    // Получение элемента по индексу
    T &get_elem(int index) {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("");
        }
        return *(begin() + index);
    }

    // Удаление элемента по индексу
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

    // Объединение двух списков
    list<T> combine(const list<T> &lst) {
        list<T> tmp(*this);
        for (auto it: lst) {
            tmp.add(it);
        }
        return tmp;
    }

    // Сортировка списка
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

    // Получение индекса элемента
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

    // Преобразование списка в массив
    T *to_array() {
        T *arr = malloc(sizeof(T) * sz);
        T *a = arr;
        for (auto it: this) {
            *(a++) = *it;
        }
        return arr;
    }

    // Перегрузка оператора доступа к элементам по индексу
    T &operator[](int index) {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("");
        }
        return *(begin() + index);
    }

    // Получение итератора на начало списка
    Iterator<T> begin() {
        return Iterator<T>(*this);
    }

    // Получение константного итератора на начало списка
    ConstIterator<T> cbegin() const {
        return ConstIterator<T>(*this);
    };

    // Получение итератора на конец списка
    Iterator<T> end() {
        return Iterator<T>(*this) + sz;
    };

    // Получение константного итератора на конец списка
    ConstIterator<T> cend() const {
        return ConstIterator<T>(*this) + sz;
    }
};

#endif //LIST_LIST_H
