#include <iostream>
#include <vector>
using namespace std;

class CRT {
public:
    int solution(vector<vector<int>> values) {
        int total = 1;
        for (vector<int> value : values) {
            total *= value[0];
        }

        int result = 0;
        for (vector<int> value : values) {
            int lcm = total / value[0];
            result = (result + lcm / gcd(lcm, value[0])[0] * value[1]) % total;
        }
        return (result + total) % total;
    }

private:
    vector<int> gcd(int num1, int num2) {
        if (!num2) {
            int aux[2] = {1, 0};
            return vector<int>(aux, aux + 2);
        }

        vector<int> result = gcd(num2, num1 % num2);
        int aux = result[0] - result[1] * (num1 / num2);
        result[0] = result[1];
        result[1] = aux;
        return result;
    }
};
