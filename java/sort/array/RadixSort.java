package sort.array;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class RadixSort {
    public void sort(int[] nums) {
        int maxValue = Arrays.stream(nums).max().getAsInt();
        int minValue = Arrays.stream(nums).min().getAsInt();

        List<Integer>[] buckets = new ArrayList[10];
        for (int j = 0; j < 10; ++j) {
            buckets[j] = new ArrayList<>();
        }

        int diff = maxValue - minValue;
        for (int gap = 1; gap <= diff; gap *= 10) {
            for (List<Integer> bucket : buckets) {
                bucket.clear();
            }
            for (int value : nums) {
                buckets[((value - minValue) / gap) % 10].add(value);
            }

            int index = 0;
            for (List<Integer> bucket : buckets) {
                for (int value : bucket) {
                    nums[index] = value;
                    ++index;
                }
            }
        }
    }
}
