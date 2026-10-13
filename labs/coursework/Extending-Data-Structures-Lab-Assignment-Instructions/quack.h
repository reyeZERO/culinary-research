#ifndef QUACK_H
#define QUACK_H

template <typename T>
class Quack {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node* frontPtr;
    Node* backPtr;

public:
    Quack() : frontPtr(nullptr), backPtr(nullptr) {}

    void push_front(const T& value) {
        Node* n = new Node(value);
        if (!frontPtr) {
            frontPtr = backPtr = n;
        } else {
            n->next = frontPtr;
            frontPtr->prev = n;
            frontPtr = n;
        }
    }

    void push_back(const T& value) {
        Node* n = new Node(value);
        if (!backPtr) {
            frontPtr = backPtr = n;
        } else {
            backPtr->next = n;
            n->prev = backPtr;
            backPtr = n;
        }
    }

    T pop_front() {
        Node* old = frontPtr;
        T val = old->data;
        frontPtr = frontPtr->next;
        if (frontPtr) frontPtr->prev = nullptr;
        else backPtr = nullptr;
        delete old;
        return val;
    }

    T pop_back() {
        Node* old = backPtr;
        T val = old->data;
        backPtr = backPtr->prev;
        if (backPtr) backPtr->next = nullptr;
        else frontPtr = nullptr;
        delete old;
        return val;
    }

    bool empty() const {
        return frontPtr == nullptr;
    }
};

#endif
