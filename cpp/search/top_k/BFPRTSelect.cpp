#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BFPRTSelect {
public:
    vector<int> search(vector<int> &nums, int k) {
        search(nums, 0, nums.size() - 1, k);
        return vector<int>(nums.begin(), nums.begin() + k);
    }

private:
    int search(vector<int> &nums, int start, int end, int k) {
        int median = getMedian(nums, start, end);
        int partition = getPartition(nums, median, end);
        if (k == partition - start + 1) {
            return partition;
        }

        if (k < partition - start + 1) {
            return search(nums, start, partition - 1, k);
        }
        return search(nums, partition + 1, end, k - (partition - start + 1));
    }

    int getMedian(vector<int> &nums, int start, int end) {
        if (end - start < 5) {
            sort(nums.begin() + start, nums.begin() + end + 1);
            return start + ((end - start) >> 1);
        }

        int index = start;
        int left = start;
        int right = end - 4;
        while (left <= right) {
            sort(nums.begin() + left, nums.begin() + left + 5);
            swap(nums[index], nums[left + 2]);

            left += 5;
            ++index;
        }
        return search(nums, start, index - 1, ((index - start) >> 1) + 1);
    }

    int getPartition(vector<int> &nums, int start, int end) {
        int pivot = nums[start];
        int left = start;
        int right = end;
        while (left < right) {
            while (left < right && nums[right] > pivot) {
                --right;
            }
            while (left < right && nums[left] <= pivot) {
                ++left;
            }

            if (left < right) {
                swap(nums[left], nums[right]);
            }
        }
        swap(nums[start], nums[left]);
        return left;
    }
};
