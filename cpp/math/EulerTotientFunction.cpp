#include <iostream>
#include <vector>
using namespace std;

class EulerTotientFunction {
public:
    vector<int> solution(int num) {
        vector<bool> isPrime(num, true);
        vector<int> primes(0);

        vector<int> result(num, 0);
        for (int i = 2; i <= num; ++i) {
            if (isPrime[i - 1]) {
                primes.emplace_back(i);
                result[i - 1] = i - 1;
            }

            for (int value : primes) {
                if (value > num / i) {
                    break;
                }

                isPrime[i * value - 1] = false;
                if (!(i % value)) {
                    result[i * value - 1] = result[i - 1] * value;
                    break;
                } else {
                    result[i * value - 1] = result[i - 1] * (value - 1);
                }
            }
        }
        return result;
    }
};
