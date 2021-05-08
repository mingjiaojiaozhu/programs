#include <iostream>
#include <vector>
using namespace std;

class Combination {
public:
    vector<vector<int>> solution(vector<int> &nums, int k) {
        vector<vector<int>> result(0);
        vector<int> aux(0);
        search(nums, k, 0, aux, result);
        return result;
    }

private:
    void search(vector<int> &nums, int k, int start, vector<int> &aux, vector<vector<int>> &result) {
        if (k == aux.size()) {
            result.emplace_back(aux);
            return;
        }

        for (int i = start; i < (int) nums.size(); ++i) {
            aux.emplace_back(nums[i]);
            search(nums, k, i + 1, aux, result);
            aux.pop_back();
        }
    }
};
