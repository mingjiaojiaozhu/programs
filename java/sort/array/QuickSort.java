package sort.array;

import java.util.Random;

public class QuickSort {
    private static final Random _random = new Random();

    public void sort(int[] nums) {
        sort(nums, 0, nums.length - 1);
    }

    private void sort(int[] nums, int start, int end) {
        if (start < end) {
            int partition = getPartition(nums, start, end);
            sort(nums, start, partition - 1);
            sort(nums, partition + 1, end);
        }
    }

    private int getPartition(int[] nums, int start, int end) {
        int index = start + _random.nextInt(end - start + 1);
        swap(nums, index, end);
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
                swap(nums, left, right);
            }
        }
        swap(nums, left, end);
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
