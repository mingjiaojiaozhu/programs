#include <iostream>
#include <vector>
using namespace std;

class CocktailSort {
public:
    void sort(vector<int> &nums) {
        int start = 0;
        int end = nums.size() - 1;
        while (start < end) {
            bool flag = false;
            int index = 0;
            for (int i = start; i < end; ++i) {
                if (nums[i + 1] < nums[i]) {
                    swap(nums[i], nums[i + 1]);

                    flag = true;
                    index = i;
                }
            }

            if (!flag) {
                break;
            }
            end = index;

            flag = false;
            index = 0;
            for (int i = end; i > start; --i) {
                if (nums[i - 1] > nums[i]) {
                    swap(nums[i], nums[i - 1]);

                    flag = true;
                    index = i;
                }
            }

            if (!flag) {
                break;
            }
            start = index;
        }
    }
};
