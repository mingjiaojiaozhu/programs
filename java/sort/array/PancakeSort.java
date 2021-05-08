package sort.array;

public class PancakeSort {
    public void sort(int[] nums) {
        for (int i = nums.length - 1; i > 0; --i) {
            int maxIndex = 0;
            for (int j = 1; j <= i; ++j) {
                if (nums[maxIndex] < nums[j]) {
                    maxIndex = j;
                }
            }
            reverse(nums, 0, maxIndex);
            reverse(nums, 0, i);
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
