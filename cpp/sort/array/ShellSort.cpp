#include <iostream>
#include <vector>
using namespace std;

class ShellSort {
public:
    void sort(vector<int> &nums) {
        int gap = 1;
        while (gap < (int) nums.size() / 3) {
            gap = gap * 3 + 1;
        }

        while (gap > 0) {
            for (int i = gap; i < (int) nums.size(); ++i) {
                int pivot = nums[i];
                int index = i - gap;
                while (index >= 0 && nums[index] > pivot) {
                    nums[index + gap] = nums[index];
                    index -= gap;
                }
                nums[index + gap] = pivot;
            }
            gap /= 3;
        }
    }
};
