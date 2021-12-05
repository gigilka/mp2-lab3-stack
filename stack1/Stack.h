#pragma once
#include <iostream>

template <class T>
class TStack {
    T* a;
    int size;
    int p;
public:
    TStack(int s = 64);
    ~TStack();
    TStack(const TStack& st);
    TStack& operator=(const TStack& st);
    bool operator==(const TStack& st) const;
    bool operator!=(const TStack& st) const;
    bool IsEmpty() const;
    bool IsFull() const;
    void Clear();
    void Push(T smt);
    T Pop();
    T Top() const;
    friend std::ostream& operator<<(std::ostream& out, const TStack& st){
        for (int i = 0; i <= st.p; i++)
            out << st.a[i] << ' ';
        return out;
    }
};
template <class T>
TStack<T>::TStack(int s) {
    if (s <= 0) {
        throw "Incorrect size";
    }
    size = s;
    a = new T[size];
    p = -1;
}
template <class T>
TStack<T>::~TStack() {
    delete[] a;
}
template <class T>
TStack<T>::TStack(const TStack& st) {
    size = st.size;
    p = st.p;
    a = new T[size];
    for (int i = 0; i < size; i++) {
        a[i] = st.a[i];
    }
}
template <class T>
TStack<T>& TStack<T>::operator=(const TStack& st) {
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
bool TStack<T>::operator==(const TStack& st) const {
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
bool TStack<T>::operator!=(const TStack& st) const {
    return !operator==(st);
}
template <class T>
bool TStack<T>::IsEmpty() const {
    return p == -1;
}
template <class T>
bool TStack<T>::IsFull() const {
    return (p == size - 1);
}
template <class T>
void TStack<T>::Clear() {
    p = -1;
}
template <class T>
void TStack<T>::Push(T smt) {
    if (IsFull()) {
        throw "TStack overflow";
    }
    p++;
    a[p] = smt;
}
template <class T>
T TStack<T>::Pop() {
    if (IsEmpty()) {
        throw "Empty stack";
    }
    T smt = a[p];
    p--;
    return smt;
}
template <class T>
T TStack<T>::Top() const {
    if (IsEmpty()) {
        throw "Empty stack";
    }
    return a[p];
}