package graph.strongly_connected_component;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Stack;

public class Gabow {
    public int[][] search(VertexNode[] graphs) {
        int[] parent = new int[graphs.length];
        Arrays.fill(parent, -1);
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        Stack<Integer> path = new Stack<>();
        Stack<Integer> root = new Stack<>();

        List<int[]> result = new ArrayList<>();
        List<Integer> aux = new ArrayList<>();
        for (int i = 0; i < graphs.length; ++i) {
            if (0 == ~parent[i]) {
                search(graphs, i, parent, visited, path, root, result, aux, 0);
            }
        }
        return result.toArray(new int[0][]);
    }

    private int search(VertexNode[] graphs, int start, int[] parent, boolean[] visited, Stack<Integer> path, Stack<Integer> root, List<int[]> result, List<Integer> aux, int count) {
        parent[start] = count;
        path.push(start);
        root.push(start);

        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (0 == ~parent[edgeIndex]) {
                count = search(graphs, edgeIndex, parent, visited, path, root, result, aux, count + 1);
            } else if (!visited[edgeIndex]) {
                while (parent[root.peek()] > parent[edgeIndex]) {
                    root.pop();
                }
            }
            edge = edge.next;
        }

        if (start != root.peek()) {
            return count;
        }
        root.pop();

        int index = path.pop();
        while (index != start) {
            aux.add(index);
            visited[index] = true;
            index = path.pop();
        }
        aux.add(start);
        visited[start] = true;
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
