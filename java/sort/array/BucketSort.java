package sort.array;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class BucketSort {
    public void sort(int[] nums) {
        int maxValue = Arrays.stream(nums).max().getAsInt();
        int minValue = Arrays.stream(nums).min().getAsInt();

        int size = (maxValue - minValue) / 10 + 1;
        List<Integer>[] buckets = new ArrayList[size];
        for (int i = 0; i < size; ++i) {
            buckets[i] = new ArrayList<>();
        }
        for (int value : nums) {
            buckets[(value - minValue) / 10].add(value);
        }

        int index = 0;
        for (List<Integer> bucket : buckets) {
            Collections.sort(bucket);

            for (int value : bucket) {
                nums[index] = value;
                ++index;
            }
        }
    }
}
