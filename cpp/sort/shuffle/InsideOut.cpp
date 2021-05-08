#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class InsideOut {
public:
    vector<int> shuffle(vector<int> &nums) {
        srand((unsigned int) time(nullptr));
        vector<int> result(nums.begin(), nums.end());
        for (int i = 0; i < (int) nums.size(); ++i) {
            int index = rand() % (i + 1);
            result[i] = result[index];
            result[index] = nums[i];
        }
        return result;
    }
};
