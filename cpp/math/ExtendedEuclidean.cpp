#include <iostream>
#include <vector>
using namespace std;

class ExtendedEuclidean {
public:
    vector<int> gcd(int num1, int num2) {
        if (!num2) {
            int aux[3] = {num1, 1, 0};
            return vector<int>(aux, aux + 3);
        }

        vector<int> result = gcd(num2, num1 % num2);
        int aux = result[1] - result[2] * (num1 / num2);
        result[1] = result[2];
        result[2] = aux;
        return result;
    }
};
