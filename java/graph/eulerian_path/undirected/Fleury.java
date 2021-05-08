package graph.eulerian_path.undirected;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class Fleury {
    public int[] search(VertexNode[] graphs) {
        int start = getStart(graphs);
        if (0 == ~start) {
            return new int[0];
        }

        boolean[][] visited = new boolean[graphs.length][graphs.length];
        for (int i = 0; i < graphs.length; ++i) {
            Arrays.fill(visited[i], false);
        }
        Stack<Integer> stack = new Stack<>();
        stack.push(start);

        List<Integer> result = new ArrayList<>();
        while (!stack.isEmpty()) {
            int index = stack.pop();
            EdgeNode edge = graphs[index].next;
            boolean flag = false;
            while (null != edge) {
                int edgeIndex = edge.index;
                if (!visited[index][edgeIndex]) {
                    flag = true;
                    break;
                }
                edge = edge.next;
            }
            if (!flag) {
                result.add(index);
            } else {
                search(graphs, index, stack, visited);
            }
        }
        Collections.reverse(result);
        return result.stream().mapToInt(Integer::valueOf).toArray();
    }

    private void search(VertexNode[] graphs, int start, Stack<Integer> stack, boolean[][] visited) {
        stack.push(start);
        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (!visited[start][edgeIndex]) {
                visited[start][edgeIndex] = true;
                visited[edgeIndex][start] = true;
                search(graphs, edgeIndex, stack, visited);
                break;
            }
            edge = edge.next;
        }
    }

    private int getStart(VertexNode[] graphs) {
        int start = 0;
        int oddCount = 0;
        for (int i = graphs.length - 1; i >= 0; --i) {
            int count = 0;
            EdgeNode edge = graphs[i].next;
            while (null != edge) {
                ++count;
                edge = edge.next;
            }
            if (0 != (count & 1)) {
                start = i;
                ++oddCount;
                if (oddCount > 2) {
                    break;
                }
            }
        }
        return (0 == oddCount || 2 == oddCount) ? start : -1;
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
