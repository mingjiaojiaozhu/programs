package sort.shuffle;

import java.util.Random;

public class KnuthDurstenfeld {
    private static final Random _random = new Random();

    public void shuffle(int[] nums) {
        for (int i = nums.length - 1; i > 0; --i) {
            int index = _random.nextInt(i + 1);
            if (index != i) {
                nums[index] ^= nums[i];
                nums[i] ^= nums[index];
                nums[index] ^= nums[i];
            }
        }
    }
}
