#include <iostream>
#include <vector>
using namespace std;

class KnapsackOfMultiple {
public:
    int solution(vector<int> &weights, vector<int> &values, vector<int> &nums, int target) {
        vector<int> result(target + 1, 0);
        for (int i = 0; i < (int) weights.size(); ++i) {
            int weight = weights[i];
            int value = values[i];
            int num = nums[i];
            for (int j = target; j >= weight; --j) {
                for (int k = 0; k <= min(num, j / weight); ++k) {
                    int pivot = result[j - k * weight] + k * value;
                    if (result[j] < pivot) {
                        result[j] = pivot;
                    }
                }
            }
        }
        return result.back();
    }
};
