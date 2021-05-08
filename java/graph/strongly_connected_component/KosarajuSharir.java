package graph.strongly_connected_component;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Stack;

public class KosarajuSharir {
    public int[][] search(VertexNode[] graphs) {
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        Stack<Integer> stack = new Stack<>();
        search(graphs, 0, visited, stack);

        VertexNode[] inverseGraphs = new VertexNode[graphs.length];
        for (int i = 0; i < graphs.length; ++i) {
            inverseGraphs[i] = new VertexNode(graphs[i].value);
        }
        for (int i = graphs.length - 1; i >= 0; --i) {
            EdgeNode edge = graphs[i].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                EdgeNode edgeNode = new EdgeNode(i, edge.weight);
                edgeNode.next = inverseGraphs[edgeIndex].next;
                inverseGraphs[edgeIndex].next = edgeNode;
                edge = edge.next;
            }
        }

        Arrays.fill(visited, false);
        List<int[]> result = new ArrayList<>();
        List<Integer> aux = new ArrayList<>();
        while (!stack.isEmpty()) {
            int index = stack.pop();
            if (!visited[index]) {
                reverseSearch(inverseGraphs, index, visited, aux);
                result.add(aux.stream().mapToInt(Integer::valueOf).toArray());
                aux.clear();
            }
        }
        return result.toArray(new int[0][]);
    }

    private void search(VertexNode[] graphs, int start, boolean[] visited, Stack<Integer> stack) {
        visited[start] = true;
        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (!visited[edgeIndex]) {
                search(graphs, edgeIndex, visited, stack);
            }
            edge = edge.next;
        }
        stack.push(start);
    }

    private void reverseSearch(VertexNode[] graphs, int start, boolean[] visited, List<Integer> aux) {
        visited[start] = true;
        aux.add(start);

        EdgeNode edge = graphs[start].next;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (!visited[edgeIndex]) {
                reverseSearch(graphs, edgeIndex, visited, aux);
            }
            edge = edge.next;
        }
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
