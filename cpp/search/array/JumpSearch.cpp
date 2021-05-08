#include <iostream>
#include <vector>
using namespace std;

class JumpSearch {
public:
    int search(vector<int> &nums, int target) {
        int step = (int) sqrt(nums.size());
        int border = step;
        while (border < (int) nums.size() && target > nums[border]) {
            border += step;
        }

        for (int i = border - step; i < min(border + 1, (int) nums.size()); ++i) {
            if (target == nums[i]) {
                return i;
            }
        }
        return -1;
    }
};
