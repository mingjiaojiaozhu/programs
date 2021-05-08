#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class KnuthDurstenfeld {
public:
    void shuffle(vector<int> &nums) {
        srand((unsigned int) time(nullptr));
        for (int i = nums.size() - 1; i > 0; --i) {
            int index = rand() % (i + 1);
            swap(nums[index], nums[i]);
        }
    }
};
