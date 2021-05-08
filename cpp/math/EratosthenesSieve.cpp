#include <iostream>
#include <vector>
using namespace std;

class EratosthenesSieve {
public:
    vector<int> sieve(int num) {
        vector<bool> isPrime(num, true);
        vector<int> result(0);
        for (int i = 2; i <= num; ++i) {
            if (isPrime[i - 1]) {
                result.emplace_back(i);
            }

            for (int value : result) {
                if (value > num / i) {
                    break;
                }
                isPrime[i * value - 1] = false;
            }
        }
        return result;
    }
};
