package search.top_k;

import java.util.Arrays;
import java.util.Random;

public class QuickSelect {
    private static final Random _random = new Random();

    public int[] search(int[] nums, int k) {
        search(nums, 0, nums.length - 1, k);
        return Arrays.copyOf(nums, k);
    }

    private void search(int[] nums, int start, int end, int k) {
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
