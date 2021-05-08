#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BucketSort {
public:
    void sort(vector<int> &nums) {
        int maxValue = *max_element(begin(nums), end(nums));
        int minValue = *min_element(begin(nums), end(nums));

        int size = (maxValue - minValue) / 10 + 1;
        vector<vector<int>> buckets(size, vector<int>(0));
        for (int value : nums) {
            buckets[(value - minValue) / 10].emplace_back(value);
        }

        int index = 0;
        for (vector<int> &bucket : buckets) {
            std::sort(bucket.begin(), bucket.end());

            for (int value : bucket) {
                nums[index] = value;
                ++index;
            }
        }
    }
};
