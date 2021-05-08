#include <iostream>
#include <vector>
using namespace std;

class CoinChange {
public:
    int solution(vector<int> &values, int target) {
        vector<int> result(target + 1, INT_MAX);
        result[0] = 0;
        for (int i = 0; i <= target; ++i) {
            for (int value : values) {
                if (i >= value) {
                    int pivot = result[i - value] + 1;
                    if (result[i] > pivot) {
                        result[i] = pivot;
                    }
                }
            }
        }
        return (result.back() <= target) ? result.back() : -1;
    }
};
