#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Factorizer {
public:
    vector<int> primeFactors(int n) {
        vector<int> factors;
        if (n <= 1) return factors;

        for (int i = 2; i * i <= n; i++) {
            while (n % i == 0) {
                factors.push_back(i);
                n /= i;
            }
        }
        if (n > 1) factors.push_back(n);
        return factors;
    }

    bool isPrime(int n) {
        vector<int> factors = primeFactors(n);
        return (factors.size() == 1 && factors[0] == n);
    }

    bool isComposite(int n) {
        if (n <= 1) return false;
        return !isPrime(n);
    }

    string reduce(int numerator, int denominator) {
        if (denominator == 0) return "undefined";

        vector<int> numFactors = primeFactors(numerator);
        vector<int> denFactors = primeFactors(denominator);

        for (size_t i = 0; i < numFactors.size(); i++) {
            for (size_t j = 0; j < denFactors.size(); j++) {
                if (numFactors[i] == denFactors[j]) {
                    numFactors[i] = -1;
                    denFactors[j] = -1;
                    break;
                }
            }
        }

        int newNum = 1, newDen = 1;
        for (int f : numFactors) if (f != -1) newNum *= f;
        for (int f : denFactors) if (f != -1) newDen *= f;

        if (newDen == 1) return to_string(newNum);
        if (newNum == newDen) return "1";
        return to_string(newNum) + "/" + to_string(newDen);
    }
};

int main() {
    Factorizer factorizer;

    // Examples
    vector<int> f1 = factorizer.primeFactors(9);
    cout << "Prime factors of 9: ";
    for (int f : f1) cout << f << " ";
    cout << endl;

    cout << "Is 17 prime? " << (factorizer.isPrime(17) ? "true" : "false") << endl;
    cout << "Is 12 composite? " << (factorizer.isComposite(12) ? "true" : "false") << endl;

    cout << "Reduce 36/12: " << factorizer.reduce(36, 12) << endl;
    cout << "Reduce 12/14: " << factorizer.reduce(12, 14) << endl;
    cout << "Reduce 12/37: " << factorizer.reduce(12, 37) << endl;

    return 0;
}
