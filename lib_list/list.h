#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_
#include <iostream>

template <class T>
class TNode {
public:
    T data;
    TNode* next;

    TNode(const TNode& node) : data(node.data), next(node.next) { }
    explicit TNode(T _data, TNode* _next = nullptr) :
        data(_data), next(_next) { }
    ~TNode() { delete[] next; }
};

template <class T>
class TList {
    friend class TNode<T>;
    TNode* first;
    TNode* last;

public:
    TList() : first(nullptr), last(nullptr) { }
    bool isEmpty() {
        return first == nullptr;
    }
    void pushback(T data) {
        TNode<T>* p = new TNode<T>(data);
        if (isEmpty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }
    void print() {
        if (isEmpty()) return;
        TNode<T>* p = first;
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    TNode<T>* find(T _data) {
        if (isEmpty()) return nullptr;
        TNode<T>* p = first;
        while (p && p->data != _data) p = p->next;
        return (p && p->data != _data) ? p : nullptr;
    }
    void popfirst() {
        if (isEmpty()) return;
        TNode<T>* p = first;
        first = p->next;
        delete p;
    }
    void poplast() {
        if (isEmpty()) return;
        if (first == last) {
            popfirst();
            return;
        }
        TNode<T>* p = first;
        while (p->next != last) p = p->next;
        p->next = nullptr;
        delete last;
        last = p;
    }
    TNode<T>* operator[] (const int index) {
        if (is_empty()) return nullptr;
        TNode<T>* p = first;
        for (int i = 0; i < index; i++) {
            p = p->next;
            if (!p) return nullptr;
        }
        return p;
    }
};

#endif  // LIB_LIST_LIST_H_