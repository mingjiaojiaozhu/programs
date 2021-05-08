#include <iostream>
#include <vector>
using namespace std;

class MergeInPlaceSort {
public:
    void sort(vector<int> &nums) {
        sort(nums, 0, nums.size() - 1);
    }

private:
    void sort(vector<int> &nums, int start, int end) {
        if (start >= end) {
            return;
        }

        int middle = start + ((end - start) >> 1);
        sort(nums, start, middle);
        sort(nums, middle + 1, end);

        if (nums[middle] > nums[middle + 1]) {
            merge(nums, start, middle, end);
        }
    }

    void merge(vector<int> &nums, int start, int middle, int end) {
        int left = start;
        int right = middle + 1;
        while (left < right && right <= end) {
            while (left < right && nums[left] <= nums[right]) {
                ++left;
            }

            int index = right;
            while (right <= end && nums[right] < nums[left]) {
                ++right;
            }

            reverse(nums.begin() + left, nums.begin() + index);
            reverse(nums.begin() + index, nums.begin() + right);
            reverse(nums.begin() + left, nums.begin() + right);

            left += right - index;
        }
    }
};
