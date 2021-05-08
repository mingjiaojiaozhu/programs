#include <iostream>
#include <vector>
using namespace std;

class PancakeSort {
public:
    void sort(vector<int> &nums) {
        for (int i = nums.size() - 1; i > 0; --i) {
            int maxIndex = 0;
            for (int j = 1; j <= i; ++j) {
                if (nums[maxIndex] < nums[j]) {
                    maxIndex = j;
                }
            }
            reverse(nums.begin(), nums.begin() + maxIndex + 1);
            reverse(nums.begin(), nums.begin() + i + 1);
        }
    }
};
