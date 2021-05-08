package sort.shuffle;

import java.util.Random;

public class InsideOut {
    private static final Random _random = new Random();

    public int[] shuffle(int[] nums) {
        int[] result = nums.clone();
        for (int i = 0; i < nums.length; ++i) {
            int index = _random.nextInt(i + 1);
            result[i] = result[index];
            result[index] = nums[i];
        }
        return result;
    }
}
