#include <iostream>
#include <vector>
using namespace std;

class BlockingSearch {
public:
    int search(vector<int> &nums, vector<vector<int>> &blocks, int target) {
        int start = 0;
        int end = blocks.size() - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (target <= blocks[middle][2]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }

        if (start >= (int) blocks.size()) {
            return -1;
        }

        for (int i = blocks[start][0]; i <= blocks[start][1]; ++i) {
            if (target == nums[i]) {
                return i;
            }
        }
        return -1;
    }
};
