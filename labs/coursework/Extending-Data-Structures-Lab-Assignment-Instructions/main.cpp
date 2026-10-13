#include <iostream>
#include "queue.h"
#include "quack.h"

int main() {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << q.pop() << "\n";
    std::cout << q.pop() << "\n";

    Quack<int> dq;
    dq.push_front(10);
    dq.push_back(20);
    dq.push_front(5);

    std::cout << dq.pop_front() << "\n";
    std::cout << dq.pop_back() << "\n";

    return 0;
}
