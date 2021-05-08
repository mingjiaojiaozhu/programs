#include <iostream>
#include <vector>
using namespace std;

class TimSort {
public:
    void sort(vector<int> &nums) {
        if ((int) nums.size() < 16) {
            int runLength = getRunLength(nums, 0, nums.size());
            insertSort(nums, 0, nums.size(), runLength);
            return;
        }

        vector<int> aux(nums.begin(), nums.end());
        vector<int> runBase(0);
        vector<int> runSize(0);

        int start = 0;
        int end = nums.size();
        while (end > 0) {
            int runLength = getRunLength(nums, start, nums.size());
            if (runLength < 16) {
                int size = min(end, 16);
                insertSort(nums, start, start + size, start + runLength);
                runLength = size;
            }

            runBase.emplace_back(start);
            runSize.emplace_back(runLength);
            mergeRuns(nums, aux, runBase, runSize);

            start += runLength;
            end -= runLength;
        }

        while ((int) runBase.size() > 1) {
            merge(nums, aux, runBase.size() - 2, runBase, runSize);
        }
    }

private:
    int getRunLength(vector<int> &nums, int start, int end) {
        if (start + 1 == end) {
            return 1;
        }

        int index = start + 1;
        if (nums[start] > nums[index]) {
            while (index < end - 1 && nums[index] > nums[index + 1]) {
                ++index;
            }
            reverse(nums.begin() + start, nums.begin() + index + 1);
        } else {
            while (index < end - 1 && nums[index] <= nums[index + 1]) {
                ++index;
            }
        }
        return index - start + 1;
    }

    void insertSort(vector<int> &nums, int start, int end, int index) {
        for (int i = index; i < end; ++i) {
            int pivot = nums[i];
            if (pivot >= nums[i - 1]) {
                continue;
            }

            int left = start;
            int right = i - 1;
            while (left <= right) {
                int middle = left + ((right - left) >> 1);
                if (pivot < nums[middle]) {
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            }

            for (int j = i - 1; j >= left; --j) {
                nums[j + 1] = nums[j];
            }
            nums[left] = pivot;
        }
    }

    void mergeRuns(vector<int> &nums, vector<int> &aux, vector<int> &runBase, vector<int> &runSize) {
        while ((int) runBase.size() > 1) {
            int index = runBase.size() - 2;
            if (index > 0 && runSize[index - 1] <= runSize[index] + runSize[index + 1]) {
                if (runSize[index - 1] < runSize[index + 1]) {
                    --index;
                }
                merge(nums, aux, index, runBase, runSize);
            } else if (runSize[index] <= runSize[index + 1]) {
                merge(nums, aux, index, runBase, runSize);
            } else {
                return;
            }
        }
    }

    void merge(vector<int> &nums, vector<int> &aux, int runIndex, vector<int> &runBase, vector<int> &runSize) {
        int base1 = runBase[runIndex];
        int size1 = runSize[runIndex];
        int base2 = runBase[runIndex + 1];
        int size2 = runSize[runIndex + 1];

        runSize[runIndex] = size1 + size2;
        if (runIndex == runSize.size() - 3) {
            runBase[runIndex + 1] = runBase[runIndex + 2];
            runSize[runIndex + 1] = runSize[runIndex + 2];
        }
        runBase.pop_back();
        runSize.pop_back();

        int start = gallopLeft(nums, base1, size1, nums[base2]);
        if (start >= base1 + size1) {
            return;
        }
        int end = gallopRight(nums, base2, size2, nums[base1 + size1 - 1]);
        if (end < base2) {
            return;
        }
        copy(nums.begin() + start, nums.begin() + end + 1, aux.begin() + start);

        int index = start;
        int left1 = start;
        int right1 = base1 + size1 - 1;
        int left2 = base2;
        int right2 = end;
        while (left1 <= right1 && left2 <= right2) {
            if (aux[left1] > aux[left2]) {
                nums[index] = aux[left2];
                ++left2;
            } else {
                nums[index] = aux[left1];
                ++left1;
            }
            ++index;
        }

        if (left1 <= right1) {
            copy(aux.begin() + left1, aux.begin() + right1 + 1, nums.begin() + index);
        }
        if (left2 <= right2) {
            copy(aux.begin() + left2, aux.begin() + right2 + 1, nums.begin() + index);
        }
    }

    int gallopLeft(vector<int> &nums, int base, int size, int pivot) {
        int start = base;
        int end = base + size - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (pivot <= nums[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }
        return end + 1;
    }

    int gallopRight(vector<int> &nums, int base, int size, int pivot) {
        int start = base;
        int end = base + size - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (pivot >= nums[middle]) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }
        return start - 1;
    }
};
