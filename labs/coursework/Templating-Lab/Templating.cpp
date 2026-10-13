#include <vector>
#include <functional>
#include <cassert>
#include <string>
#include <cmath>
#include <iostream>

template <typename T>
std::vector<T> vec_fill(T elem) {
    std::vector<T> v(10);
    for (std::size_t i = 0; i < v.size(); ++i) v[i] = elem + static_cast<T>(i);
    return v;
}

template <typename T>
T until(T elem, std::function<T(T)> func, std::function<bool(T)> predicate) {
    while (!predicate(elem)) elem = func(elem);
    return elem;
}

template <typename T>
void order(T& a, T& b, T& c) {
    if (b > a) std::swap(a, b);
    if (c > a) std::swap(a, c);
    if (c > b) std::swap(b, c);
}

int main() {
    {
        auto v = vec_fill<int>(5);
        assert(v.size() == 10);
        assert(v.front() == 5);
        assert(v.back() == 14);
        auto v2 = vec_fill<double>(2.5);
        assert(v2.size() == 10);
        assert(std::fabs(v2.front() - 2.5) < 1e-9);
        assert(std::fabs(v2.back() - 11.5) < 1e-9);
        auto v3 = vec_fill<char>('a');
        assert(v3.size() == 10);
        assert(v3.front() == 'a');
        assert(v3.back() == 'j');
    }
    {
        int r1 = until<int>(1, [](int x){ return x*2; }, [](int x){ return x >= 100; });
        assert(r1 == 128);
        long long r2 = until<long long>(3LL, [](long long x){ return x + x + 1; }, [](long long x){ return x >= 50; });
        assert(r2 == 63);
        char r3 = until<char>('a', [](char ch){ return static_cast<char>(ch + 1); }, [](char ch){ return ch >= 'f'; });
        assert(r3 == 'f');
    }
    {
        int a=3,b=10,c=7;
        order(a,b,c);
        assert(a==10 && b==7 && c==3);
        double x=-1.2,y=-5.0,z=2.2;
        order(x,y,z);
        assert(std::fabs(x-2.2)<1e-9 && std::fabs(y+1.2)<1e-9 && std::fabs(z+5.0)<1e-9);
        std::string s1="beta", s2="alpha", s3="gamma";
        order(s1,s2,s3);
        assert(s1=="gamma" && s2=="beta" && s3=="alpha");
    }
    std::cout << "OK\n";
    return 0;
}
