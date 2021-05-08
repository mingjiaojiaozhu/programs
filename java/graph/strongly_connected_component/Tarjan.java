package graph.strongly_connected_component;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Stack;

public class Tarjan {
    public int[][] search(VertexNode[] graphs) {
        int[] parent = new int[graphs.length];
        Arrays.fill(parent, -1);
        Stack<Integer> stack = new Stack<>();

        List<int[]> result = new ArrayList<>();
        List<Integer> aux = new ArrayList<>();
        for (int i = 0; i < graphs.length; ++i) {
            if (0 == ~parent[i]) {
                search(graphs, i, parent, stack, result, aux, 0);
            }
        }
        return result.toArray(new int[0][]);
    }

    private int search(VertexNode[] graphs, int start, int[] parent, Stack<Integer> stack, List<int[]> result, List<Integer> aux, int count) {
        parent[start] = count;
        int minValue = count;
        stack.push(start);

        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (0 == ~parent[edgeIndex]) {
                count = search(graphs, edgeIndex, parent, stack, result, aux, count + 1);
            }
            edge = edge.next;

            if (minValue > parent[edgeIndex]) {
                minValue = parent[edgeIndex];
            }
        }

        if (parent[start] > minValue) {
            parent[start] = minValue;
            return count;
        }

        int index = stack.pop();
        while (index != start) {
            aux.add(index);
            parent[index] = Integer.MAX_VALUE;
            index = stack.pop();
        }
        aux.add(start);
        parent[start] = Integer.MAX_VALUE;
        result.add(aux.stream().mapToInt(Integer::valueOf).toArray());
        aux.clear();
        return count;
    }

    public class EdgeNode {
        public int index = 0;
        public int weight = 0;
        public EdgeNode next = null;

        public EdgeNode(int index, int weight) {
            this.index = index;
            this.weight = weight;
        }
    }

    public class VertexNode {
        public int value = 0;
        public EdgeNode next = null;

        public VertexNode(int value) {
            this.value = value;
        }
    }
}
