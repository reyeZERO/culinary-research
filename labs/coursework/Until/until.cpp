#include <functional>
#include <cassert>
#include <iostream>

int until(int x, std::function<int(int)> f, std::function<bool(int)> g) {
    while (!g(x)) x = f(x);
    return x;
}

int main() {
    auto doubler = [](int v){ return v * 2; };
    auto gt100 = [](int v){ return v > 100; };
    assert(until(1, doubler, gt100) == 128);

    auto inc = [](int v){ return v + 1; };
    auto eq10 = [](int v){ return v == 10; };
    assert(until(3, inc, eq10) == 10);
    assert(until(10, inc, eq10) == 10);

    auto square = [](int v){ return v * v; };
    auto ge1000 = [](int v){ return v >= 1000; };
    assert(until(2, square, ge1000) == 65536);

    auto dec2 = [](int v){ return v - 2; };
    auto leNeg10 = [](int v){ return v <= -10; };
    assert(until(-3, dec2, leNeg10) == -11);

    auto id_or_add3 = [](int v){ return v < 0 ? -v : v + 3; };
    auto mult7 = [](int v){ return v % 7 == 0; };
    assert(until(1, id_or_add3, mult7) == 7);
    assert(until(-14, id_or_add3, mult7) == 14);

    auto identity = [](int v){ return v; };
    auto divisible_by_5 = [](int v){ return v % 5 == 0; };
    assert(until(5, identity, divisible_by_5) == 5);
    assert(until(6, [](int v){ return v + 4; }, divisible_by_5) == 10);

    std::cout << "OK\n";
    return 0;
}
