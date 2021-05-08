package sort.array;

import java.util.ArrayList;
import java.util.List;

public class TimSort {
    public void sort(int[] nums) {
        if (nums.length < 16) {
            int runLength = getRunLength(nums, 0, nums.length);
            insertSort(nums, 0, nums.length, runLength);
            return;
        }

        int[] aux = nums.clone();
        List<Integer> runBase = new ArrayList<>();
        List<Integer> runSize = new ArrayList<>();

        int start = 0;
        int end = nums.length;
        while (end > 0) {
            int runLength = getRunLength(nums, start, nums.length);
            if (runLength < 16) {
                int size = Math.min(end, 16);
                insertSort(nums, start, start + size, start + runLength);
                runLength = size;
            }

            runBase.add(start);
            runSize.add(runLength);
            mergeRuns(nums, aux, runBase, runSize);

            start += runLength;
            end -= runLength;
        }

        while (runBase.size() > 1) {
            merge(nums, aux, runBase.size() - 2, runBase, runSize);
        }
    }

    private int getRunLength(int[] nums, int start, int end) {
        if (start + 1 == end) {
            return 1;
        }

        int index = start + 1;
        if (nums[start] > nums[index]) {
            while (index < end - 1 && nums[index] > nums[index + 1]) {
                ++index;
            }
            reverse(nums, start, index);
        } else {
            while (index < end - 1 && nums[index] <= nums[index + 1]) {
                ++index;
            }
        }
        return index - start + 1;
    }

    private void insertSort(int[] nums, int start, int end, int index) {
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

    private void mergeRuns(int[] nums, int[] aux, List<Integer> runBase, List<Integer> runSize) {
        while (runBase.size() > 1) {
            int index = runBase.size() - 2;
            if (index > 0 && runSize.get(index - 1) <= runSize.get(index) + runSize.get(index + 1)) {
                if (runSize.get(index - 1) < runSize.get(index + 1)) {
                    --index;
                }
                merge(nums, aux, index, runBase, runSize);
            } else if (runSize.get(index) <= runSize.get(index + 1)) {
                merge(nums, aux, index, runBase, runSize);
            } else {
                return;
            }
        }
    }

    private void merge(int[] nums, int[] aux, int runIndex, List<Integer> runBase, List<Integer> runSize) {
        int base1 = runBase.get(runIndex);
        int size1 = runSize.get(runIndex);
        int base2 = runBase.get(runIndex + 1);
        int size2 = runSize.get(runIndex + 1);

        runSize.set(runIndex, size1 + size2);
        if (runIndex == runSize.size() - 3) {
            runBase.set(runIndex + 1, runBase.get(runIndex + 2));
            runSize.set(runIndex + 1, runSize.get(runIndex + 2));
        }
        runBase.remove(runBase.size() - 1);
        runSize.remove(runSize.size() - 1);

        int start = gallopLeft(nums, base1, size1, nums[base2]);
        if (start >= base1 + size1) {
            return;
        }
        int end = gallopRight(nums, base2, size2, nums[base1 + size1 - 1]);
        if (end < base2) {
            return;
        }
        System.arraycopy(nums, start, aux, start, end - start + 1);

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
            System.arraycopy(aux, left1, nums, index, right1 - left1 + 1);
        }
        if (left2 <= right2) {
            System.arraycopy(aux, left2, nums, index, right2 - left2 + 1);
        }
    }

    private int gallopLeft(int[] nums, int base, int size, int pivot) {
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

    private int gallopRight(int[] nums, int base, int size, int pivot) {
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

    private void reverse(int[] nums, int start, int end) {
        while (start < end) {
            nums[start] ^= nums[end];
            nums[end] ^= nums[start];
            nums[start] ^= nums[end];

            ++start;
            --end;
        }
    }
}
