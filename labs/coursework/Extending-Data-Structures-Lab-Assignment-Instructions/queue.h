#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* frontPtr;
    Node* backPtr;

public:
    Queue() : frontPtr(nullptr), backPtr(nullptr) {}

    void push(const T& value) {
        Node* n = new Node(value);
        if (!backPtr) {
            frontPtr = backPtr = n;
        } else {
            backPtr->next = n;
            backPtr = n;
        }
    }

    T pop() {
        Node* old = frontPtr;
        T val = old->data;
        frontPtr = frontPtr->next;
        if (!frontPtr) backPtr = nullptr;
        delete old;
        return val;
    }

    bool empty() const {
        return frontPtr == nullptr;
    }
};

#endif
