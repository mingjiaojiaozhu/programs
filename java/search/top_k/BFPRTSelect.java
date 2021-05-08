package search.top_k;

import java.util.Arrays;

public class BFPRTSelect {
    public int[] search(int[] nums, int k) {
        search(nums, 0, nums.length - 1, k);
        return Arrays.copyOf(nums, k);
    }

    private int search(int[] nums, int start, int end, int k) {
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

    private int getMedian(int[] nums, int start, int end) {
        if (end - start < 5) {
            Arrays.sort(nums, start, end + 1);
            return start + ((end - start) >> 1);
        }

        int index = start;
        int left = start;
        int right = end - 4;
        while (left <= right) {
            Arrays.sort(nums, left, left + 5);
            swap(nums, index, left + 2);

            left += 5;
            ++index;
        }
        return search(nums, start, index - 1, ((index - start) >> 1) + 1);
    }

    private int getPartition(int[] nums, int start, int end) {
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
                swap(nums, left, right);
            }
        }
        swap(nums, start, left);
        return left;
    }

    private void swap(int[] nums, int i, int j) {
        if (i != j) {
            nums[i] ^= nums[j];
            nums[j] ^= nums[i];
            nums[i] ^= nums[j];
        }
    }
}
