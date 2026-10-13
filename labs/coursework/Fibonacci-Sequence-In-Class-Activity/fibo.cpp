#include <iostream>
#include <vector>
using namespace std;

long long fib_rec(int n) {
    static long long calls = 0;
    calls++;
    if (n <= 2) return 1;
    return fib_rec(n - 1) + fib_rec(n - 2);
}

long long fib_iter(int n, long long &iterations) {
    iterations = 0;
    if (n <= 2) return 1;
    long long a = 1, b = 1;
    for (int i = 3; i <= n; ++i) {
        long long c = a + b;
        a = b;
        b = c;
        iterations++;
    }
    return b;
}

long long fib_memo(int n) {
    static vector<long long> memo;
    static long long calls = 0;
    calls++;
    if (n <= 2) return 1;
    if ((int)memo.size() < n + 1) memo.assign(n + 1, -1);
    if (memo[n] != -1) return memo[n];
    memo[n] = fib_memo(n - 1) + fib_memo(n - 2);
    return memo[n];
}

int main() {
    long long iters = 0;
    long long fi = fib_iter(10, iters);
    long long fm = fib_memo(10);
    cout << "fib_iter(10) = " << fi << "\n";
    cout << "fib_memo(10) = " << fm << "\n";
    cout << "loop iterations for N=10 = " << iters << "\n";
    return 0;
}

    return 0;
}
