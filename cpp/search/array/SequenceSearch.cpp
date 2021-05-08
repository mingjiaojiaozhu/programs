#include <iostream>
#include <vector>
using namespace std;

class SequenceSearch {
public:
    int search(vector<int> &nums, int target) {
        vector<int> aux(nums.begin(), nums.end());
        aux.emplace_back(target);

        int index = 0;
        while (target != aux[index]) {
            ++index;
        }
        return (index < (int) nums.size()) ? index : -1;
    }
};
