package graph.traversal;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Stack;

public class DFS {
    public int[] traverse(VertexNode[] graphs, int start) {
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        Stack<Integer> stack = new Stack<>();
        stack.push(start);

        List<Integer> result = new ArrayList<>();
        while (!stack.isEmpty()) {
            int index = stack.pop();
            if (visited[index]) {
                continue;
            }

            result.add(index);
            visited[index] = true;

            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                if (!visited[edgeIndex]) {
                    stack.push(edgeIndex);
                }
                edge = edge.next;
            }
        }
        return result.stream().mapToInt(Integer::valueOf).toArray();
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
