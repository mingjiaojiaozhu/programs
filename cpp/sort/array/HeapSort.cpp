#include <iostream>
#include <vector>
using namespace std;

class HeapSort {
public:
    void sort(vector<int> &nums) {
        for (int i = (nums.size() >> 1) - 1; i >= 0; --i) {
            adjustHeap(nums, i, nums.size());
        }

        for (int i = nums.size() - 1; i > 0; --i) {
            swap(nums[0], nums[i]);
            adjustHeap(nums, 0, i);
        }
    }

private:
    void adjustHeap(vector<int> &nums, int parent, int length) {
        int pivot = nums[parent];
        while (true) {
            int child = (parent << 1) + 1;
            if (child >= length) {
                break;
            }

            if (child < length - 1 && nums[child] < nums[child + 1]) {
                ++child;
            }
            if (nums[child] <= pivot) {
                break;
            }
            nums[parent] = nums[child];
            parent = child;
        }
        nums[parent] = pivot;
    }
};
