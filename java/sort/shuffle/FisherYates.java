package sort.shuffle;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

public class FisherYates {
    private static final Random _random = new Random();

    public int[] shuffle(int[] nums) {
        List<Integer> aux = Arrays.stream(nums).boxed().collect(Collectors.toList());
        List<Integer> result = new ArrayList<>();
        while (!aux.isEmpty()) {
            int index = _random.nextInt(aux.size());
            result.add(aux.get(index));
            aux.remove(index);
        }
        return result.stream().mapToInt(Integer::valueOf).toArray();
    }
}
