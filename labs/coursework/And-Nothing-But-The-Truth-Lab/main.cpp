#include <iostream>
#include <vector>
using namespace std;

bool isSorted(const vector<int>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < v[i - 1]) return false;
    }
    return true;
}

bool subsetSum(const vector<int>& nums,
               const vector<int>& indices,
               int target) {
    int sum = 0;
    for (int i : indices) {
        if (i < 0 || i >= (int)nums.size()) return false;
        sum += nums[i];
    }
    return sum == target;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

bool verifyPrimeFactorization(int n, const vector<int>& factors) {
    if (n <= 1) return false;
    long long product = 1;
    for (int f : factors) {
        if (!isPrime(f)) return false;
        product *= f;
    }
    return product == n;
}

int main() {
    vector<int> a = {1, 2, 3, 4, 5};
    cout << isSorted(a) << endl;

    vector<int> nums = {3, 8, 1, 5};
    vector<int> idx = {0, 3};
    cout << subsetSum(nums, idx, 8) << endl;

    vector<int> factors = {2, 2, 3};
    cout << verifyPrimeFactorization(12, factors) << endl;

    return 0;
}
