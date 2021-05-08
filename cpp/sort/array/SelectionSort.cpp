#include <iostream>
#include <vector>
using namespace std;

class SelectionSort {
public:
    void sort(vector<int> &nums) {
        int start = 0;
        int end = nums.size() - 1;
        while (start <= end) {
            int maxIndex = start;
            int minIndex = start;
            for (int i = start + 1; i <= end; ++i) {
                if (nums[maxIndex] < nums[i]) {
                    maxIndex = i;
                } else if (nums[minIndex] > nums[i]) {
                    minIndex = i;
                }
            }

            swap(nums[minIndex], nums[start]);
            if (maxIndex == start) {
                maxIndex = minIndex;
            }
            swap(nums[maxIndex], nums[end]);

            ++start;
            --end;
        }
    }
};
