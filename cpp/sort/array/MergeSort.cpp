#include <iostream>
#include <vector>
using namespace std;

class MergeSort {
public:
    void sort(vector<int> &nums) {
        vector<int> aux(nums.begin(), nums.end());
        sort(nums, aux, 0, nums.size() - 1);
    }

private:
    void sort(vector<int> &nums, vector<int> &aux, int start, int end) {
        if (start >= end) {
            return;
        }

        int middle = start + ((end - start) >> 1);
        sort(aux, nums, start, middle);
        sort(aux, nums, middle + 1, end);

        if (aux[middle] > aux[middle + 1]) {
            merge(nums, aux, start, middle, end);
        } else {
            copy(aux.begin() + start, aux.begin() + end + 1, nums.begin() + start);
        }
    }

    void merge(vector<int> &nums, vector<int> &aux, int start, int middle, int end) {
        int index = start;
        int left = start;
        int right = middle + 1;
        while (left <= middle && right <= end) {
            if (aux[left] > aux[right]) {
                nums[index] = aux[right];
                ++right;
            } else {
                nums[index] = aux[left];
                ++left;
            }
            ++index;
        }

        if (left <= middle) {
            copy(aux.begin() + left, aux.begin() + middle + 1, nums.begin() + index);
        }
        if (right <= end) {
            copy(aux.begin() + right, aux.begin() + end + 1, nums.begin() + index);
        }
    }
};
