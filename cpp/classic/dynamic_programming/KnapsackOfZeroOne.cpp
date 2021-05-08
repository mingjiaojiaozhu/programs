#include <iostream>
#include <vector>
using namespace std;

class KnapsackOfZeroOne {
public:
    int solution(vector<int> &weights, vector<int> &values, int target) {
        vector<int> result(target + 1, 0);
        for (int i = 0; i < (int) weights.size(); ++i) {
            int weight = weights[i];
            int value = values[i];
            for (int j = target; j >= weight; --j) {
                int pivot = result[j - weight] + value;
                if (result[j] < pivot) {
                    result[j] = pivot;
                }
            }
        }
        return result.back();
    }
};
