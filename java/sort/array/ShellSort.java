package sort.array;

public class ShellSort {
    public void sort(int[] nums) {
        int gap = 1;
        while (gap < nums.length / 3) {
            gap = gap * 3 + 1;
        }

        while (gap > 0) {
            for (int i = gap; i < nums.length; ++i) {
                int pivot = nums[i];
                int index = i - gap;
                while (index >= 0 && nums[index] > pivot) {
                    nums[index + gap] = nums[index];
                    index -= gap;
                }
                nums[index + gap] = pivot;
            }
            gap /= 3;
        }
    }
}
