package search.array;

import java.util.Arrays;

public class SequenceSearch {
    int search(int[] nums, int target) {
        int[] aux = Arrays.copyOf(nums, nums.length + 16);
        aux[nums.length] = target;

        int index = 0;
        while (target != aux[index]) {
            ++index;
        }
        return (index < nums.length) ? index : -1;
    }
}
