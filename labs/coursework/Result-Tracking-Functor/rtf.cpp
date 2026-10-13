#include <functional>
#include <optional>
#include <cassert>
#include <string>
#include <iostream>

template <typename R, typename A, typename B>
class BiApplier {
    std::function<R(A,B)> fn_;
    std::size_t count_ = 0;
    std::optional<R> last_;
public:
    template <typename F>
    explicit BiApplier(F f) : fn_(std::function<R(A,B)>(f)) {}
    R apply(const A& a, const B& b) {
        R r = fn_(a,b);
        last_ = r;
        ++count_;
        return r;
    }
    std::size_t calls() const { return count_; }
    const std::optional<R>& last_result() const { return last_; }
};

int add(int x, int y) { return x + y; }
double maxd(double x, double y) { return x > y ? x : y; }
std::string cat(const std::string& a, const std::string& b) { return a + b; }

int main() {
    BiApplier<int,int,int> A1(add);
    BiApplier<int,int,int> A2(add);
    BiApplier<double,double,double> B1(maxd);
    BiApplier<std::string,std::string,std::string> C1(cat);

    assert(A1.calls() == 0);
    assert(!A1.last_result().has_value());

    assert(A1.apply(2,3) == 5);
    assert(A1.apply(-4,9) == 5);
    assert(A1.calls() == 2);
    assert(A1.last_result().value() == 5);

    assert(A2.apply(10,1) == 11);
    assert(A2.calls() == 1);
    assert(A2.last_result().value() == 11);

    assert(B1.apply(1.5, 7.2) == 7.2);
    assert(B1.apply(-3.0, -8.0) == -3.0);
    assert(B1.calls() == 2);
    assert(B1.last_result().value() == -3.0);

    auto mul = [](long a, long b){ return a * b; };
    BiApplier<long,long,long> D1(mul);
    BiApplier<long,long,long> D2(mul);
    assert(D1.apply(6,7) == 42);
    assert(D2.apply(3,9) == 27);
    assert(D1.calls() == 1 && D2.calls() == 1);
    assert(D1.last_result().value() == 42);
    assert(D2.last_result().value() == 27);

    auto pick_first = [](std::string a, int){ return a; };
    BiApplier<std::string,std::string,int> E1(pick_first);
    assert(E1.apply("x", 5) == "x");
    assert(E1.calls() == 1);
    assert(E1.last_result().value() == "x");

    std::cout << "OK\n";
    return 0;
}
