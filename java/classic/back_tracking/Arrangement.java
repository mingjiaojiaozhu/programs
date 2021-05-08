package classic.back_tracking;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Arrangement {
    public int[][] solution(int[] nums, int k) {
        List<int[]> result = new ArrayList<>();
        search(nums, k, 0, result);
        return result.toArray(new int[0][]);
    }

    private void search(int[] nums, int k, int start, List<int[]> result) {
        if (k == start) {
            result.add(Arrays.copyOf(nums, k));
            return;
        }

        search(nums, k, start + 1, result);
        for (int i = start + 1; i < nums.length; ++i) {
            swap(nums, start, i);
            search(nums, k, start + 1, result);
            swap(nums, start, i);
        }
    }

    private void swap(int[] nums, int i, int j) {
        nums[i] ^= nums[j];
        nums[j] ^= nums[i];
        nums[i] ^= nums[j];
    }
}
