package sort.array;

public class MergeInPlaceSort {
    public void sort(int[] nums) {
        sort(nums, 0, nums.length - 1);
    }

    private void sort(int[] nums, int start, int end) {
        if (start >= end) {
            return;
        }

        int middle = start + ((end - start) >> 1);
        sort(nums, start, middle);
        sort(nums, middle + 1, end);

        if (nums[middle] > nums[middle + 1]) {
            merge(nums, start, middle, end);
        }
    }

    private void merge(int[] nums, int start, int middle, int end) {
        int left = start;
        int right = middle + 1;
        while (left < right && right <= end) {
            while (left < right && nums[left] <= nums[right]) {
                ++left;
            }

            int index = right;
            while (right <= end && nums[right] < nums[left]) {
                ++right;
            }

            reverse(nums, left, index - 1);
            reverse(nums, index, right - 1);
            reverse(nums, left, right - 1);

            left += right - index;
        }
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
