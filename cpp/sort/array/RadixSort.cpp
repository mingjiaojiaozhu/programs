#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class RadixSort {
public:
    void sort(vector<int> &nums) {
        int maxValue = *max_element(begin(nums), end(nums));
        int minValue = *min_element(begin(nums), end(nums));

        int diff = maxValue - minValue;
        for (int gap = 1; gap <= diff; gap *= 10) {
            vector<vector<int>> buckets(10, vector<int>(0));
            for (int value : nums) {
                buckets[((value - minValue) / gap) % 10].emplace_back(value);
            }

            int index = 0;
            for (vector<int> &bucket : buckets) {
                for (int value : bucket) {
                    nums[index] = value;
                    ++index;
                }
            }
        }
    }
};
