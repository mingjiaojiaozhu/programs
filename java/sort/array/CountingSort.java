package sort.array;

import java.util.Arrays;

public class CountingSort {
    public void sort(int[] nums) {
        int maxValue = Arrays.stream(nums).max().getAsInt();
        int minValue = Arrays.stream(nums).min().getAsInt();

        int size = maxValue - minValue + 1;
        int[] buckets = new int[size];
        Arrays.fill(buckets, 0);
        for (int value : nums) {
            ++buckets[value - minValue];
        }
        for (int i = 1; i < size; ++i) {
            buckets[i] += buckets[i - 1];
        }

        int[] aux = nums.clone();
        for (int i = nums.length - 1; i >= 0; --i) {
            int index = aux[i] - minValue;
            nums[buckets[index] - 1] = aux[i];
            --buckets[index];
        }
    }
}
