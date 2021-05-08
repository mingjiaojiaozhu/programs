#include <iostream>
#include <vector>
using namespace std;

class FibonacciSequence {
public:
    vector<int> solution(int num) {
        vector<int> result(0);
        result.emplace_back(1);
        result.emplace_back(1);
        for (int i = 2; i < num; ++i) {
            result.emplace_back(result[i - 1] + result[i - 2]);
        }
        return result;
    }
};
