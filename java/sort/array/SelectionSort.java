package sort.array;

public class SelectionSort {
    public void sort(int[] nums) {
        int start = 0;
        int end = nums.length - 1;
        while (start <= end) {
            int maxIndex = start;
            int minIndex = start;
            for (int i = start + 1; i <= end; ++i) {
                if (nums[maxIndex] < nums[i]) {
                    maxIndex = i;
                } else if (nums[minIndex] > nums[i]) {
                    minIndex = i;
                }
            }

            swap(nums, minIndex, start);
            if (maxIndex == start) {
                maxIndex = minIndex;
            }
            swap(nums, maxIndex, end);

            ++start;
            --end;
        }
    }

    private void swap(int[] nums, int i, int j) {
        if (i != j) {
            nums[i] ^= nums[j];
            nums[j] ^= nums[i];
            nums[i] ^= nums[j];
        }
    }
}
