package classic.back_tracking;

import java.util.ArrayList;
import java.util.List;

public class Subcollection {
    public int[][] solution(int[] nums) {
        List<int[]> result = new ArrayList<>();
        List<Integer> aux = new ArrayList<>();
        search(nums, 0, aux, result);
        return result.toArray(new int[0][]);
    }

    private void search(int[] nums, int start, List<Integer> aux, List<int[]> result) {
        result.add(aux.stream().mapToInt(Integer::valueOf).toArray());
        for (int i = start; i < nums.length; ++i) {
            aux.add(nums[i]);
            search(nums, i + 1, aux, result);
            aux.remove(aux.size() - 1);
        }
    }
}
