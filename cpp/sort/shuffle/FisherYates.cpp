#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class FisherYates {
public:
    vector<int> shuffle(vector<int> &nums) {
        srand((unsigned int) time(nullptr));
        vector<int> result(0);
        while (!nums.empty()) {
            int index = rand() % nums.size();
            result.emplace_back(nums[index]);
            nums.erase(nums.begin() + index);
        }
        return result;
    }
};
