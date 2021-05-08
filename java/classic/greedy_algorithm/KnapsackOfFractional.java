package classic.greedy_algorithm;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class KnapsackOfFractional {
    public int solution(int[] weights, int[] values, int target) {
        List<GoodNode> goods = new ArrayList<>();
        for (int i = 0; i < weights.length; ++i) {
            goods.add(new GoodNode(weights[i], values[i]));
        }

        Collections.sort(goods, new Comparator<GoodNode>() {
            @Override
            public int compare(GoodNode node1, GoodNode node2) {
                return (node1.rate < node2.rate) ? 1 : -1;
            }
        });

        int result = 0;
        for (GoodNode good : goods) {
            if (target < good.weight) {
                return result + target * good.value / good.weight;
            }

            target -= good.weight;
            result += good.value;
        }
        return result;
    }

    private class GoodNode {
        public int weight = 0;
        public int value = 0;
        public double rate = 0;

        public GoodNode(int weight, int value) {
            this.weight = weight;
            this.value = value;
            this.rate = (double) value / weight;
        }
    }
}
