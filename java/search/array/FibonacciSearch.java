package search.array;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class FibonacciSearch {
    public int search(int[] nums, int target) {
        List<Integer> fibonacci = new ArrayList<>(Arrays.asList(new Integer[]{1, 1}));
        int index = 1;
        while (nums.length > fibonacci.get(index) - 1) {
            ++index;
            fibonacci.add(fibonacci.get(index - 1) + fibonacci.get(index - 2));
        }

        int[] aux = Arrays.copyOf(nums, fibonacci.get(index));
        Arrays.fill(aux, nums.length, aux.length, nums[nums.length - 1]);

        int start = 0;
        int end = nums.length - 1;
        while (start <= end) {
            int middle = start + fibonacci.get(index - 1) - 1;
            if (target == aux[middle]) {
                return (middle >= nums.length) ? nums.length - 1 : middle;
            }

            if (target < aux[middle]) {
                end = middle - 1;
                --index;
            } else {
                start = middle + 1;
                index -= 2;
            }
        }
        return -1;
    }
}
