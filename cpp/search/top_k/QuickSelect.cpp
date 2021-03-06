#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class QuickSelect {
public:
    vector<int> search(vector<int> &nums, int k) {
        srand((unsigned int) time(nullptr));
        search(nums, 0, nums.size() - 1, k);
        return vector<int>(nums.begin(), nums.begin() + k);
    }

private:
    void search(vector<int> &nums, int start, int end, int k) {
        int partition = getPartition(nums, start, end);
        if (k == partition - start + 1) {
            return;
        }

        if (k < partition - start + 1) {
            search(nums, start, partition - 1, k);
        } else {
            search(nums, partition + 1, end, k - (partition - start + 1));
        }
    }

    int getPartition(vector<int> &nums, int start, int end) {
        int index = start + rand() % (end - start + 1);
        swap(nums[index], nums[end]);
        int pivot = nums[end];

        int left = start;
        int right = end;
        while (left < right) {
            while (left < right && nums[left] < pivot) {
                ++left;
            }
            while (left < right && nums[right] >= pivot) {
                --right;
            }

            if (left < right) {
                swap(nums[left], nums[right]);
            }
        }
        swap(nums[left], nums[end]);
        return left;
    }
};
