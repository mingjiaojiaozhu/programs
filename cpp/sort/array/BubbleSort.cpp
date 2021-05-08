#include <iostream>
#include <vector>
using namespace std;

class BubbleSort {
public:
    void sort(vector<int> &nums) {
        int border = nums.size() - 1;
        for (int _ : nums) {
            bool flag = false;
            int index = 0;
            for (int i = 0; i < border; ++i) {
                if (nums[i + 1] < nums[i]) {
                    swap(nums[i], nums[i + 1]);

                    flag = true;
                    index = i;
                }
            }

            if (!flag) {
                break;
            }
            border = index;
        }
    }
};
