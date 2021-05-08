#include <iostream>
#include <vector>
using namespace std;

class StoogeSort {
public:
    void sort(vector<int> &nums) {
        sort(nums, 0, nums.size() - 1);
    }

private:
    void sort(vector<int> &nums, int start, int end) {
        if (nums[start] > nums[end]) {
            swap(nums[start], nums[end]);
        }

        if (start + 1 < end) {
            int third = (end - start + 1) / 3;
            sort(nums, start, end - third);
            sort(nums, start + third, end);
            sort(nums, start, end - third);
        }
    }
};
