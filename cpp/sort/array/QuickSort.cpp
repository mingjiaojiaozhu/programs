#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class QuickSort {
public:
    void sort(vector<int> &nums) {
        srand((unsigned int) time(nullptr));
        sort(nums, 0, nums.size() - 1);
    }

private:
    void sort(vector<int> &nums, int start, int end) {
        if (start < end) {
            int partition = getPartition(nums, start, end);
            sort(nums, start, partition - 1);
            sort(nums, partition + 1, end);
        }
    }

    int getPartition(vector<int> &nums, int start, int end) {
        int index = start + rand() % (end - start + 1);
        swap(nums[index], nums[end]);
        int pivot = nums[end];

        int left = start;
        int right = end;
        while (left < right) {
            while (left < right && nums[left] < pivot) {
                ++left;
            }
            while (left < right && nums[right] >= pivot) {
                --right;
            }

            if (left < right) {
                swap(nums[left], nums[right]);
            }
        }
        swap(nums[left], nums[end]);
        return left;
    }
};
