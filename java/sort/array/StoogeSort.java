package sort.array;

public class StoogeSort {
    public void sort(int[] nums) {
        sort(nums, 0, nums.length - 1);
    }

    private void sort(int[] nums, int start, int end) {
        if (nums[start] > nums[end]) {
            nums[start] ^= nums[end];
            nums[end] ^= nums[start];
            nums[start] ^= nums[end];
        }

        if (start + 1 < end) {
            int third = (end - start + 1) / 3;
            sort(nums, start, end - third);
            sort(nums, start + third, end);
            sort(nums, start, end - third);
        }
    }
}
