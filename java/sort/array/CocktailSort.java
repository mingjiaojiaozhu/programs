package sort.array;

public class CocktailSort {
    public void sort(int[] nums) {
        int start = 0;
        int end = nums.length - 1;
        while (start < end) {
            boolean flag = false;
            int index = 0;
            for (int i = start; i < end; ++i) {
                if (nums[i + 1] < nums[i]) {
                    swap(nums, i , i + 1);

                    flag = true;
                    index = i;
                }
            }

            if (!flag) {
                break;
            }
            end = index;

            flag = false;
            index = 0;
            for (int i = end; i > start; --i) {
                if (nums[i - 1] > nums[i]) {
                    swap(nums, i , i - 1);

                    flag = true;
                    index = i;
                }
            }

            if (!flag) {
                break;
            }
            start = index;
        }
    }

    private void swap(int[] nums, int i, int j) {
        nums[i] ^= nums[j];
        nums[j] ^= nums[i];
        nums[i] ^= nums[j];
    }
}
