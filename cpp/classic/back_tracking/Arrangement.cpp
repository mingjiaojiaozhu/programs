#include <iostream>
#include <vector>
using namespace std;

class Arrangement {
public:
    vector<vector<int>> solution(vector<int> &nums, int k) {
        vector<vector<int>> result(0);
        search(nums, k, 0, result);
        return result;
    }

private:
    void search(vector<int> &nums, int k, int start, vector<vector<int>> &result) {
        if (k == start) {
            result.emplace_back(vector<int>(nums.begin(), nums.begin() + k));
            return;
        }

        search(nums, k, start + 1, result);
        for (int i = start + 1; i < (int) nums.size(); ++i) {
            swap(nums[start], nums[i]);
            search(nums, k, start + 1, result);
            swap(nums[start], nums[i]);
        }
    }
};
