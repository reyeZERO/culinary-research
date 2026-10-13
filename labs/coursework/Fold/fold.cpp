#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <cassert>

int fold(const std::vector<int>& v, const std::function<int(int,int)>& f) {
    if (v.empty()) throw std::invalid_argument("fold: empty vector with no seed");
    int acc = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        acc = f(acc, v[i]);
    }
    return acc;
}

int fold(const std::vector<int>& v, int init, const std::function<int(int,int)>& f) {
    int acc = init;
    for (int x : v) acc = f(acc, x);
    return acc;
}

int fold_recursive(const std::vector<int>& v, const std::function<int(int,int)>& f) {
    if (v.empty()) throw std::invalid_argument("fold_recursive: empty vector with no seed");
    std::function<int(size_t)> go = [&](size_t i) -> int {
        if (i == v.size() - 1) return v[i];
        return f(v[i], go(i + 1));
    };
    return go(0);
}

int main() {
    std::vector<int> a{1, 2, 3, 4};

    auto sum = [](int x, int y){ return x + y; };
    auto prod = [](int x, int y){ return x * y; };
    auto mx = [](int x, int y){ return x > y ? x : y; };

    assert(fold(a, sum) == 10);
    assert(fold(a, prod) == 24);
    assert(fold(a, mx) == 4);

    assert(fold(a, 0, sum) == 10);
    assert(fold(a, 1, prod) == 24);

    assert(fold_recursive(a, sum) == 10);

    std::cout << "OK\n";
    return 0;
}
