#include <iostream>
#include <vector>
using namespace std;

class GnomeSort {
public:
    void sort(vector<int> &nums) {
        int index = 0;
        while (index < (int) nums.size()) {
            if (!index || nums[index - 1] <= nums[index]) {
                ++index;
            } else {
                swap(nums[index], nums[index - 1]);
                --index;
            }
        }
    }
};
