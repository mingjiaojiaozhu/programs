#include <iostream>
#include <vector>
using namespace std;

class InterpolationSearch {
public:
    int search(vector<int> &nums, int target) {
        int start = 0;
        int end = nums.size() - 1;
        while (start < end && nums[start] != nums[end]) {
            int middle = start + (target - nums[start]) * (end - start) / (nums[end] - nums[start]);
            if (middle < start || middle > end) {
                return -1;
            }

            if (target == nums[middle]) {
                return middle;
            }

            if (target < nums[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }
        return (start < (int) nums.size() && target == nums[start]) ? start : -1;
    }
};
