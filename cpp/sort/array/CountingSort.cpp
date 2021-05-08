#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class CountingSort {
public:
    void sort(vector<int> &nums) {
        int maxValue = *max_element(begin(nums), end(nums));
        int minValue = *min_element(begin(nums), end(nums));

        int size = maxValue - minValue + 1;
        vector<int> buckets(size, 0);
        for (int value : nums) {
            ++buckets[value - minValue];
        }
        for (int i = 1; i < size; ++i) {
            buckets[i] += buckets[i - 1];
        }

        vector<int> aux(nums.begin(), nums.end());
        for (int i = nums.size() - 1; i >= 0; --i) {
            int index = aux[i] - minValue;
            nums[buckets[index] - 1] = aux[i];
            --buckets[index];
        }
    }
};
