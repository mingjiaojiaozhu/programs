package classic.back_tracking;

import java.util.ArrayList;
import java.util.List;

public class Combination {
    public int[][] solution(int[] nums, int k) {
        List<int[]> result = new ArrayList<>();
        List<Integer> aux = new ArrayList<>();
        search(nums, k, 0, aux, result);
        return result.toArray(new int[0][]);
    }

    private void search(int[] nums, int k, int start, List<Integer> aux, List<int[]> result) {
        if (k == aux.size()) {
            result.add(aux.stream().mapToInt(Integer::valueOf).toArray());
            return;
        }

        for (int i = start; i < nums.length; ++i) {
            aux.add(nums[i]);
            search(nums, k, i + 1, aux, result);
            aux.remove(aux.size() - 1);
        }
    }
}
