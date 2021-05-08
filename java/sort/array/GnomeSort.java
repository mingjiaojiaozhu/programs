package sort.array;

public class GnomeSort {
    public void sort(int[] nums) {
        int index = 0;
        while (index < nums.length) {
            if (0 == index || nums[index - 1] <= nums[index]) {
                ++index;
            } else {
                nums[index] ^= nums[index - 1];
                nums[index - 1] ^= nums[index];
                nums[index] ^= nums[index - 1];

                --index;
            }
        }
    }
}
