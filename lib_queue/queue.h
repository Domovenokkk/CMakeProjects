#ifndef QUEUE_QUEUE_H_
#define QUEUE_QUEUE_H_

#include <iostream>
#include "../lib_stack/stack.h"

template <class T>
class TQueue {
    size_t size;
    size_t currentSize;
    Stack<T>* data;

public:
    TQueue() : size(100), currentSize(0), data(new Stack<T>(100)) {}
    explicit TQueue(size_t size_) : size(size_), currentSize(0), data(new Stack<T>(size_)) {}

    ~TQueue() {
        delete data;
    }

    bool isEmpty() const {
        return data->isEmpty();
    }

    bool isFull() const {
        return currentSize == size;
    }

    void push(T val) {
        if (!isFull()) {
            data->push(val);
            currentSize++;
        }
        else {
            throw std::runtime_error("Queue is full");
        }
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        T value = data->getTop();
        data->pop();
        currentSize--;
        return value;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    size_t getSize() const {
        return currentSize;
    }

    T front() const {
        if (!isEmpty()) {
            return data->getTop();
        }
        else {
            throw std::runtime_error("Queue is empty");
        }
    }

    void print() const {
        Stack<T>* temp = new Stack<T>(*data);
        while (!temp->isEmpty()) {
            std::cout << temp->pop() << " ";
        }
        std::cout << std::endl;
        delete temp;
    }
};

#endif // QUEUE_QUEUE_H_