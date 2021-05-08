package sort.array;

public class BubbleSort {
    public void sort(int[] nums) {
        int border = nums.length - 1;
        for (int _ : nums) {
            boolean flag = false;
            int index = 0;
            for (int i = 0; i < border; ++i) {
                if (nums[i + 1] < nums[i]) {
                    nums[i] ^= nums[i + 1];
                    nums[i + 1] ^= nums[i];
                    nums[i] ^= nums[i + 1];

                    flag = true;
                    index = i;
                }
            }

            if (!flag) {
                break;
            }
            border = index;
        }
    }
}
