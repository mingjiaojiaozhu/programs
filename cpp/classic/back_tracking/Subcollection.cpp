#include <iostream>
#include <vector>
using namespace std;

class Subcollection {
public:
    vector<vector<int>> solution(vector<int> &nums) {
        vector<vector<int>> result(0);
        vector<int> aux(0);
        search(nums, 0, aux, result);
        return result;
    }

private:
    void search(vector<int> &nums, int start, vector<int> &aux, vector<vector<int>> &result) {
        result.emplace_back(aux);
        for (int i = start; i < (int) nums.size(); ++i) {
            aux.emplace_back(nums[i]);
            search(nums, i + 1, aux, result);
            aux.pop_back();
        }
    }
};
