#pragma once
#include <iostream>

template <class T>
class Stack {
    T* a;
    int size;
    int p;
public:
    Stack(int s = 64);
    ~Stack();
    Stack(const Stack& st);
    Stack& operator=(const Stack& st);
    bool operator==(const Stack& st) const;
    bool operator!=(const Stack& st) const;
    bool IsEmpty() const;
    bool IsFull() const;
    void Clear();
    void Push(T smt);
    T Pop();
    T Top() const;
    friend std::ostream& operator<<(std::ostream& out, const Stack& st){
        for (int i = 0; i <= st.p; i++)
            out << st.a[i] << ' ';
        return out;
    }
};
template <class T>
Stack<T>::Stack(int s) {
    if (s <= 0) {
        throw "Incorrect size";
    }
    size = s;
    a = new T[size];
    p = -1;
}
template <class T>
Stack<T>::~Stack() {
    delete[] a;
}
template <class T>
Stack<T>::Stack(const Stack& st) {
    size = st.size;
    p = st.p;
    a = new T[size];
    for (int i = 0; i < size; i++) {
        a[i] = st.a[i];
    }
}
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& st) {
    if (size != st.size) {
        delete[] a;
        size = st.size;
        a = new T[size];
    }
    p = st.p;
    for (int i = 0; i < size; i++) {
        a[i] = st.a[i];
    }
    return *this;
}
template <class T>
bool Stack<T>::operator==(const Stack& st) const {
    if (size != st.size) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (a[i] != st.a[i]) {
            return false;
        }
    }
    return true;
}
template <class T>
bool Stack<T>::operator!=(const Stack& st) const {
    return !operator==(st);
}
template <class T>
bool Stack<T>::IsEmpty() const {
    return p == -1;
}
template <class T>
bool Stack<T>::IsFull() const {
    return (p == size - 1);
}
template <class T>
void Stack<T>::Clear() {
    p = -1;
}
template <class T>
void Stack<T>::Push(T smt) {
    if (IsFull()) {
        throw "Stack overflow";
    }
    p++;
    a[p] = smt;
}
template <class T>
T Stack<T>::Pop() {
    if (IsEmpty()) {
        throw "Empty stack";
    }
    T smt = a[p];
    p--;
    return smt;
}
template <class T>
T Stack<T>::Top() const {
    if (IsEmpty()) {
        throw "Empty stack";
    }
    return a[p];
}